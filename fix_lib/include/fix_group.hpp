#ifndef FIX_GROUP_HPP
#define FIX_GROUP_HPP

#include "fix_field.hpp"
#include "logger.hpp"

namespace qffixlib {

    // Helper to find the index of the element with the given Id
    template <int Id, typename Tuple, std::size_t Index = 0>
    constexpr std::optional<std::size_t> find_index_by_id() {
        if constexpr (Index == std::tuple_size_v<Tuple>) {
            // End of tuple, not found
            return std::nullopt;
        } else {
            using CurrentType = std::decay_t<std::tuple_element_t<Index, Tuple>>;
            if constexpr (CurrentType::mId == Id) {
                // Found the element with the given Id
                return Index;
            } else {
                // Continue searching
                return find_index_by_id<Id, Tuple, Index + 1>();
            }
        }
    }

    // Function to get the element by Id (returns std::optional<Type>)
    template <int Id, typename Tuple>
    constexpr auto get_element_by_id(Tuple& tuple) {
        constexpr auto index = find_index_by_id<Id, Tuple>();
        if constexpr (index.has_value()) {
            return std::optional<std::tuple_element_t<index.value(), Tuple>>(std::get<index.value()>(tuple));
        } else {
            return std::optional<std::tuple_element_t<0, Tuple>>(std::nullopt);
        }
    }

    // Function to get the position by Id (returns std::optional<std::size_t>)
    template <int Id, typename Tuple>
    constexpr auto get_position_by_id() {
        return find_index_by_id<Id, Tuple>();
    }


    // old

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
        bool isSet() const {
            constexpr size_t index = get_index_by_tag<Tag, Fields...>();
            return (std::get<index>(fields).isSet);
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

        void deserializeNoOrder(TokenIterator& iter) {
            while(iter->tag != 0)
            {
                if (auto element = get_element_by_id<iter->tag>(fields)) {
                    element.deserialzie(iter);
                } else {
                    LOG_WARN("could not find tag {}", iter->tag);
                    //std::cout << "could not find tag: "  << iter->tag << std::endl;
                }
                ++iter;
            }
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
            return std::get<index>(this->fields).groups;
        }
    };


    template <int Tag, typename... Fields>
    struct Group {
        static constexpr int tag = Tag;
        int value;

        Group() = default;

        std::vector<BaseMessage<Fields...>> groups;

        void serialize(SendingBuffer& buff)  const {
            if (groups.size() == 0) {
                return;
            }
            
            buff.set(tag);

            buff.set(VALUE_SEPARATOR);

            buff.set(value);

            buff.set(FIELD_SEPARATOR);;
            
            for(auto& gr : groups) {
                gr.serialize(buff);
            }
        }

        template <int FieldTag, typename Value>
        void set(int group_index, const Value& newValue) {
            constexpr size_t index = get_index_by_tag<FieldTag, Fields...>();
            std::get<index>(groups[group_index]).value = newValue;
        }

        BaseMessage<Fields...>& createGroup() {
            value +=1;
            groups.resize(groups.size() + 1);
            return groups.at(groups.size() - 1);
        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                value = LexicalCast<int64_t>::cast((*iter).data,(*iter).length);
                ++iter;
                groups.resize(value);
                for (int i=0; i < value; i++) {
                    groups.at(i).deserialize(iter);
                }
            }
        }
    };


}

#endif //FIX_GROUP_HPP
