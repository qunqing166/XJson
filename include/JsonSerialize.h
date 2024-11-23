#pragma once

#include <string>
#include "JsonArray.h"
#include "JsonObject.h"
#include "JsonValue.h"
#include <variant>

class JsonSerialize
{
public:
    static std::string Serialize(const JsonObject &obj);

    static std::string Serialize(const JsonArray &arr);

    static JsonValue Deserialize(const std::string &json);

private:

    static JsonValue ParseValue(const std::string &json, int &out_len);

    static JsonObject ParseObject(const std::string &json, int &out_len);

    static JsonArray ParseArray(const std::string &json, int &out_len);
};