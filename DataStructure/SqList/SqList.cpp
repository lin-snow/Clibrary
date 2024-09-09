#include <stdio.h>
#include <stdlib.h>

typedef enum Status
{
    OK = 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef int ElemType;

typedef struct SqList
{
    ElemType *elem; // 存储空间的基址
    int length;     // 当前长度
    int size;       // 存储容量
    int increment;  // 扩容的增量
} SqList;

int main()
{
    system("cls");

    Status InitList_Sq(SqList & L, int size, int inc);            // 初始化顺序表
    Status DestroyList_Sq(SqList & L);                            // 销毁顺序表L
    Status ClearList_Sq(SqList & L);                              // 将顺序表清空
    Status ListEmpty_Sq(SqList L);                                // 若顺序表为空表，则返回TRUE,否则返回FALSE
    int ListLength_Sq(SqList L);                                  // 返回顺序表中元素的个数
    Status GetElem_Sq(SqList L, int i, ElemType &e);              // 用e返回顺序表L中第i个元素的值
    int Search_Sq(SqList L, ElemType e);                          // 在顺序表L中顺序查找元素e，成功时返回该元素在顺序表中的第一次出现的位置
    Status visit(ElemType e);                                     // 访问元素函数
    Status ListTraverse_Sq(SqList L, Status(*visit)(ElemType e)); // 遍历顺序表L，依次对每个元素调用函数visit()
    Status PutElem_Sq(SqList & L, int i, ElemType e);             // 将顺序表L中的第i个元素赋值为e
    Status Append_Sq(SqList & L, ElemType e);                     // 在顺序表L表尾添加元素e
    Status DeleteLast_Sq(SqList & L, ElemType & e);               // 删除顺序表L的表尾元素，并用参数e返回其值

    system("pause");
    return 0;
}

Status InitList_Sq(SqList &L, int size, int inc)
{
    L.elem = (ElemType *)malloc(sizeof(ElemType) * size);
    if (L.elem == NULL)
        return OVERFLOW;

    L.length = 0;
    L.size = size;
    L.increment = 0;

    return OK;
}

Status DestroyList_Sq(SqList &L) {
    free(L.elem);
    L.elem = NULL;
    return OK;
}

Status ClearList_Sq(SqList &L) {
    L.length = 0;
    return OK;
}

Status ListEmpty_Sq(SqList L) {
    if (L.length == 0) return TRUE;
    else if (L.length < 0) return OVERFLOW;
    else return FALSE;
}

int ListLength_Sq(SqList L) {
    return L.length;
}

Status GetElem_Sq(SqList L, int i, ElemType &e) {
    if (i > L.length) return OVERFLOW;
    
    e = L.elem[i-1];
    return OK;
}

int Search_Sq(SqList L, ElemType e) {
    int i = 0;
    while (i < L.length) {
        if (L.elem[i] == e) return i;
    }

    return -1;
}

Status visit(ElemType e) {
    printf("%d\s", e);
}

Status ListTraverse_Sq(SqList L, Status (*visit)(ElemType e)) {
    for (int i = 0; i < L.length; i++) {
        visit(L.elem[i]);
    }
    return OK;
}
Status PutElem_Sq(SqList &L, int i, ElemType e) {
    if (i > L.length || i <= 0) return OVERFLOW;

    L.elem[i-1] = e;
    return OK;
}
Status Append_Sq(SqList &L, ElemType e) {
    // 是否已满
    ElemType * newBase;
    if (L.length == L.size) {
        newBase = (ElemType *)realloc(L.elem, sizeof(ElemType) * (L.size + L.increment));
        if (newBase == NULL) return OVERFLOW;
        L.size += L.increment;
    }
    L.elem = newBase;

    L.elem[L.length++] = e;
    return OK;
}

Status DeleteLast_Sq(SqList &L, ElemType &e) {
    if (ListEmpty_Sq(L) == TRUE) return ERROR;
    e = L.elem[L.length - 1];
    --L.length;
    return OK; 
}
