#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    // 函数原型
    int gcd(int x, int y);
    int lcm(int x, int y);
    int RecursionGCD(int x, int y);
    int RecursionLCM(int x, int y);

    // 输入两个数，分别为x 和 y
    printf("Please input two numbers: ");
    int x, y;
    scanf("%d %d", &x, &y);

    /* 调用辗转相除法函数求最大公约数和最小公倍数 */
    printf("The Greatest common divisor is %d and Least common multiple is %d .\n",gcd(x,y),lcm(x,y));
    /* 调用递归函数去最大公约数和最小公倍数 */
    printf("The Greatest common divisor is %d and Least common multiple is %d .\n",RecursionGCD(x,y),RecursionLCM(x,y));
    /* 暂停程序，查看结果 */
    system("pause");
    /* 程序结束，返回0 */
    return 0;

}

// 辗转相除法求最大公约数
int gcd(int x, int y) {
    // 循环直到y为0
    while (y != 0) {
        int temp = x % y; // 余数
        x = y; 
        y = temp;
    }
    // 返回最大公约数
    return x; 
}

// 辗转相除法求最小公倍数
int lcm(int x, int y) {
    // 返回最小公倍数(两数乘积除以最大公约数)
    return x * y / gcd(x, y);
}

// 递归求最大公约数
int RecursionGCD(int x, int y) {
    if (y == 0) {
        return x;
    } else {
        return RecursionGCD(y, x % y);
    }
}

// 递归求最小公倍数
int RecursionLCM(int x, int y) {
    // 返回最小公倍数(两数乘积除以最大公约数)
    return x * y / RecursionGCD(x, y);
}



