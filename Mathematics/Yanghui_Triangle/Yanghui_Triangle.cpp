#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* 清屏 */
    system("cls");
    /* 函数原型 */
    long long calculateCombination(int n,int r);
    /* 定义输出的行数 */
    int numRows;
    /* 用户输入要输出的行数 */
    printf("please input the number of row to output yanghui triangle: ");
    scanf("%d", &numRows);

    /* 打印杨辉三角 */
    for (int i =0; i< numRows; i++)
    {
        /* 打印每行前面的空格，使其呈三角形状 */
        for (int j = 0; j < numRows - i - 1; j++) {
            printf(" ");
        }

        /* 打印每个系数 */
        for (int j = 0; j <= i; j++) {
            /* 调用计算组合数的函数 */
            long long coef = calculateCombination(i, j);
            /* 打印系数，保持对对齐 */
            printf("%3lld", coef);
        }
        /* 换行 */
        printf("\n"); 
    }
    /* 暂停程序，查看结果 */
    system("pause");
    /* 程序结束，返回0 */
    return 0;
}

long long calculateCombination(int n, int r) {
    /* 使用递推公式计算组合数 */
    /* 递归终止条件 */
    if (r == 0 || r == n) {
        return 1;
    } else {
        /* C(n , r) = C(n-1, r-1) + C(n-1, r) */
        return calculateCombination(n - 1, r - 1) + calculateCombination(n - 1, r);
    }
}