#include <iostream>
#include <vector>

// 合并两个有序数组的函数
void Merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建两个临时数组
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    // 将数组复制到临时数组
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    // 合并临时数组回到原数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++]; 
        }
    }

    // 复制剩余的元素
    while ( i < n1 ) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] == rightArr[j++];
    }
}

// 递归的归并排序函数
void MSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 递归地对左右两个子数组进行排序
        MSort(arr, left, mid);
        MSort(arr, mid + 1, right);

        // 合并排序后的两个子数组
        Merge(arr, left, mid ,right);
    }
}

// 主函数， 调用MSort进行排序
void MergeSort(std::vector<int>& arr) {
    if  (arr.size() > 1) {
        MSort(arr, 0, arr.size() - 1);
    }
}

int main() {
    
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "给定数组: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;

    // 调用MergeSort进行排序
    MergeSort(arr);

    std::cout << "排序后的数组: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}