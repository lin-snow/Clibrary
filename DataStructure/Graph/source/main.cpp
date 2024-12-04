//#pragma execution_character_set("gbk") // 使用vs编译时使用的编码
#include <iostream>
#include <string>
#include <cfloat>
#include <windows.h>
#include "./Headers/Graph.h"
#include "./Headers/test.hpp"

int main() {
    system("cls"); // 清屏
    SetConsoleOutputCP(65001); // 设置控制台输出为UTF-8编码 (默认g++编译时使用)

    testGraph();

    return 0;
}




