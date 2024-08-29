#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    // 函数原型
    void quicksort(int * arr, int left, int right);

    // 先有一个乱序的数组(作为全局变量，用于函数调用中使用)
    int a[10] = {10,8,6,4,2,3,5,7,9,1},k;

    // 调用函数进行快速排序
    quicksort(a,0,9);

    // 输出排序后的数组
    for (k=0;k<10;k++) printf("%3d ",a[k]);

    // 暂停程序查看输出结果
    system("pause");
    return 0;
}

// 函数定义
void quicksort(int * arr, int left, int right) {
    int i = left, j = right;
    int key = arr[i]; // 每次调用函数都把左边那个数设为基准

    if (left >= right) return; // 如果left 大于等于 right, 则返回空语句， 结束该函数

    while (i < j) {
        // 查找小于基准数key的位置并停下来，即为j
        while (i < j && arr[j] >= key) {
            j--;
        }

        // 将其赋值给arr[i]
        arr[i] = arr[j];

        // 查找大于基准数key的位置并停下来， 即为i
        while (i < j && arr[i] <= key) {
            i++;
        }

        // 将其付给上一个while中j停下来的位置
        arr[j] = arr[i];
    }

    // 此时i和j在同一个位置，把这个位置的值改为刚开始设置的基准值key
    arr[j] = key;

    quicksort(arr, left, i-1); // 对左边的进行快速排序
    quicksort(arr, i+1, right); // 对右边进行快速排序
}