#include "field_collection.hpp"
#include <algorithm>
#include <stdexcept>

namespace qffixlib
{

field_collection::field_collection(std::initializer_list<Field> fields)
:   std::vector<Field>(fields)
{
}

bool field_collection::set(const Field& field, set_operation operation) 
{
    if (operation == set_operation::append) {
        push_back(field);
        return true;
    }

    auto existing = std::find_if(begin(), end(), [&](const auto& current_field) { return current_field.tag() == field.tag(); });

    if (existing == end()) {
        if (operation == set_operation::replace_first_or_append) {
            push_back(field);
            return true;
        }
        return false;
    }

    *existing = field;

    return true; 
}

bool field_collection::set(int tag, const char* value, set_operation operation)
{
    return set(tag, std::string(value), operation);
}

bool field_collection::set(int tag, std::string value, set_operation operation)
{
    return set(Field(tag, std::move(value)), operation);
}

bool field_collection::set(int tag, uint32_t value, set_operation operation)
{
    return set(tag, std::to_string(value), operation);
}

bool field_collection::set(int tag, uint64_t value, set_operation operation)
{
    return set(tag, std::to_string(value), operation);
}

bool field_collection::set(int tag, bool value, set_operation operation)
{
    return set(tag, value ? std::string("Y") : std::string("N"), operation);
}

bool field_collection::set(int tag, const qffixlib::field_value& value, set_operation operation)
{
    return set(tag, std::string(value.value()), operation);
}

Field field_collection::get(int tag) const
{
    auto result = try_get(tag);

    if (!result.has_value()) {
        throw std::out_of_range("field collection does not contain a field with Tag " + std::to_string(tag));
    }

    return result.value();
}


std::optional<Field> field_collection::try_get(int tag) const noexcept
{
    auto field = std::find_if(begin(), end(), [&](const auto& field) { return field.tag() == tag; });

    if (field == end()) {
        return std::nullopt;
    }

    return *field;
}

Field field_collection::try_get_or_default(int tag, const qffixlib::field_value& default_value) const
{
    auto value = try_get(tag);

    if (value.has_value()) {
        return value.value();
    }

    return Field(tag, default_value);
}

Field field_collection::try_get_or_default(int tag, const Field& default_value) const
{
    auto value = try_get(tag);

    if (value.has_value()) {
        return value.value();
    }

    return default_value;
}

Field field_collection::try_get_or_default(int tag, uint32_t default_value) const
{
    auto value = try_get(tag);

    if (value.has_value()) {
        return value.value();
    }

    return Field(tag, default_value);
}

Field field_collection::try_get_or_default(int tag, const std::string& default_value) const
{
    auto value = try_get(tag);

    if (value.has_value()) {
        return value.value();
    }

    return Field(tag, default_value);
}

bool field_collection::remove(int tag, remove_operation operation)
{
    auto predicate = [=](const auto& field) { return field.tag() == tag; };

    if (operation == remove_operation::remove_first) {
        auto first = std::find_if(begin(), end(), predicate);
        if (first == end()) {
            return false;
        }
        erase(first);
        return true;
    }

    if (operation == remove_operation::remove_all) {
        auto first = std::remove_if(begin(), end(), predicate);
        if (first == end()) {
            return false;
        }
        erase(first, end());
        return true;
    }

    return false;
}
}