#include <stdio.h>
#include <stdlib.h>

typedef enum Status {
    OK= 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef int KeysType;

typedef struct {
    KeysType * keys; // 关键字
                     // 其他数据项
} KeysRcdType; // 基数排序中的记录类型

typedef struct {
    KeysRcdType * rcd; // 0号位置哨兵
    int length; // 顺序表长度
    int size;   // 顺序表容量
    int digitNum; // 关键字位数
    int radix; // 关键字基数
} KeysSqList;

int main() {
    system("cls");

    void RadixPass(KeysRcdType rcd[], KeysRcdType rcd1[], int n, int i, int count[], int pos[], int radix);
    Status RadixSort(KeysSqList & L);


    system("pause");
    return 0;
}

void RadixPass(KeysRcdType rcd[], KeysRcdType rcd1[], int n, int i, int count[], int pos[], int radix) {
    // 对数组rcd中记录关键字的第i位计数，计算得到起始位置数组pos[]
    // 并按照pos数组将数组rcd中记录复制到数组rcd1
    int k, j;
    for (k = 1; k <= n; k++) count[rcd[k].keys[i]]++; // 对各种取值计数
    pos[0] = 1;
    for (j = 1; j < radix; ++j) pos[j] = count[j-1] + pos[j-1]; // 求起始位置
    for (k = 1; k <= n; ++k) { // 收集
        j = rcd[k].keys[i];
        rcd1[pos[j]++] = rcd[k]; // 复制记录，对应的起始位置加一
    }
}

Status RadixSort(KeysSqList & L) { // 对顺序表L进行顺序计数计数排序
    KeysRcdType * rcd1; // 开设同等大小的辅助空间用于复制数据
    int i = 0, j;
    int * count, * pos;
    count = (int*)malloc(L.radix * sizeof(int));
    pos = (int *)malloc(L.radix * sizeof(int));
    rcd1 = (KeysRcdType *)malloc((L.length + 1) * sizeof(KeysRcdType));
    if (NULL == count || NULL == pos || NULL == rcd1) return OVERFLOW;
    while (i < L.digitNum) {
        for (j = 0 ; j < L.radix; ++j) count[j] = 0 ; // 初始化
        if (0 == i % 2) // 对L.rcd进行一趟基数排序，结果存储rcd1
            RadixPass(L.rcd, rcd1, L.length, i++, count, pos, L.radix);
        else            // 对rcd1进行一趟基数排序，结果存入L.rcd
            RadixPass(rcd1, L.rcd, L.length, i++, count, pos, L.radix);
    }
    if ( 1 == L.digitNum % 2) // 排序后的结果在rcd1中，复制至L.rcd中 
        for (j = 1; j <= L.length; j++) L.rcd[j] = rcd1[j];
    free(count); free(pos); free(rcd1);
    return OK;
}