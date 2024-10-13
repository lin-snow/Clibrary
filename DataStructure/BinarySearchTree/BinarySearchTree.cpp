#include <stdio.h>
#include <stdlib.h>

typedef enum Status {
    OK = 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef struct RcdType {
    int key;
} RcdType;
typedef int KeyType;


typedef struct BSTNode {
    RcdType data; // 数据元素
    struct BSTNode * lchild, * rchild; // 左右孩子指针
} BSTNode, *BSTree;

// 构造一棵空的二叉查找树
Status InitBST(BSTree &T){} 

// 二叉查找树T存在，销毁树T
Status DestroyBST(BSTree &T);

// 若二叉查找树T中存在值为key的节点， 则返回该节点指针，否则返回NULL
BSTree SearchBST(BSTree T, KeyType key){
    if (T == NULL) return NULL;
    if (T->data.key == key) return T;
    if (T->data.key > key)
        return SearchBST(T->lchild, key); // 在左子树上继续查找
    return SearchBST(T->rchild, key); // 在右子树上继续查找
}

// 二叉查找树非递归查找
BSTree SearchBST_I(BSTree T, KeyType key) {
    while (T!= NULL) {
        if(T->data.key == key) return T;
        else if (T->data.key > key) T = T->lchild; // 在左子树中继续查找
        else T = T->rchild;
    }
    return NULL;
}

// 若二叉查找树T中不存在值为key的节点，则插入T
Status InsertBST(BSTree &T, RcdType e){
    if (T == NULL) { // 若二叉查找树是空树，则创建新插入的节点并作为根结点
        BSTNode * s;
        s = (BSTNode *)malloc(sizeof(BSTNode));
        if (s == NULL) return OVERFLOW;
        s->data = e; s->lchild = NULL; s->rchild = NULL;
        T = s;
        return TRUE;
    }

    // 插入节点的值小于根节点值，在左子树递归插入
    if (e.key < T->data.key) return InsertBST(T->lchild, e);
    // 插入节点的值大于根结点的值，在右子树递归插入
    if (e.key > T->data.key) return InsertBST(T->rchild, e);
    
    return FALSE; // e.key == T->data.key, 节点已经存在
}

// 删除节点操作
void DeleteNode (BSTree &p) {
    // 删除二叉查找树中的p节点，引用形参p的实参是要删除的p节点的双亲指向其的指针域
    BSTNode *q, *s;
    q = p; // 令q指向要删除的p节点
    if (p->rchild == NULL) { // 被删除的p节点的右子树为空
        p = p->lchild;
        free(q);
    } else if (p->lchild == NULL) { // 被删除的p节点的左子树为空
        p = p->rchild; // 置p节点的右子树为p节点的双亲节点的相应子树
        free(q);
    } else { // 左右子树均不为空
        s = p->lchild; //s指向p节点的左孩子
        while(s->rchild != NULL) {// 向右走到尽头，令s指向被删除节点的直接前驱
            q = s;
            s = s->rchild;
        }
        if (q == p) // s 节点是被删节点的左孩子
            q->lchild = s->lchild; // 删除s节点只需将其左子树置为q节点的左子树
        else q->rchild = s->lchild; // 删除s节点只需要将其右子树置为q节点的右子树
        free(s);
    }
}

// 若二叉查找树中存在值为key的节点则删除
Status DeleteBST(BSTree &T, KeyType key) {
    // 若二叉查找树T中存在值为key的节点， 则删除该节点，并返回TRUE; 否则返回FALSE
    if (T == NULL) return FALSE; // 不存在值为key的节点
    if (T->data.key == key) { // 找到值为key的节点
        DeleteNode(T);
        return TRUE;
    } else if (T->data.key > key)
        return DeleteBST(T->lchild, key); // 对子树递归并非返回结果

    return DeleteBST(T->rchild, key); // 对子树递归并返回结果
}
