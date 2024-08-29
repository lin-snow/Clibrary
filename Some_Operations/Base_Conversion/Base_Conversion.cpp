#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* 清屏 */
    system("cls");
    /* 函数原型 */
    void Recursion_tobinary(int num);
    /* 定义一个变量,存放需要转换的十进制数 */
    int n;
    printf("Please input a number : ");
    scanf("%d",&n);
    Recursion_tobinary(n);

    /* 暂停程序，查看结果 */
    printf("\n");
    system("pause");
    return 0;
}

/* 使用递归的方式输出一个数的二进制形式 */
void Recursion_tobinary(int num)
{
    if (num == 0)
    {
        return;
    }

    // 递归调用,通过整除2来去除最低位
    Recursion_tobinary(num / 2);

    // 输出当前最低位的二进制表示
    printf("%d", num % 2);
}