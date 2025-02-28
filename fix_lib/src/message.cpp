#include "message.hpp"
#include "tag.hpp"
#include <cassert>
#include <charconv>
#include "logger.hpp"
#include "utils.hpp"

namespace qffixlib {

	static constexpr const char VALUE_SEPARATOR = '=';
	static constexpr const char FIELD_SEPARATOR = '\01';

	Message::Message(bool fill_in_header, std::initializer_list<Field> fields)
	{
		if (fill_in_header) {
			populate_header();
		}

		for (const auto& field : fields) {
			m_fields.set(field, set_operation::replace_first_or_append);
		}
	}

	void Message::populate_header() 
	{
		m_fields = {
				Field( FIX::Tag::BeginString,    std::string("") ),
				Field( FIX::Tag::BodyLength,     std::string("") ),
				Field( FIX::Tag::MsgType,        std::string("") ),
				Field( FIX::Tag::SenderCompID,   std::string("") ),
				Field( FIX::Tag::TargetCompID,   std::string("") ),
				Field( FIX::Tag::MsgSeqNum,      std::string("") ),
				Field( FIX::Tag::SendingTime,    std::string("") )
			};
	}

	void Message::reset()
	{
		m_fields.clear();
		m_decode_checksum = 0;
		m_decode_checksum_valid = false;
	}

	void Message::decode(const char* data, std::size_t length) {
		const char* current = data;
		const char* checksum_current = data;
		const char* end = data + length;
		auto complete = false;

		int currentGroup = 0;
		int groupTagDistance = -1;
		std::unordered_map<int, std::vector<int>>::iterator currentDictGroup = mGroupDictionary.end();


		while (current != end)
		{
			const auto* equals = std::find(current, end, VALUE_SEPARATOR);

			if (equals == end) {
				break;
			}

			int tag = 0;
			
			auto [ptr, ec] = std::from_chars(current, equals, tag);
			
			if (ec != std::errc()) {
				throw std::out_of_range(std::string(current, equals) + " is not a valid field tag");
			}
			const auto* delimiter = std::find(equals + 1, end, FIELD_SEPARATOR);

			if (delimiter == end) {
				break;
			}

			auto raw_length = delimiter - current + 1;

			const std::string_view value(equals + 1, std::distance(equals, delimiter) - 1);

			if (isRepeatingGroupTag(tag)) {
				LOG_DEBUG("group tag={} value={}", tag, value);
				int numGroups = std::stoi(std::string(value));
				mGroups.resize(numGroups);				
				currentDictGroup = mGroupDictionary.find(tag);
				m_fields.emplace_back(tag, value, raw_length);
			} else if (currentDictGroup != mGroupDictionary.end()) {
				auto it = std::find(currentDictGroup->second.begin(), currentDictGroup->second.end(), tag);
				if (it == currentDictGroup->second.end()) {
					// end of the groups
					LOG_DEBUG("end groups tag={} count={}", tag, currentGroup);
					currentGroup = 0;
					groupTagDistance = -1;
					currentDictGroup = mGroupDictionary.end();
					m_fields.emplace_back(tag, value, raw_length);
				} else {
					auto distance = std::distance(currentDictGroup->second.begin(), it);
					if (distance == groupTagDistance) {
						LOG_ERROR("dupliacted group tag {}", tag);
						throw std::runtime_error("duplicated field");
					}
					else if (distance < groupTagDistance) {
						//LOG_INFO("new group tag {} distance {} current group {}", tag, distance, currentGroup);
						groupTagDistance = -1;
						mGroups[++currentGroup].fields.emplace_back(tag, value, raw_length);
					} else  {
						//LOG_INFO("group tag {}", tag);
						mGroups[currentGroup].fields.emplace_back(tag, value, raw_length);
						groupTagDistance = distance;
					}
				}
			} else {
				m_fields.emplace_back(tag, value, raw_length);
			}
				
			current = delimiter + 1; 

			if (tag == FIX::Tag::CheckSum) {
				complete = true;
				break;
			}

			// We only calculate the checksum up to the checksum field itself.
			checksum_current = current;
		}
		m_decode_checksum += std::reduce(data, checksum_current);

		if (complete) {
			m_decode_checksum %= 256;
			m_decode_checksum_valid = true;
		}
	}

	bool Message::isRepeatingGroupTag(int tag) {
		return mGroupDictionary.find(tag) != mGroupDictionary.end();
	}

	bool Message::isPartOfGroup(int, int) {
        return false;
    }

