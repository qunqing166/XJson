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

    JsonValue obj = JsonSerialize::Deserialize(str);

    std::cout << JsonSerialize::Serialize(obj.ToObject()) << std::endl;

    return 0;
}
