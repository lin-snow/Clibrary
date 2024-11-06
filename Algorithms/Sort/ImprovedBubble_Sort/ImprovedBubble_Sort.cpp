#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    // 函数原型
    void ImprovedBubbleSort(int arr[], int n);

    // 测试数组
    int testarr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    // 数组长度
    int n = sizeof(testarr) / sizeof(testarr[0]);
    
    // 输出排序前的数组
    printf("Before Sort: \n");
    for (int i = 0; i < n; i++) printf("%d ",testarr[i] );

    printf("\n");

    // 进行进化版冒泡排序
    ImprovedBubbleSort(testarr, n);
    
    // 输出排序后的数组
    printf("After Sort: \n");
    for (int i = 0; i < n; i++) printf("%d ", testarr[i]);



    system("pause");
    return 0;
}

/* 优化思路；
        1. 提前终止循环，比如某个数组已经有序
        2. 记录最一次交换的位置，后面的元素已经有序
        3. 双向冒泡排序，在一次遍历中进行正向和方向两次冒泡排序
*/
void ImprovedBubbleSort(int arr[], int n) {
    int swapped = 1; // 是否发生了交换
    int bound = n - 1; // 有序区域的边界

    while (swapped) {
        swapped = 0;
        int newBound = 0; // 下一轮的边界

        // 正向冒泡排序找到最大值
        for (int i = 0; i < bound; i++) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swapped = 1; // 发生了交换
                newBound = i; // 更新边界
            }
        }

        
        if (!swapped) break; // 如果没有发生交换，说明数组已经有序

        bound = newBound; // 更新边界为新边界

        // 反向冒泡找到最小值
        for (int i = bound; i > 0; i--) {
            if (arr[i-1] > arr[i]) {
                int temp = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = temp;
                swapped  = 1; // 发生了交换
                newBound = i - 1; // 更新边界
            }
        }

        bound = newBound; // 更新边界为新的边界
    }
}