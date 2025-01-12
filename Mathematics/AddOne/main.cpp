#include <iostream>
#include <string>



int main() {
    system("cls");
    system("chcp 65001");
    std::string inputNum;

    int addone(int (&mydigit)[], int curIndex);

    std::cout << "请输入数字： " ;
    std::cin >> inputNum;

    // 将string转换为字符数组
    int digits[inputNum.size() + 2] = {0};
    int index = 1;
    int digitsLen = inputNum.size();
    for (char c : inputNum) {
        if (c != '-') {
            digits[index++] = c - '0';
        } else {
            std::cout << "请输入非负数！"  << std::endl;
        }
        
        // std::cout << digits[index - 1] << std::endl;
    } 

    addone(digits, digitsLen);

    std::cout << "最终结果为： " ;
    for (int i = 0; i < digitsLen + 1; i++) {
        if (i == 0 && digits[i] == 0) {
            continue;
        } else {
            std::cout << digits[i];
        }
    }
        

    return 0;
}

int addone(int (&mydigit)[], int curIndex) {
    if (curIndex == 0) {
        mydigit[curIndex] = 1;
        return 0;
    }

    if (mydigit[curIndex] < 9) {
        mydigit[curIndex]++;
        return 0;
    } else if (mydigit[curIndex] == 9) {
        mydigit[curIndex] = 0;
        return addone(mydigit,--curIndex);
    } else {
        return -1;
    }

}