#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    // 函数原型
    void SelectionSort(int * arr, int n);

    // 定义一个数组
    int arr[] = {1, 5, 3, 2, 4};

    // 排序前
    printf("Before Sort: \n");
    for (int i = 0; i < 5; i++) {
        printf("%2d ", arr[i]);
    }

    printf("\n");

    // 选择排序
    SelectionSort(arr, 5);

    // 排序后
    printf("After Sort: \n");
    for (int i = 0; i < 5; i++) {
        printf("%2d ", arr[i]);
    }

    system("pause");
    return 0;
}

void SelectionSort(int * arr, int n) {
    for (int i = 0; i < n-1; i++) {
        // 初始化最小元素的索引
        int minIndex = i;

        // 从 i+1 开始遍历未排序序列，找到最小元素
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // 将最小元素与未排序的第一个元素交换位置
        if (i != minIndex) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}