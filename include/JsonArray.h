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

// class JsonArray
// {
//     using JsonValue = std::variant<int, double, bool, std::string, JsonObj, JsonArray>;

// public:
//     JsonArray() {}
//     ~JsonArray() {}

//     static JsonArray FromDoc(const std::string& doc)
//     {
//         JsonArray arr;

//         std::string value;

//         int state = 0;

//         int word_start = 0;
        
//         for(int i = 0; i < doc.size(); ++i)
//         {
//             if(state == 0)
//             {
//                 if(doc[i] == '[')
//                 {
//                     state = 1;
//                     word_start = i + 1;
//                 }
//             }
//             else if(state == 1)
//             {
//                 if(doc[i] == ',' || doc[i] == ']')
//                 {
//                     value = doc.substr(word_start, i - word_start);
//                     word_start = i + 1;

//                     if(value[0] == '"' && value[value.size() - 1] == '"')
//                     {
//                         arr.m_list.push_back(value.substr(1, value.size() - 2));
//                     }
//                     else if(value[0] == '{' && value[value.size() - 1] == '}')
//                     {
//                         JsonObj tmp = JsonObj::FromDoc(value);
//                         arr.m_list.push_back(tmp);
//                         i += tmp.DocLen();
//                     }
//                     else if(value == "true")
//                     {
//                         arr.m_list.push_back(true);
//                     }
//                     else if(value == "false")
//                     {
//                         arr.m_list.push_back(false);
//                     }
//                     else if(value.find('.') != std::string::npos)
//                     {
//                         double num = std::stod(value);
//                         arr.m_list.push_back(num);
//                     }
//                     else
//                     {
//                         int num = std::stoi(value);
//                         arr.m_list.push_back(num);
//                     }

//                     if(doc[i] == ']')
//                     {
//                         arr.SetDocLen(i + 1);
//                         break;
//                     }
//                 }

//             }
//         }

//         arr.Print();

//         return arr;
//     }
    
//     void Print()
//     {
//         for(auto& value : m_list)
//         {
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
//                 else if constexpr (std::is_same_v<T, JsonObj>)
//                 {
//                     arg.Print();
//                 }
//             }, value);
//         }
//     }

//     int DocLen(){return m_doc_len;}
//     void SetDocLen(int len){m_doc_len = len;}

// private:
//     std::list<JsonValue> m_list;

//     int m_doc_len;
// };