#include "../include/JsonArray.h"
#include "../include/JsonSerialize.h"
#include <string>
#include <iostream>
#include "../include/JsonSerialize.h"
#include <fstream>
#include <sstream>
#include <chrono>

class Timer
{
public:

    Timer()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<float>(end_time - start_time);
        std::cout << "Time elapsed: " << duration.count() * 1000 << " microseconds" << std::endl;
    }

private:

    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

void Test()
{
    

    std::ifstream file("E:/MyProject/C++/XJson/test/test.json");

    std::ostringstream oss;
    oss << file.rdbuf();

    std::string str = oss.str();
    file.close();

    Timer timer;
    JsonValue obj = JsonSerialize::Deserialize(str);

    std::cout << JsonSerialize::Serialize(obj.ToObject()) << std::endl;
}

int main()
{

    Test();

    return 0;
}
