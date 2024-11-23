#pragma once

#include <iostream>
#include <list>
#include <string>
#include <variant>
#include <vector>
#include "JsonValue.h"

class JsonArray
{
public:

    JsonArray() {}
    JsonArray(const std::vector<JsonValue>& list) : m_list(list) {}

    ~JsonArray() {}

    JsonValue At(int index) const
    {
        return m_list.at(index);
    }

    JsonValue operator[](int index) const
    {
        return m_list.at(index);
    }

    void Add(const JsonValue& value)
    {
        m_list.push_back(value);
    }

    int Size() const
    {
        return m_list.size();
    }

    std::vector<JsonValue> ToArray() const
    {
        return m_list;
    }

private:

    std::vector<JsonValue> m_list;

};
