#include "../include/JsonSerialize.h"

std::string JsonSerialize::Serialize(const JsonObject &obj)
{
    std::string result = "{";

    for (auto &[key, value] : obj.ToMap())
    {
        switch (value.Type())
        {
        case JsonValue::JsonType::Object:
            result += "\"" + key + "\":" + Serialize(value.ToObject());
            break;
        case JsonValue::JsonType::Array:
            result += "\"" + key + "\":" + Serialize(value.ToArray());
            break;
        case JsonValue::JsonType::String:
            result += "\"" + key + "\":\"" + value.ToString() + "\"";
            break;
        case JsonValue::JsonType::Int:
            result += "\"" + key + "\":" + std::to_string(value.ToInt());
            break;
        case JsonValue::JsonType::Double:
            result += "\"" + key + "\":" + std::to_string(value.ToDouble());
            break;
        case JsonValue::JsonType::Bool:
            result += "\"" + key + "\":" + (value.ToBool() ? "true" : "false");
            break;
        case JsonValue::JsonType::Null:
            result += "\"" + key + "\":null";

            break;
        default:
            break;
        }
        result += ",";
    }

    if (result.size() > 1)
    {
        result.pop_back();
    }
    result += "}";
    return result;
}
std::string JsonSerialize::Serialize(const JsonArray &arr)
{
    std::string result = "[";

    for (auto &value : arr.ToArray())
    {
        switch (value.Type())
        {
        case JsonValue::JsonType::Object:
            result += Serialize(value.ToObject());
            break;
        case JsonValue::JsonType::Array:
            result += Serialize(value.ToArray());
            break;
        case JsonValue::JsonType::String:
            result += "\"" + value.ToString() + "\"";
            break;
        case JsonValue::JsonType::Int:
            result += std::to_string(value.ToInt());
            break;
        case JsonValue::JsonType::Double:
            result += std::to_string(value.ToDouble());
            break;
        case JsonValue::JsonType::Bool:
            result += (value.ToBool() ? "true" : "false");
            break;
        case JsonValue::JsonType::Null:
            result += "null";
            break;
        default:
            break;
        }
        result += ",";
    }
    if (result.size() > 1)
    {
        result.pop_back();
    }
    result += "]";
    return result;
}

JsonValue JsonSerialize::Deserialize(const std::string &json)
{
    int len = 0;
    while (1)
    {
        if (json[len] == '{')
        {
            std::string str = json.substr(len);
            return ParseObject(str, len);
        }
        else if (json[len] == '[')
        {
            return ParseArray(json.substr(len), len);
        }
        else if (len >= json.size())
        {
            return JsonValue();
        }
        else
        {
            len++;
        }
    }
}

JsonValue JsonSerialize::ParseValue(const std::string &json, int &out_len)
{
    JsonValue value;

    for (int i = 0; i < json.size(); ++i)
    {
        if (json[i] == ' ')
            continue;

        if (json[i] == '{')
        {
            int len = 0;
            std::string str = json.substr(i);
            value = ParseObject(str, len);
            out_len = i + len;
            return value;
        }
        else if (json[i] == '[')
        {
            int len = 0;
            std::string str = json.substr(i);
            value = ParseArray(str, len);
            out_len = i + len;
            return value;
        }
        else
        {
            int word_start = i;
            for (int j = i; j < json.size(); ++j)
            {
                switch (json[j])
                {
                case ',':;
                case '}':;
                case ']':
                    std::string word = json.substr(word_start, j - word_start);

                    int s = 0;
                    int e = word.size() - 1;
                    while(word[s] == ' ' || word[s] == '\n')s++;
                    while(word[e] == ' ' || word[e] == '\n')e--;
                    word = word.substr(s, e - s + 1);   

                    if (word == "true")
                    {
                        value = true;
                    }
                    else if (word == "false")
                    {
                        value = false;
                    }
                    else if (word == "null")
                    {

                    }
                    else if (word[0] == '"' && word[word.size() - 1] == '"')
                    {
                        value = word.substr(1, word.size() - 2);
                    }
                    else if (word.find('.') != std::string::npos)
                    {
                        value = std::stod(word);
                    }
                    else
                    {
                        value = std::stoi(word);
                    }
                    out_len = j;
                    return value;
                }
            }
        }
    }
    return value;
}

JsonObject JsonSerialize::ParseObject(const std::string &json, int &out_len)
{
    out_len = 0;
    JsonObject obj;

    std::string key;
    std::string value;

    int state = 0;

    int word_start = 0;

    for (int i = 0; i < json.size(); ++i)
    {
        if (state == 0)
        {
            if (json[i] == '{')
            {
                state = 1;
            }
        }
        else if (state == 1)
        {
            if (json[i] == '"')
            {
                word_start = i + 1;

                for (int j = i + 1; j < json.size(); ++j)
                {
                    if (json[j] == '"')
                    {
                        key = json.substr(word_start, j - word_start);
                        i = j;
                        break;
                    }
                }
            }
            else if (json[i] == ':')
            {
                int len = 0;

                value = json.substr(i + 1);

                JsonValue v = ParseValue(value, len);

                obj.Insert(key, v);

                i += len;
                state = 2;
            }
        }
        else if (state == 2)
        {
            if (json[i] == ',' || json[i] == '}')
            {
                if (json[i] == '}')
                {
                    out_len = i + 1;
                    return obj;
                }
                state = 1;
                while (json[i] == ' ')
                    i++;
            }
        }
    }

    return obj;
}

JsonArray JsonSerialize::ParseArray(const std::string &json, int &out_len)
{
    JsonArray arr;

    std::string value;

    int state = 0;

    int word_start = 0;

    for (int i = 0; i < json.size(); ++i)
    {
        if (state == 0)
        {
            if (json[i] == '[')
            {
                state = 1;
                int len = 0;
                std::string str = json.substr(i + 1);
                arr.Add(ParseValue(str, len));
                i += len - 1;
            }
        }
        else if (state == 1)
        {
            if (json[i] == ',')
            {
                int len = 0;
                std::string str = json.substr(i + 1);
                arr.Add(ParseValue(str, len));
                i += len;
            }
            else if (json[i] == ']')
            {
                out_len = i;
                break;
            }
        }
    }

    return arr;
}
