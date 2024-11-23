#pragma once

#include <iostream>
#include <map>
#include <string>
#include "JsonValue.h"

class JsonObject
{
public:
    JsonObject() {}
    JsonObject(const std::map<std::string, JsonValue>& map) : m_map(map) {}

    ~JsonObject() {}

    JsonValue Value(const std::string& key) const
    {
        auto it = m_map.find(key);
        if(it == m_map.end())
        {
            return JsonValue();
        }
        return it->second;
    }

    void Insert(const std::string& key, const JsonValue& value)
    {
        m_map[key] = value;
    }

    JsonValue& operator[](const std::string& key)
    {
        return m_map[key];
    }

    bool Contains(const std::string& key) const
    {
        return m_map.find(key)!= m_map.end();
    }

    bool Empty() const
    {
        return m_map.empty();
    }
    int Size() const
    {
        return m_map.size();
    }

    void Clear()
    {
        m_map.clear();
    }

    void Erase(const std::string& key)
    {
        m_map.erase(key);    
    }

    std::map<std::string, JsonValue> ToMap() const
    {
        return m_map;
    }



private:
    std::map<std::string, JsonValue> m_map;
};