	Message::decode_result Message::decode(std::string_view buffer)
	{
		const auto* current = buffer.data();
		const auto* checksum_current = buffer.data();
		const auto* end = buffer.data() + buffer.size();
		auto complete = false;


		while (current != end)
		{
			const auto* equals = std::find(current, end, VALUE_SEPARATOR);

			if (equals == end) {
				break;
			}

			int tag = 0;
			
			auto [ptr, ec] = std::from_chars(current, equals, tag);
			
			if (ec != std::errc()) {
				throw std::out_of_range(std::string(current, equals) + " is not a valid field tag");
			}

			/*if (FIX_5_0SP2::fields()[tag].is_data()) 
			{
				if (m_fields.empty()) {
					throw std::runtime_error("parsed a data field with tag=" + std::to_string(tag) + " that was not preceeded by a length field");                
				}

				int length = 0;

				try {
					length = std::stoi(m_fields.rbegin()->value());
				}
				catch (std::exception&) {
					throw std::runtime_error("parsed a data field with tag=" + std::to_string(tag) + " but the preceeding field value was not a valid numeric length");
				}

				if (equals + length + 1 >= end) { // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
					break;
				}

				const std::string_view value(equals + 1, length); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

				if (*(equals + length + 1) != field_separator) { // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
					throw std::runtime_error("parsed a data field wtih tag=" + std::to_string(tag) + " but the field did not have a trailing field separator");
				}

				m_fields.emplace_back(tag, value);
				// Only update current when we have a complete field so the return value is correct.
				// +1 for the field separator, +1 to move to the first character of the next tag.
				current = equals + length + 2; // // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			}
			else
			{
			*/	const auto* delimiter = std::find(equals + 1, end, FIELD_SEPARATOR); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

				if (delimiter == end) {
					break;
				}

				auto raw_length = delimiter - current;

				const std::string_view value(equals + 1, std::distance(equals, delimiter) - 1); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				
				m_fields.emplace_back(tag, value, raw_length);

				// Only update current when we have a complete field so the return value is correct.
				// +1 to move past the delimiter to the start of the next tag.
				current = delimiter + 1; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			//}

			if (tag == FIX::Tag::CheckSum) {
				complete = true;
				break;
			}

			// We only calculate the checksum up to the checksum field itself.
			checksum_current = current;
		}

		m_decode_checksum += std::reduce(buffer.data(), checksum_current);

		if (complete) {
			m_decode_checksum %= 256;
			m_decode_checksum_valid = true;
		}

		return { static_cast<size_t>(std::distance(&*buffer.begin(), current)), complete };
	}

	std::span<char>::pointer Message::encode(std::span<char>::pointer current, 
											std::span<char>::pointer end, 
											const Field& field)
	{
		auto [ptr, ec] = std::to_chars(current, end, field.tag());

		if (ec != std::errc()) {
			return nullptr;
		}

		current = ptr;

		if (current >= end) {
			return nullptr;
		}

		*current++ = VALUE_SEPARATOR;

		if (current >= end) {
			return nullptr;
		}

		auto value_length = field.value().length();

		if (current + value_length >= end) {
			return nullptr;
		}

		std::memcpy(current, field.value().data(), value_length);

		current += value_length;

		*current++ = FIELD_SEPARATOR;

		return current;
	}

	size_t Message::encode(std::span<char> buffer, int options)
	{
		if ((options & encode_options::set_body_length) != 0) {    
			fields().set(FIX::Tag::BodyLength, calculateBodyLength());
		}

		auto* current = buffer.data();
		auto* end = buffer.data() + buffer.size();

		for (const auto& field : fields())
		{
			if (field.tag() == FIX::Tag::CheckSum && ((options & encode_options::set_checksum) != 0)) 
			{
				auto checksum = calculateChecksum(std::string_view(buffer.data(), current - buffer.data()));
				auto checksum_field = qffixlib::Field(FIX::Tag::CheckSum, formatChecksum(checksum)); 
							
				if (fields().set(checksum_field)) 
				{
					current = encode(current, end, checksum_field);

					if (current == nullptr) {
						return 0;
					}

					break;
				}
			}

			current = encode(current, end, field);

			if (current == nullptr) {
				return 0;
			}
		}

		return current - buffer.data();
	}

	uint32_t Message::calculateBodyLength() const
	{
		bool passed_body_length {false};
		uint32_t length {0};

		for (const auto& field : fields())
		{
			if (field.tag() == FIX::Tag::CheckSum) {
				break;
			}

			if (!passed_body_length) {
				if (field.tag() == FIX::Tag::BodyLength) {
					passed_body_length = true;
				}
				continue;
			}

			if (field.rawLength()) {
				length += field.rawLength();
			} else {
				length += number_of_digits(field.tag());
				length += field.value().length();
				length += 2; // field && value separators 
			}
		}
		for(const auto& group : mGroups) {
			for(const auto& field: group.fields) {
				if (field.rawLength()) {
					length += field.rawLength();
				} else {
					length += number_of_digits(field.tag());
					length += field.value().length();
					length += 2; // field && value separators 
				}
			}
		}

		return length;
	}

	uint32_t Message::calculate_Checksum() const
	{
		if (m_decode_checksum_valid) {
			return m_decode_checksum;
		}

		throw std::runtime_error("NO DECODE CHECKSUM");

		return 0;
	}

