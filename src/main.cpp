#include "../include/JsonArray.h"
#include "../include/JsonSerialize.h"
#include <string>
#include <iostream>
#include "../include/JsonSerialize.h"
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream file("E:/MyProject/C++/XJson/src/test.json");

    std::ostringstream oss;
    oss << file.rdbuf();

    std::string str = oss.str();
    file.close();

    // std::cout << "json string: " << str << std::endl;

    JsonValue obj = JsonSerialize::Deserialize(str);
    // JsonValue obj = JsonSerialize::Deserialize("{\"name\":\"John\", \"age\":30, \"city\":\"New York\", \"jj\":[{\"ii\":1}, 12, false, \"hello\"]}");

    std::cout << JsonSerialize::Serialize(obj.ToObject()) << std::endl;

    // JsonObj::FromDoc("{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}");
    // JsonArray::FromDoc("[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]");
    return 0;
}
