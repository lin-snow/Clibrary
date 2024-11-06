#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    system("cls"); // 清屏

    int isPrime(int n); // 函数原型

    printf("Please input a number: ");
    int x = 0;
    scanf("%d", &x); // 输入待判断的数

    if (isPrime(x)) {
        printf("%d is Prime!\n", x);
    } else {
        printf("%d isn't Prime!\n", x);
    }

    system("pause");
    return 0;
}

int isPrime(int n) {
    // 判断是否小于等于1
    if ( n <= 1 ) return 0;

    // 判断是否为偶数
    if ( n % 2 == 0 ) return 0;

    // 从3开始，逐个检查输入的数能否3 到 n之间的奇数整除
    for(int i = 3; i <=  sqrt(n); i += 2) {
        if (n % i == 0) return 0; 
    }

    return 1;
}