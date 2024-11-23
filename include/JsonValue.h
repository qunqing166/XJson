#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <variant>

class JsonArray;
class JsonObject;

class JsonValue 
{
public:

    enum JsonType
    {
        Null,
        Bool,
        Int,
        Double,
        String,
        Array,
        Object
    };

    JsonValue() { type = JsonType::Null; }
    JsonValue(const JsonValue& other)
    {
        type = other.type;
        this->value = other.value;
    }
    JsonValue(int value){ SetValue(value); }    
    JsonValue(double value){ SetValue(value); }
    JsonValue(bool value){ SetValue(value); }
    JsonValue(const char* value){ SetValue(std::string(value)); }
    JsonValue(const std::string& value){ SetValue(value); }
    JsonValue(const std::vector<JsonValue>& value){ SetValue(value); }
    JsonValue(const std::map<std::string, JsonValue>& value){ SetValue(value); }
    JsonValue(const JsonArray &value){ SetValue(value); }
    JsonValue(const JsonObject &value){SetValue(value); }


    ~JsonValue() {};

    JsonValue operator=(const JsonValue& other)
    {
        type = other.type;
        this->value = other.value;
        return *this;
    }

    JsonValue operator[](std::variant<int, std::string> key)
    {
        switch(key.index())
        {
        case 0:
            return std::get<std::vector<JsonValue>>(value).at(std::get<int>(key));
        case 1:
            return std::get<std::map<std::string, JsonValue>>(value).at(std::get<std::string>(key));
        default:
            return JsonValue();
        }
    }

    bool IsInt() const { return type == Int; }
    bool IsDouble() const { return type == Double; }
    bool IsBool() const { return type == Bool; }
    bool IsString() const { return type == String; }
    bool IsArray() const { return type == Array; }
    bool IsObject() const { return type == Object; }

    int ToInt() const { return std::get<int>(value); }
    double ToDouble() const { return std::get<double>(value); }
    bool ToBool() const { return std::get<bool>(value); }
    const std::string& ToString() const { return std::get<std::string>(value); }

    JsonArray ToArray() const;
    JsonObject ToObject() const;

    void SetValue(int value) { type = JsonType::Int; this->value = value; }
    void SetValue(double value) { type = JsonType::Double; this->value = value; }
    void SetValue(bool value) { type = JsonType::Bool; this->value = value; }
    void SetValue(const std::string& value) { type = JsonType::String; this->value = value; }
    void SetValue(const std::vector<JsonValue>& value) { type = JsonType::Array; this->value = value; }
    void SetValue(const std::map<std::string, JsonValue>& value) { type = JsonType::Object; this->value = value; }
    void SetValue(const JsonArray& value);
    void SetValue(const JsonObject& value);

    JsonType Type() const { return type; }

private:
    JsonType type;

    std::variant<int, double, bool, std::string, std::vector<JsonValue>, std::map<std::string, JsonValue>> value;
    
};