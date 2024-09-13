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
    
    void ShellSort(RcdSqList &L);

    system("pause");
    return 0;
}


void ShellSort(RcdSqList &L) {
    int i, j, k = 0;
    int increment = L.length;
    do {
        increment = increment / 3 + 1; // 增量序列
        for (i = increment+1; i <= L.length; i++) {
            if (L.rcd[i].key < L.rcd[i-increment].key) { // i的key小于前面的某一个key
                L.rcd[0] = L.rcd[i]; // 暂存到零号位
                for (j = i-increment; j > 0 && L.rcd[0].key < L.rcd[j].key; j-=increment)
                    L.rcd[j+increment] = L.rcd[j]; // 后移查找插入位置
                L.rcd[j+increment] = L.rcd[0]; // 插入
            }
        }
    } while (increment > 1); // 增量不为1时执行循环
}


