#include "../include/JsonValue.h"
#include "../include/JsonArray.h"
#include "../include/JsonObject.h"

JsonArray JsonValue::ToArray() const
{
    return std::get<std::vector<JsonValue>>(value);  
}

JsonObject JsonValue::ToObject() const
{
    return std::get<std::map<std::string, JsonValue>>(value);
}

void JsonValue::SetValue(const JsonArray &value)
{
    type = JsonType::Array;
    this->value = value.ToArray();
}

void JsonValue::SetValue(const JsonObject &value)
{
    type = JsonType::Object;
    this->value = value.ToMap();
}
