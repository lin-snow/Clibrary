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

// 循环队列
typedef struct
{
    ElemType *elem; // 队列的基址
    int front; // 指向队头元素
    int rear; // 指向队尾元素的下一个位置
    int maxSize; // 队列最多可容纳的元素
    int length; // 队列当前元素的个数
} SqQueue; // 循环队列

int main()
{
    system("cls");

    Status InitQueue_Sq(SqQueue & Q, int size);   // 构造一个空队列，队列的容量为size
    Status DestroyQueue_Sq(SqQueue & Q);          // 销毁队列Q
    void ClearQueue_Sq(SqQueue & Q);              // 清空队列
    Status QueueEmpty_Sq(SqQueue Q);              // 若队列为空，则返回TRUE,否则返回FLASE
    int QueueLength_Sq(SqQueue Q);                // 返回队列中元素的个数，即队列的长度
    Status GetHead_Sq(SqQueue Q, ElemType & e);   // 若队列不为空，则用e返回队列中的头元素，否则返回ERROR
    Status EnQueue_Sq(SqQueue & Q, ElemType e);   // 在队尾插入新元素e
    Status DeQueue_Sq(SqQueue & Q, ElemType & e); // 若队列不为空，则删除队头的元素并用e返回其值，返回OK，否则返回ERROR

    system("pause");
    return 0;
}

Status InitQueue_Sq(SqQueue &Q, int size)
{
    Q.elem = (ElemType *)malloc(sizeof(ElemType) * size);
    if (Q.elem == NULL)
        return OVERFLOW;
    Q.front = 0;
    Q.rear = 0;
    Q.maxSize = size;
    Q.length = 0;
    return OK;
}

Status DestroyQueue_Sq(SqQueue &Q) {
    free(Q.elem);
    Q.elem = NULL;
    return OK;
}

void ClearQueue_Sq(SqQueue &Q) {
    Q.front = Q.rear = 0;
    Q.length = 0;
    return;
}           

Status QueueEmpty_Sq(SqQueue Q) {
    if (Q.front == Q.rear && Q.length == 0) return TRUE;
    else if (Q.front < 0 || Q.rear < 0) return OVERFLOW;
    else return FALSE;
}

int QueueLength_Sq(SqQueue Q) {
    return (Q.rear - Q.front + Q.maxSize)%Q.maxSize;
}

Status GetHead_Sq(SqQueue Q, ElemType &e) {
    if (QueueEmpty_Sq(Q) == TRUE || QueueEmpty_Sq(Q) == OVERFLOW) return ERROR;
    else if (QueueEmpty_Sq(Q) == FALSE) {
        e = Q.elem[Q.front];
        return OK;
    } 
}
Status EnQueue_Sq(SqQueue &Q, ElemType e) {
    // 队列是否已满
    if ((Q.rear + 1)%Q.maxSize == Q.front) return ERROR;

    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1)%Q.maxSize;

    return OK;
}
Status DeQueue_Sq(SqQueue &Q, ElemType &e) {
    if (QueueEmpty_Sq(Q) == TRUE || QueueEmpty_Sq(Q) == OVERFLOW) return ERROR;

    e = Q.elem[Q.front];
    Q.front = (Q.front + 1)%Q.maxSize;
    return OK;
}
