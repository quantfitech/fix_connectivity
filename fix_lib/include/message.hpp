#ifndef MESSAGE_H
#define MESSAGE_H
#include <optional>
#include <span>
#include "field_collection.hpp"
#include <unordered_set>
#include "tag.hpp"

namespace qffixlib
{

// It is useful to be able to disable the setting of various standard fields when encoding for
// testing purposes.
namespace encode_options {
   constexpr int none               = 0b00000;
   constexpr int set_checksum       = 0b00001;
   constexpr int set_body_length    = 0b00010;
   constexpr int set_begin_string   = 0b00100;
   constexpr int set_msg_seq_num    = 0b01000;
   constexpr int set_sending_time   = 0b10000;
   constexpr int standard           = set_checksum | set_body_length | set_begin_string | set_msg_seq_num | set_sending_time;
   constexpr int standard_no_sending = set_checksum | set_body_length | set_begin_string | set_msg_seq_num;
}

struct FixGroup {
    //std::unordered_map<int, std::string> fields;
    field_collection fields;
    std::vector<FixGroup> subGroups;  // For nested repeating groups
};

using FixGroups = std::vector<FixGroup>;

class Message
{
public:

    Message(bool populate_header = false, std::initializer_list<Field> fields = {});

	void populate_header();

    field_collection& fields() { return m_fields; }
    const field_collection& fields() const { return m_fields; }

    void reset();

    const std::string& BeginString() const;
    const std::string& SenderCompID() const;
    const std::string& TargetCompID() const;
    char MsgType() const;
    uint32_t MsgSeqNum() const;
    bool PossDupFlag() const;
    bool GapFillFlag() const;
    bool ResetSeqNumFlag() const;

    bool isAdmin() const;

    void pretty_print(std::ostream& stream) const;

    // Decode FIX tag/value pairs and store them in this message. This does no validation of
    // the field content and does not validate the BodyLength or CheckSum. This supports
    // decoding fragmentary messages. This method is restartable, it can be called multiple
    // times with separate pieces of the same message until completion. This method does not
    // track completeness on subsequent calls so you can call it again after it has returned
    // complete=true and it will decode and store any fields it reads which may result in an
    // invalid message.
    struct decode_result
    {
        size_t consumed;
        bool complete;
    };

    decode_result decode(std::string_view buffer);
    void decode(const char*, std::size_t);

    // Encode this FIX message into the supplied buffer. This method calculates 
    // and rewrites the BodyLength and CheckSum by default, these fields must already be present, they
    // will not be added. It does no validation of the message content/structure. 
    // Returns 0 if the buffer is not big enough.
    size_t encode(std::span<char> buffer, int options = encode_options::standard);

    uint32_t calculateBodyLength() const;
    uint32_t calculate_Checksum() const;

    static uint32_t calculateChecksum(std::string_view buffer);
    static std::string formatChecksum(uint32_t checksum);

    const FixGroups& groups() const { return  mGroups; }


private:

    std::unordered_map<int, std::vector<int>> mGroupDictionary = {  {FIX::Tag::NoMDEntries, {FIX::Tag::MDUpdateAction, FIX::Tag::MDEntryType, FIX::Tag::MDEntryID, FIX::Tag::Symbol,
                                                                                             FIX::Tag::MDEntryPx, FIX::Tag::MDEntrySize, FIX::Tag::TransactTime, 
                                                                                             FIX::Tag::MDPriceLevel, FIX::Tag::AggressorSide}} };

	std::string msg_type;

    std::vector<FixGroup> mGroups;

    field_collection m_fields;

    bool isRepeatingGroupTag(int tag);

    bool isPartOfGroup(int, int);

    static std::span<char>::pointer encode(std::span<char>::pointer current, 
                                           std::span<char>::pointer end, 
                                           const Field& field);

    uint32_t m_decode_checksum = 0;
    bool m_decode_checksum_valid = false;

};

}

#endif