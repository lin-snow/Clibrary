#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;

typedef struct {
    KeyType key; //关键数据项
    // ... 其他数据项
} RecordType, RcdType;

typedef struct {
    RcdType * rcd; // 存储空间基址
    int length; // 当前长度
    int size; // 存储容量
} RcdSqList; // 记录的顺序表

int main() {
    system("cls");

    void InsertSort(RcdSqList &L); // 对顺序表L作直接插入排序

    system("pause");
    return 0;
}

void InsertSort(RcdSqList &L) {
    int i, j;
    for (i = 1; i < L.length; i++) {
        if (L.rcd[i+1].key < L.rcd[i].key) {
            L.rcd[0] = L.rcd[i+1]; // 先将记录保存在空闲的零号单元
            j = i + 1;
            do {
                j--;
                L.rcd[j+1] = L.rcd[j]; // 将i+1前面的数据往后面移，挪出一个合适的位置放L.rcd[0]
            } while (L.rcd[0].key <L.rcd[j-1].key); // 判断是否需要继续移动
            L.rcd[j] = L.rcd[0]; // 插入
        }
    }
}