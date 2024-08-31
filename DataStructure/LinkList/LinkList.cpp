#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Index;

// 定义链表结点
typedef struct Node {
    // 数据域
    int data;
    // 指针域
    struct Node * prev;
    struct Node * next;
} Node;

// 定义链表 
typedef struct LinkList {
    // 头结点
    Node * Head; // 链表中第一个结点的地址
    // 尾结点
    Node * Tail; // 链表中最后一个结点的地址
    // 链表信息
    int LinkList_Size;  // 链表中结点的数量
} LinkList;


int main() {
    system("cls"); // 清屏

    // 函数原型
    _Bool isLinkListEmpty(LinkList* LinkList); // 判断链表是否为空函数
    _Bool isLoop(LinkList* LinkList); // 判断链表是否成环
    void InitLinkList(LinkList* LinkList); // 链表初始化函数
    void InitNode(Node* Node); // 结点初始化函数
    void AppendUniNode(LinkList* LinkList); // 单向链表结点创建函数
    void InsertUniNode(LinkList* LinkList, Node* newNode); // 单向链表结点插入函数
    void AppendBiNode(LinkList* LinkList); // 双向链表结点创建函数
    void InsertBiNode(LinkList* LinkList, Node* newNode); // 双向链表结点插入函数
    void FreeLinkList(LinkList* LinkListToFree); // 释放链表函数
    void oeswap(LinkList* LinkList); // 单向链表奇偶调换
    Node* FindMidNode(LinkList* LinkList); // 找到链表的中间结点
    Node* GetNode(LinkList* LinkList, Index nodeIndex); // 获取某个位置的结点 
    Index Where(LinkList* LinkList, Node* node2find); // 查找结点在链表中的位置

    // 创建一个单向链表
    LinkList* UniLinkList = (LinkList*)malloc(sizeof(LinkList));

    // 创建一个双向链表
    LinkList* BiLinkList = (LinkList*)malloc(sizeof(LinkList));

    // 创建循环链表
    LinkList* LoopLinkList = (LinkList*)malloc(sizeof(LinkList));

    system("pause");
    return 0;
}

// 链表初始化
void InitLinkList(LinkList* LinkList) {
    LinkList->Head = NULL; // 头结点为空
    LinkList->Tail = NULL; // 尾结点为空
    LinkList->LinkList_Size = 0; // 结点数为0
}

// 结点初始化
void InitNode(Node* Node) {
    Node->prev = NULL;
    Node->next = NULL;
}

// 判断链表是否为空
_Bool isLinkListEmpty(LinkList* LinkList) {
    if (LinkList->LinkList_Size <= 0 && LinkList->Head == NULL && LinkList->Tail == NULL) {
        return true;
    } else {
        return false;
    }
}

// 获取某个位置的结点
Node* GetNode(LinkList* LinkList, Index nodeIndex) {
    if(isLinkListEmpty(LinkList)) {
        perror("The LinkList is empty!");
        return NULL;
    }

    if(nodeIndex > LinkList->LinkList_Size) {
        perror("Please input a correct node index!");
        return NULL;
    }

    Index temp = 0;
    Node* nodePTR = LinkList->Head;
    while(++temp < nodeIndex) nodePTR = nodePTR->next;
    return nodePTR;
} 

// 查看某个结点在链表中的位置
Index Where(LinkList* LinkList, Node* node2find) {
    if(isLinkListEmpty(LinkList)) {
        perror("The LinkList is empty!");
        return -1;
    }

    Index nodeIndex = 1;
    Node* nodePTR = LinkList->Head;
    do {
        if(nodePTR == node2find) {
            return nodeIndex;
        } else if (nodeIndex > LinkList->LinkList_Size) {
            printf("The Node is not exist in the LinkList!\n");
            return -1;
        } else {
            nodePTR = nodePTR->next;
        }
    } while(nodeIndex++);
} 

// 单向链表插入结点
void InsertUniNode(LinkList* LinkList, Node* newNode) {
    if (isLinkListEmpty(LinkList)) { 
        /* 链表为空 */
        LinkList->Head = newNode; // 链表头指针指向新结点 
        LinkList->Tail = newNode; // 链表尾指针指向尾结点
        LinkList->LinkList_Size++; // 链表结点数加一
        return;
    } else {
        /* 链表不为空，插入到末尾 */
        LinkList->Tail = newNode;
        LinkList->LinkList_Size++;
        return;
    }
}

// 单向链表结点创建函数
void AppendUniNode(LinkList* LinkList) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 给结点创建一个内存空间
    if (newNode == NULL) {
        perror("Creating new node failed!!!"); // 输出错误信息
        return;
    }

    InitNode(newNode); // 初始化结点

    InsertUniNode(LinkList, newNode); // 加入链表

    return;
}

// 双向链表结点插入
void InsertBiNode(LinkList* LinkList, Node* newNode) {
    
}




