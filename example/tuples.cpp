#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <charconv>
#include <span>
#include <vector>
#include <cmath>
#include <string>
#include <cstdint>
#include <cstring>
#include <algorithm>


    template<typename T> struct LexicalCast
    {
        static T cast(const char*, size_t)
        {
            return {};
        }
    };

    template<>
    struct LexicalCast<std::string>
    {
        static std::string cast(const char* offset, size_t size)
        {
            return {offset, size};
        }
    };

    template<>
        struct LexicalCast<double>
        {
            static double cast(const char* offset, size_t /*size*/)
            {
                double r = 0.0;
                bool neg = false;
                if (*offset == '-') {
                    neg = true;
                    ++offset;
                }
                while (*offset >= '0' && *offset <= '9') {
                    r = (r*10.0) + (*offset - '0');
                    ++offset;
                }
                if (*offset == '.') {
                    double f = 0.0;
                    int n = 0;
                    ++offset;
                    while (*offset >= '0' && *offset <= '9') {
                        f = (f*10.0) + (*offset - '0');
                        ++offset;
                        ++n;
                    }
                    r += f / std::pow(10.0, n);
                }
                if (neg) {
                    r = -r;
                }
                return r;
            }
        };

        template<>
        struct LexicalCast<int>
        {
            static int64_t cast(const char* offset, size_t /*size*/)
            {
                int64_t x = 0;
                bool neg = false;
                if (*offset == '-') {
                    neg = true;
                    ++offset;
                }
                while (*offset >= '0' && *offset <= '9') {
                    x = (x*10) + (*offset - '0');
                    ++offset;
                }
                if (neg) {
                    x = -x;
                }
                return x;
            }
        };


class TokenIterator {
    static constexpr const char VALUE_SEPARATOR = '=';
	static constexpr const char FIELD_SEPARATOR = '|'; //'\01';

    struct TokenData {
        int tag={0};
        const char* data{nullptr};
        long length{0};
    };

public:
   
    using pointer = const TokenData*;
    using reference = const TokenData&;

    // Construct from a stream and delimiter.
    TokenIterator(const char* data, size_t length)
        : mData(data), mLength(length)
    {
        mEnd = mData + mLength;
        mCurrent = mData;
        ++(*this); // Read the first token
    }

    // Pre-increment: read next token from the stream.
    TokenIterator& operator++() {

        if (mCurrent != mEnd)
		{
			const auto* equals = std::find(mCurrent, mEnd, VALUE_SEPARATOR);

			if (equals == mEnd) {
				mCurrentToken = {};
                mCurrent = mEnd = nullptr;
			}

			int tag = 0;
			
			auto [ptr, ec] = std::from_chars(mCurrent, equals, tag);
			
			if (ec != std::errc()) {
				throw std::out_of_range(std::string(mCurrent, equals) + " is not a valid field tag");
			}
			const auto* delimiter = std::find(equals + 1, mEnd, FIELD_SEPARATOR);

			if (delimiter == mEnd && *delimiter != FIELD_SEPARATOR) {
				mCurrentToken = {};
                mCurrent = mEnd = nullptr;
			}
            //auto raw_length = delimiter - mCurrent + 1;
            mCurrentToken = {tag, equals + 1, delimiter - equals - 1};
            std::cout << mEnd - mCurrent << std::endl;
            if (delimiter != mEnd) {
                mCurrent = delimiter + 1;                
            } else {
                mCurrentToken = {};
                mCurrent = mEnd = nullptr;
            }
        }
        return *this;
    }


    // Post-increment.
    TokenIterator operator++(int) {
        TokenIterator temp(*this);
        ++(*this);
        return temp;
    }

    // Dereference returns the current token.
    reference operator*() const { return mCurrentToken; }
    pointer operator->() const { return &mCurrentToken; }

