#include <iostream>
#include <string>
#include <stdexcept>

class stackEmpty {
    public:
        stackEmpty(): message() {}
        stackEmpty(const char* theMessage): message(theMessage) {}

        void outputMessage() {
            std::cout << message << std::endl;
        }

    private:
        std::string message;
};