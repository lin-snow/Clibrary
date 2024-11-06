#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    int i, j, k, n = 10;
    // 有一个乱序的数组，其中有n个数，n=10
    int arr[10] = {33,22,44,55,66,11,99,88,77,100};

    // 冒泡排序（从小到大）
    for (i=1; i<n-1; i++)
        for (j=0; j<n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }

    // 输出排序结果
    for (k=0; k<10; k++) printf("%2d ", arr[k]);

    system("pause");
    return 0;
}
