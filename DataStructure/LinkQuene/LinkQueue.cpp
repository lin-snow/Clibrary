#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef enum Status {
    ERROR = 0,
    SUCCESS = 1
} Status;

typedef struct Node {
    ElemType data;
    struct Node* next;
} Node;

typedef struct LQueue {
    Node* front;
    Node* rear;
    int length;
} LQueue;

int main() {
    system("cls");
    
    // 函数原型
    Status InitLQueue(LQueue* Q); // 初始化队列
    Status ClearLQueue(LQueue* Q); // 清空队列
    Status DestroyLQueue(LQueue* Q); // 销毁队列
    Status IsEmptyLQueue(const LQueue* Q); // 检查队列是否为空
    Node* GetHeadNode(LQueue* Q); // 获取队列头元素
    Node* GetRearNode(LQueue* Q); // 获取队列尾元素
    Status EnLQueue(LQueue* Q, ElemType* e); // 入队
    Node* DeLQueue(LQueue* Q, ElemType* e); // 出队
    int GetLength(LQueue* Q); // 获取队列长度
    Status printLQueue(LQueue* Q); // 打印队列

    system("pause");
    return 0;
}

// 初始化队列
Status InitLQueue(LQueue* Q) {
    Q->front = NULL;
    Q->rear = NULL;
    Q->length = 0;

    if (Q->front == NULL && Q->rear == NULL && Q->length == 0) {
        return SUCCESS;
    }
}

// 检查队列是否为空
Status IsEmptyLQueue(const LQueue* Q) {
    if (Q->length == 0 && Q->front == NULL && Q->rear == NULL) {
        return SUCCESS; // 为空
    } else {
        return ERROR; // 不为空
    }
}

// 获取队列头元素
Node* GetHeadNode(LQueue* Q) {
    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == SUCCESS) {
        printf("The LQueue is Empty!\n");
        return NULL;
    }

    return Q->front;
}

// 获取队列尾元素
Node* GetRearNode(LQueue* Q) {
    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == SUCCESS) {
        printf("The LQueue is Empty!\n");
        return NULL;
    }

    return Q->rear;
}

// 清空队列
Status ClearLQueue(LQueue* Q) {
    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == SUCCESS) {
        printf("The LQueue is Empty!\n");
        return SUCCESS;
    }

    // 清空队列
    Node* FreePtr = Q->front;
    while(Q->front != NULL) {
        Node* tempPtr = FreePtr->next;
        free(FreePtr);
        FreePtr = tempPtr;
    }

    // 修改队列信息
    Q->front = NULL;
    Q->rear = NULL;
    Q->length = 0;

    return SUCCESS;
}

// 销毁队列
Status DestroyLQueue(LQueue* Q) {
    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == ERROR) {
        // 清空队列
        Node* FreePtr = Q->front;
        while(Q->front != NULL) {
            Node* tempPtr = FreePtr->next;
            free(FreePtr);
            FreePtr = tempPtr;
        }
    }

    // 销毁队列
    free(Q);
    Q = NULL;
    return SUCCESS;
}

// 获取队列长度
int GetLength(LQueue* Q) {
    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == SUCCESS) {
        return 0;
    }

    Node* Counter = Q->front;
    int length = 0;

    while (Counter != NULL) {
        length++; // 计数加一
        Counter = Counter->next; // 移动到下一个结点
    }

    if (length == Q->length) {
        return length;
    } else {
        perror("The LQueue has wrong!\n");
        return -1;
    }
}

// 入队
Status EnLQueue(LQueue* Q, ElemType* e) {
    // 数据检查
    if (Q == NULL || e == NULL) {
        perror("The LQueue or the data has wrong!\n");
        return ERROR;
    }

    // 创建结点
    Node* MyNode = (Node*)malloc(sizeof(Node)); 
    if (MyNode == NULL) {
        perror("create failed!\n");
        return ERROR;
    }

    MyNode->data = *e;

    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == SUCCESS) {
        Q->front = MyNode;
        Q->rear = MyNode;
        Q->length++;
    } else {
        Q->rear->next = MyNode;
        Q->rear = MyNode;
        Q->length++;
    }
    return SUCCESS;
}

// 出队
Node* DeLQueue(LQueue* Q, ElemType* e) {
    // 检查队列是否为空
    if (IsEmptyLQueue(Q) == SUCCESS) {
        printf("The Queue is Empty!\n");
        return NULL;
    }

    // 将队尾的节点出队
    Node* SearchPtr = Q->front;
    while (SearchPtr != Q->rear) {
        SearchPtr = SearchPtr->next;
    }

    Node* tempPtr = Q->rear;
    SearchPtr->next = NULL;
    Q->rear = SearchPtr;

    return tempPtr;
}

// 遍历队列
Status printLQueue(LQueue* Q) {
    // 检查队列是否为空
    if (IsEmptyLQueue) {
        printf("The Queue is Empty!\n");
        return ERROR;
    }

    Node* currentNode = Q->front;
    while (currentNode != NULL) {
        printf("%2d \n", currentNode->data);
        currentNode->next;
    }
    return SUCCESS;
}

