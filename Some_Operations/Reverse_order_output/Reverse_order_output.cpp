#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* 清屏 */
    system("cls");
    /* 函数原型 */
    void reverse(int * arr, int len);
    void reverse_output(int * arr, int len);
    /* 首先定义两个整形数组arr1和arr2 */
    int arr1[10] = {9,8,7,6,5,4,3,2,1,0};
    int arr2[10] = {9,8,7,6,5,4,3,2,1,0};
    /* 调用函数将数组逆转 */
    reverse(arr1,10);
    /* 输出逆转后的数组 */
    for (int i = 0;i < 10;i++) printf("%2d ",arr1[i]);
    /* 递归逆序输出数组 */
    printf("\n");
    reverse_output(arr2, 10);
    /* 暂停程序，查看结果 */
    system("pause");
    return 0;
}

/* 将数组改为逆序 */
void reverse(int * arr, int len) {
    /* 定义两个指针，分别指向数组的首尾元素 */
    int i = 0;
    int j = len - 1;

    /* 循环交换数组中的元素 */
    while (i < j) {
        // 交换 i 和 j指向的元素
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        /* 更新 i 和 j */
        i++;
        j--;
    }
}

/* 递归逆序输出数组 */
void reverse_output(int * arr, int len) {
    /* 递归出口 */
    if (len == 0) {
        return;
    }

    /* 输出数组的最后一个元素 */
    printf("%d ",arr[len - 1]);

    /* 递归调用，逆序输出数组的剩余元素 */
    reverse_output(arr, len - 1);
}