	std::string Message::formatChecksum(uint32_t checksum)
	{
		auto buffer = std::to_string(checksum);

		if (buffer.length() > 3) {
			throw std::runtime_error("Cannot format CheckSum that is greater than 3 digits '" + buffer + "'");
		}

		static const char* padding = "000";

		return padding + buffer.length() + buffer;
	}

	uint32_t Message::calculateChecksum(std::string_view buffer)
	{
		return std::reduce(buffer.begin(), buffer.end(), 0) % 256;
	}

	const std::string& Message::BeginString() const
	{
		// TODO - maybe cache this but wait until we figure out an invalidation policy for message reuse etc
		auto field = std::find_if(m_fields.begin(), 
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::BeginString; });

		if (field == m_fields.end()) {
			throw std::runtime_error("message does not have a BeginString field");
		}

		return field->value();
	}

	const std::string& Message::SenderCompID() const
	{
		// TODO - maybe cache this but wait until we figure out an invalidation policy for message reuse etc
		auto field = std::find_if(m_fields.begin(), 
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::SenderCompID; });

		if (field == m_fields.end()) {
			throw std::runtime_error("message does not have a SenderCompID field");
		}

		return field->value();
	}

	const std::string& Message::TargetCompID() const
	{
		// TODO - maybe cache this but wait until we figure out an invalidation policy for message reuse etc
		auto field = std::find_if(m_fields.begin(), 
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::TargetCompID; });

		if (field == m_fields.end()) {
			throw std::runtime_error("message does not have a TargetCompID field");
		}

		return field->value();
	}

	char Message::MsgType() const
	{
		auto field = std::find_if(m_fields.begin(), 
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::MsgType; });

		if (field == m_fields.end()) {
			throw std::runtime_error("message does not have a MsgType field");
		}

		return field->value()[0];
	}

	uint32_t Message::MsgSeqNum() const
	{
		auto field = std::find_if(m_fields.begin(),
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::MsgSeqNum; });

		if (field == m_fields.end()) {
			throw std::runtime_error("message does not have a MsgSeqNum field");
		}

		return std::stoi(field->value());
	}

	bool Message::PossDupFlag() const
	{
		auto field = std::find_if(m_fields.begin(),
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::PossDupFlag; });

		if (field == m_fields.end()) {
		return false;
		}

		// TODO - bust this out into a get boolean method probably on field collection

		if (field->value() == "N") {
			return false;
		}

		if (field->value() == "Y") {
			return true;
		}

		throw std::runtime_error("field does not contain a valid boolean value " + std::to_string(field->tag()) + "=" + field->value());
	}

	bool Message::GapFillFlag() const
	{
		auto field = std::find_if(m_fields.begin(),
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::GapFillFlag; });

		if (field == m_fields.end()) {
		return false;
		}

		// TODO - bust this out into a get boolean method probably on field collection

		if (field->value() == "N") {
			return false;
		}

		if (field->value() == "Y") {
			return true;
		}

		throw std::runtime_error("field does not contain a valid boolean value " + std::to_string(field->tag()) + "=" + field->value());
	}

	bool Message::ResetSeqNumFlag() const
	{
		auto field = std::find_if(m_fields.begin(),
								m_fields.end(), 
								[](const auto& field) { return field.tag() == FIX::Tag::ResetSeqNumFlag; });

		if (field == m_fields.end()) {
		return false;
		}

		// TODO - bust this out into a get boolean method probably on field collection

		if (field->value() == "N") {
			return false;
		}

		if (field->value() == "Y") {
			return true;
		}

		throw std::runtime_error("field does not contain a valid boolean value " + std::to_string(field->tag()) + "=" + field->value());
	}


	bool Message::isAdmin() const
	{
		return strchr("0A12345", msg_type.c_str()[0]) != 0;
	}

	void Message::pretty_print(std::ostream&) const
	{
		// TODO - add an interface to support custom dictionaries.
		/*int widest_field_name {0};
		int widest_tag {0};

		for (const auto& field : fields())
		{
			auto name {FIX_5_0SP2::fields().name_of_field(field.tag())};
				
			if (name.length() > widest_field_name) {
				widest_field_name = int(name.length());
			}
			
			auto digits = int(number_of_digits(field.tag())); 

			if (digits > widest_tag) {
				widest_tag = digits;
			}
		}

		stream << FIX_5_0SP2::messages().name_of_message(MsgType()) << "\n{\n";

		for (const auto& field : fields())
		{
			// BodyLength  (9) 145
			//    MsgType (35) A
			auto name {FIX_5_0SP2::fields().name_of_field(field.tag())};

			stream << std::setw(widest_field_name) << std::right << name 
				<< std::setw(widest_tag + 4) << std::right << " (" + std::to_string(field.tag()) + ") "
				<< field.value();
			
			auto name_of_value = FIX_5_0SP2::fields().name_of_value(field.tag(), field.value());

			if (!name_of_value.empty()) {
				stream << " - " << name_of_value;
			}

			stream << '\n'; 
		}

		stream << "}\n";
	*/	
	}
}