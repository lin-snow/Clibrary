#include <stdio.h>
#include <stdlib.h>

int main() {
    // 清屏
    system("cls");
    // 函数原型
    int binary_search(int * arr,int len,int x);
    // 首先我们需要一个有序的数组,
    int arr[10] = {1,12,23,44,46,57,68,73,86,97};
    // 定义一个变量x，改变量中的值为你要查找的值
    int x = 23;
    // 定义一个索引变量index,用于接受查找函数的返回值
    int index;
    // 调用binary_search()进行查找
    index = binary_search(arr,10,x);
    // 判断是否找到x,如果找到,则输出，否则提示未找到
    if (index != -1) printf("the %d is found in the arr and the index is %d \n",x,index);
    else printf("%d could not be found in the array.\n",x);

    //暂停程序
    system("pause");
    return 0;
}

/* 
    arr为传入的有序数组的地址，
    len为该数组的长度，
    x为需要进行查找的数 
*/
int binary_search(int * arr, int len, int x) {
    // 初始化左右边界
    int left = 0;
    int right = len - 1;

    // 定义中间索引变量
    int mid;

    // 循环查找
    while (left <= right) {
        // 计算中间元素的索引
        mid = (left + right) / 2;

        // 比较中间元素和要查找的元素
        if (arr[mid] == x) {
            // 找到了，返回中间元素的索引
            return mid;
        } else if (arr[mid] < x) {
            // 要查找的元素在右边
            left = mid + 1;
        } else {
            // 要查找的元素在左边
            right = mid - 1;
        }
    }   

    // 未找到x, 返回 -1
    return -1;
}


