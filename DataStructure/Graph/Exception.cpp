#ifndef EXCEPTION_CPP
#define EXCEPTION_CPP

#include <iostream>
#include <string>
#include <stdexcept>
#include "Exception.cpp"

class illegalParameterValue {
    public:
        illegalParameterValue(): // 默认构造函数
            message("Illegal parameter value") {}
        illegalParameterValue(const std::string & theMessage)
            : message(theMessage) {} // 带参数的构造函数

        void outputMessage() { 
            std::cout << message << std::endl;
        }
    private:
        std::string message;
};

#endif