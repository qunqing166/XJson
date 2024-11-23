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

    // std::map<std::string, JsonValue>::iterator begin() const
    // {
    //     return m_map.begin();
    // }

    // std::map<std::string, JsonValue>::iterator end() const
    // {
    //     return m_map.end();
    // }

    std::map<std::string, JsonValue> ToMap() const
    {
        return m_map;
    }



private:
    std::map<std::string, JsonValue> m_map;
};

// class JsonObject
// {

// public:
//     JsonObject() {}
//     ~JsonObject() {}

//     static JsonObject FromDoc(const std::string& doc)
//     {
//         JsonObject obj;

//         std::string key;
//         // JsonValue value;
//         std::string value;

//         int state = 0;

//         int word_start = 0;

//         for(int i = 0; i < doc.size(); ++i)
//         {
//             if(state == 0)
//             {
//                 if(doc[i] == '{')
//                 {
//                     state = 1;
//                 }
//             }
//             else if(state == 1)
//             {
//                 if(doc[i] == '"')
//                 {
//                     word_start = i + 1;
                    
//                     for(int j = i + 1; j < doc.size(); ++j)
//                     {
//                         if(doc[j] == '"')
//                         {
//                             key = doc.substr(word_start, j - word_start);
//                             i = j;
//                             // std::cout << "key: " << key << "    ";
//                             break;
//                         }
//                     }
//                 }
//                 else if(doc[i] == ':')
//                 {
//                     state = 2;
//                     while(doc[++i] == ' ');
//                     if(doc[i] == '{')
//                     {
//                         JsonObject tmp = JsonObj::FromDoc(doc.substr(i));
//                         obj.m_map[key] = tmp;
//                         i += tmp.DocLen();
//                     }
//                     else if(doc[i] == '[')
//                     {

//                     }
//                     else
//                     {
//                         word_start = i + 1;
//                     }
//                 }
//             }
//             else if(state == 2)
//             {
//                 if(doc[i] == ',' || doc[i] == '}')
//                 {

//                     if(doc[i] == '}')
//                     {
//                         // len = i + 1;
//                         obj.SetDocLen(i + 1);
//                         break;
//                     }

//                     state = 1;
//                     value = doc.substr(word_start, i - word_start);
//                     // std::cout << "value: " << value << std::endl;
//                     if(value[0] == '"' && value[value.size() - 1] == '"')
//                     {
//                         // JsonValue v = value.substr(1, value.size() - 2);
//                         obj.m_map[key] = value.substr(1, value.size() - 2);
//                     }
//                     else if(value == "true")
//                     {
//                         obj.m_map[key] = true;
//                     }
//                     else if(value == "false")
//                     {
//                         obj.m_map[key] = false;
//                     }
//                     else
//                     {
//                         if(value.find('.') != std::string::npos)
//                         {
//                             double num = std::stod(value);
//                             obj.m_map[key] = num;
//                         }
//                         else
//                         {
//                             int num = std::stoi(value);
//                             obj.m_map[key] = num;
//                         }
//                     }

//                 }
//             }
//         }

//         // obj.Print();

//         return obj;
//     }

//     void Print()
//     {
//         for(auto& [key, value] : m_map)
//         {
//             std::cout << "key: " << key << "    ";
//             std::cout << "value: ";
//             std::visit([&](auto&& arg) {
//                 using T = std::decay_t<decltype(arg)>;
//                 if constexpr (std::is_same_v<T, int>)
//                 {
//                     std::cout << arg << std::endl;
//                 }
//                 else if constexpr (std::is_same_v<T, double>)
//                 {
//                     std::cout << arg << std::endl;
//                 }
//                 else if constexpr (std::is_same_v<T, bool>)
//                 {
//                     std::cout << arg << std::endl;
//                 }
//                 else if constexpr (std::is_same_v<T, std::string>)
//                 {
//                     std::cout << arg << std::endl;
//                 }
//                 else if constexpr (std::is_same_v<T, JsonObject>)
//                 {
//                     arg.Print();
//                 }
//             }, value);
//         }
//     }

//     int DocLen(){return m_doc_len;}
//     void SetDocLen(int len){m_doc_len = len;}

// private:
//     std::map<std::string, JsonValue> m_map;

//     int m_doc_len;
// };