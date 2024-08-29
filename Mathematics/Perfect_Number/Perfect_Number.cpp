#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* 清屏 */
    system("cls");
    /* 函数原型 */
    int isPerfectNumber(int num);
    
    int lowerLimit, upperLimit;

    /* 用户输入要查找的完数范围 */
    printf("请输入要查找的完数范围的上限和下限（ 用空格分隔 ）: ");
    scanf("%d %d", &lowerLimit, &upperLimit);

    printf("在范围 %d 到 %d 之间的完数有： \n", lowerLimit, upperLimit);

    /* 遍历范围内的每个数，判断是否是完数 */
    for (int i = lowerLimit ; i<= upperLimit; i++) {
        /* 调用函数判断该数是否为完数，如果是则输出 */
        if(isPerfectNumber(i)) {
            printf("%d\n",i);
        }
    }
    /* 暂停程序，查看结果 */
    system("pause");
    /* 结束程序，返回0 */
    return 0;
}

/* 函数定义 */
int isPerfectNumber(int num) {
    int sum = 1; /* 初始化为1，因为1是所有正整数的因子 */

    /* 从2遍历到num的平方根，找出所有因子 */
    for (int i =2; i * i <= num; i++) {
        /* 判断num能否被i整除 */
        if (num % i == 0) {
            /* num能被i整除，说明i和num/i为num的两个因数 */
            sum += i;
            /* 如果i不等于num/i,说明i和num/i是不同的因数，都需要加上 */
            if (i != num/i) {
                sum += num / i;
            }

            /* 如果因子的和等于num本身，则num是完数 */
            if (sum == num && num != 1) {
                return 1; // 是完数
            } else {
                return 0; //不是完数
            }
        }
    }
}