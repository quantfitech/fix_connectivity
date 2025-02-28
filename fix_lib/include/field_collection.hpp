#ifndef FIELD_COLLECTION_HPP
#define FIELD_COLLECTION_HPP

#include <vector>
#include <string>
#include <optional>
#include "field.hpp"

namespace qffixlib
{

enum class set_operation
{
    // Replace the first occurrence of a field with this tag. 
    // If there is no field with this tag do nothing.
    replace_first,
    // Replace the first occurrence of a field with this tag. 
    // If there is no field with this tag add a field with this tag and value.
    replace_first_or_append,
    // Append a new field with this tag and value. 
    append
};

enum class remove_operation
{
    // Remove the first occurrence of a field with this tag.
    // If there is not field with this tag do nothing.
    remove_first,
    // Remove all occurrences of a field with this tag.
    // If there is not field with this tag do nothing.
    remove_all
};

class field_collection : public std::vector<Field>
{
public:

    field_collection() {}
    field_collection(std::initializer_list<Field> fields);

    // The set methods return true if one or more fields were added/updated, false if not.
    bool set(int tag, const char* value, set_operation operation = set_operation::replace_first); 
    bool set(int tag, std::string value, set_operation operation = set_operation::replace_first);
    bool set(int tag, uint32_t value, set_operation operation = set_operation::replace_first);
    bool set(int tag, uint64_t value, set_operation operation = set_operation::replace_first);
    bool set(int tag, bool value, set_operation operation = set_operation::replace_first);
    bool set(const Field& field, set_operation operation = set_operation::replace_first);
    bool set(int tag, const qffixlib::field_value& value, set_operation operation = set_operation::replace_first);
   
    Field get(int tag) const;

    std::optional<Field> try_get(int tag) const noexcept;

    Field try_get_or_default(int tag, const qffixlib::field_value& default_value) const;
    Field try_get_or_default(int tag, const Field& default_value) const;
    Field try_get_or_default(int tag, uint32_t default_value) const;
    Field try_get_or_default(int tag, const std::string& default_value) const;

    // The remove methods return true if one or more fields were removed, false if not.
    bool remove(int tag, remove_operation operation = remove_operation::remove_first);
    
    // void remove_at(size_t index);
    // void remove_range(size_t first_index, size_t last_index);

};

}

#endif