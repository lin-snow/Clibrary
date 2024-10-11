#include <iostream>
#include <string>
#include <stdexcept>

class illegalIndex {
    public:
        illegalIndex(): message("Illegal Index") {} // 默认构造函数
        illegalIndex(char * theMessage): message(theMessage) {} // 带参数的构造函数

        void outputMessage() { // 输出信息
            std::cout << message << std::endl;
        }
    private:
        std::string message;
};