    // Equality: two iterators are equal if they have the same stream pointer.
    bool operator==(const TokenIterator& other) const {
        return mData == other.mData;
    }
    bool operator!=(const TokenIterator& other) const {
        return !(*this == other);
    }

private:
    const char* mData{nullptr};
    size_t mLength{0};
    const char* mEnd{nullptr};
    const char* mCurrent{nullptr};
    TokenData mCurrentToken{};
};

struct SendingBuffer {
    char data[1024];
    size_t offset{0};

    void set(char aChar) {
        *(current()) = aChar;
        offset += 1;
    }

    void set(uint64_t value) {
        auto [ptr, ec] = std::to_chars(current(), end(), value);

		if (ec != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        offset = ptr - data;

		if (current() >= end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
    }

    void set(int value) {
        auto [ptr, ec] = std::to_chars(current(), end(), value);

		if (ec != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        offset = ptr - data;

		if (current() >= end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
    }

    char* current() { return  data + offset; }
    char* end() {return data + 1023; }
};


template <int Tag, typename Type>
struct Field {

    static constexpr int tag = Tag;
    Type value;

    Field() = default;
    explicit Field(Type t) : value(t) {}
    using ValueType = Type;

    bool isSet{false};

    void setValue(Type val) {
        value = val;
        isSet = true; 
    }

    void serialize(SendingBuffer& buff) const {   
        if (!isSet)
        {
            return;
        }
       	auto [ptr, ec] = std::to_chars(buff.current(), buff.end(), tag);

		if (ec != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        buff.offset = ptr - buff.data;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

		*(buff.current()) = '=';
        buff.offset += 1;

        auto [ptr_val, ec_val] = std::to_chars(buff.current(), buff.end(), value);

		if (ec_val != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        buff.offset = ptr_val - buff.data;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

        *(buff.current()) = '|';
        buff.offset += 1;

    }

    void deserialize(TokenIterator& iter) {
        if ((*iter).tag == tag) {
            //value = LexicalCast<Type>::cast((*iter).data, (*iter).length);
            setValue(LexicalCast<Type>::cast((*iter).data, (*iter).length));
            ++iter;
        }
    }
};


template <int Tag>
struct Field<Tag,char> {

    static constexpr int tag = Tag;
    char value;

    Field() = default;
    explicit Field(char t) : value(t) {}
    using ValueType = char;

    bool isSet{false};

    void setValue(char val) {
        value = val;
        isSet = true; 
    }

    void serialize(SendingBuffer& buff) const {   
        if (!isSet)
        {
            return;
        }
       	auto [ptr, ec] = std::to_chars(buff.current(), buff.end(), tag);

		if (ec != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        buff.offset = ptr - buff.data;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

		*(buff.current()) = '=';
        buff.offset += 1;

        *(buff.current()) = value;
        buff.offset += 1;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

        *(buff.current()) = '|';
        buff.offset += 1;

    }

    void deserialize(TokenIterator& iter) {
        if ((*iter).tag == tag) {
            //value = LexicalCast<int>::cast((*iter).data, (*iter).length);
            setValue((*iter).data[0]);
            ++iter;
        }
    }
};

template <int Tag>
struct Field<Tag,std::string> {

    static constexpr int tag = Tag;
    std::string value;

    Field() = default;
    explicit Field(const std::string& t) : value(t) {}
    using ValueType = std::string;

    bool isSet{false};

    void setValue(std::string val) {
        value = val;
        isSet = true; 
    }

    void serialize(SendingBuffer& buff) const {   
        if (!isSet)
        {
            return;
        }
       	auto [ptr, ec] = std::to_chars(buff.current(), buff.end(), tag);

		if (ec != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        buff.offset = ptr - buff.data;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

		*(buff.current()) = '=';
        buff.offset += 1;

        std::memcpy(buff.current(), value.data(), value.length());
        buff.offset += value.length();


		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

        *(buff.current()) = '|';
        buff.offset += 1;

    }

    void deserialize(TokenIterator& iter) {
        if ((*iter).tag == tag) {
            //value = std::string((*iter).data, (*iter).length);
            setValue(std::string((*iter).data, (*iter).length));
            ++iter;
        }
    }
};


// Base case: first field matches
template <int Tag, typename Field, typename... Rest>
constexpr size_t get_index_by_tag_impl(size_t index = 0) {
    if constexpr (Field::tag == Tag)
        return index;
    else {
        static_assert(sizeof...(Rest) > 0, "Tag not found in FIXMessage");
        return get_index_by_tag_impl<Tag, Rest...>(index + 1);
    }
}

template <int Tag, typename... Fields>
constexpr size_t get_index_by_tag() {
    return get_index_by_tag_impl<Tag, Fields...>(0);
}

template <typename... Fields>
class BaseMessage {
public:
    std::tuple<Fields...> fields;

    // Compile-time getter: get<FieldTag>() returns a reference to the field's value.
    template <int Tag>
    auto& get() {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(fields).value;
    }
    
    template <int Tag>
    const auto& get() const {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(fields).value;
    }
    
    // Compile-time setter: set<FieldTag>(newValue)
    template <int Tag, typename Value>
    void set(const Value& newValue) {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        //std::get<index>(fields).value = newValue;
        std::get<index>(fields).setValue(newValue);  
    }

    void deserialize(TokenIterator& iter) {
        // Using a fold expression to expand over the tuple elements.
        std::apply([&iter](auto&... elems) { ((elems.deserialize(iter)), ...); }, fields);
    }

    void serialize( SendingBuffer& buff) const {
        // Using a fold expression to expand over the tuple elements.
        std::apply([&buff](auto&... elems) { ((elems.serialize(buff)), ...); }, fields);
    }

    template <int Tag>
    auto& createGroup() {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(this->fields).createGroup();
    }

    template <int Tag>
    auto& getGroups() {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(this->fields).groups();
    }
};


template <int Tag, typename... Fields>
struct Group {
    static constexpr int tag = Tag;
    int value;

    Group() = default;
    //using GroupFields = std::tuple<Fields...>;
    //std::tuple<Fields...> fields;

    std::vector<BaseMessage<Fields...>> groups;

    void serialize(SendingBuffer& buff)  const {
        //std::cout << "group: " << std::to_string(Tag) + "=" + std::to_string(value) << std::endl;
        if (value == 0 || groups.size() == 0) {
            return;
        }  
       	auto [ptr, ec] = std::to_chars(buff.current(), buff.end(), tag);

		if (ec != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        buff.offset = ptr - buff.data;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

		*(buff.current()) = '=';
        buff.offset += 1;

        auto [ptr1, ec1] = std::to_chars(buff.current(), buff.end(), value);

		if (ec1 != std::errc()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}
        buff.offset = ptr1 - buff.data;

		if (buff.current() >= buff.end()) {
			throw std::runtime_error("failed to copy tag to buffer");
		}

        *(buff.current()) = '|';
        buff.offset += 1;

        for(auto& gr : groups) {
             //std::apply([](const auto&... elems) { ((elems.tostring()), ...); }, gr);
             gr.serialize(buff);
        }
        std::cout << "end group." << std::endl;
    }

    template <int FieldTag, typename Value>
    void set(int group_index, const Value& newValue) {
        constexpr size_t index = get_index_by_tag<FieldTag, Fields...>();
        //std::get<index>(fields).value = newValue;
        std::get<index>(groups[group_index]).value = newValue;
    }

    BaseMessage<Fields...>& createGroup() {
        value +=1;
        groups.resize(groups.size() + 1);
        return groups.at(groups.size() - 1);
    }

    void deserialize(TokenIterator& iter) {
        if ((*iter).tag == tag) {
            value = LexicalCast<int>::cast((*iter).data,(*iter).length);
            ++iter;
            groups.resize(value);
            for (int i=0; i < value; i++) {
                //std::apply([&iter](auto&... elems) { ((elems.deserialize(iter)), ...); }, groups[i]);
                groups.at(i).deserialize(iter);
            }
        }
    }
};

// FIXMessage definition:
template <typename... Fields>
class FIXMessage : public BaseMessage<Fields...> {
public:

    template <int Tag>
    void makeGroups(int i) {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(this->fields).groups.resize(i);
    }

    template <int Tag>
    auto& getGroup(int i) {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(this->fields).groups[i];
    }

    template <int Tag>
    auto& getGroupElement() {
        constexpr size_t index = get_index_by_tag<Tag, Fields...>();
        return std::get<index>(this->fields);
    }
};


// Base case: Print a regular (non-tuple) element.
template <typename T>
void print_tuple_element(const T& elem) {
    //std::cout << elem.tag << "-" << elem.value << std::endl;
    elem.tostring();
}

// Helper: Print all elements of a tuple (non-nested version).
template <typename Tuple, std::size_t... Is>
void print_tuple_impl(const Tuple& tup, std::index_sequence<Is...>) {
    // For each element, call our overloaded print_tuple_element.
    ((print_tuple_element(std::get<Is>(tup))), ...);
}

// The wrapper to print a (possibly nested) tuple in a flat manner.
template <typename... Ts>
void print_flat_tuple(const std::tuple<Ts...>& tup) {
    print_tuple_impl(tup, std::make_index_sequence<sizeof...(Ts)>{});
    std::cout << "\n";
}



int main() {

    using F1 = Field<1,std::string>;
    using F2 = Field<2,int>;
    using F3 = Field<3,double>;
    // Create an inner tuple where the first element (2) is the repetition count,
    // and then we have 3.14 and "Hello".

    //using Inner = std::tuple<F2, F1, F3>;
    //Inner inner_tuple(2, "abc", 3.12);
    
    // Create an outer tuple that contains:
    // "Outer String", the inner tuple, and a character 'A'.
    //std::tuple<F1, Inner, F1> outer_tuple("outer", inner_tuple, "end");

    using NestedGroupType = Group<100, F3, F2>;

    using GroupType = Group<99, F1, F2, NestedGroupType>;

    //std::string fixMsg = "1=dupa|2=1|99=2|1=gr1|2=20|1=gr2|2=22|3=3.14";
    std::string fixMsg = "1=dupa|2=1|99=2|1=gr1|2=20|2=22|100=1|3=666.6|2=66|3=3.14|";
    std::stringstream ss(fixMsg);
    //TokenIterator it(ss, '|');
    TokenIterator it(fixMsg.c_str(), fixMsg.length());
    FIXMessage<F1,F2, GroupType, F3> desMsg;
    desMsg.deserialize(it);
    SendingBuffer buffdes;
    desMsg.serialize(buffdes);
    auto res = std::string(buffdes.data, buffdes.offset);
    std::cout << "res: " << res << std::endl;


    FIXMessage<F1,F2, GroupType, F3> msg;
    msg.set<1>("dupa");
    msg.set<2>(1);
    msg.set<3>(3.14);
    auto& gr = msg.createGroup<99>();
    gr.set<1>("gr0");
    gr.set<2>(20);
    auto& subGr = gr.createGroup<100>();
    subGr.set<3>(1.21);
    subGr.set<2>(21);
    auto& gr2 = msg.createGroup<99>();
    gr2.set<1>("gr2");
    gr2.set<2>(22);
    //auto& group = msg.getGroup<99>(0);

    auto a3 = msg.get<3>();
    
    //auto& grEl = msg.getGroupElement<99>();
    //grEl.set<1>(0, "gr0");
    //grEl.set<2>(0, 20);

    //iterateGroup(msg.fields);
    SendingBuffer buff;
    msg.serialize(buff);
    res = std::string(buff.data, buff.offset);
    std::cout << "res1: " << res << std::endl;
    
    
   // print_flat_tuple(msg.fields);

    // When flattened, we want:
    // "Outer String", then the inner tuple printed as "3.14 Hello" repeated 2 times, then 'A'
    //print_flat_tuple(outer_tuple);  


    return 0;
}
