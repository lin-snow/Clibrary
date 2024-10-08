#include <stdio.h>
#include <stdlib.h>


typedef enum Status {
    OK = 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef char TElemType;

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild; // 左右孩子指针域
} BiTNode, *BiTree;

int main() {
    void InitBiTree(BiTree &T); // 创建一颗空二叉树
    BiTree MakeBiTree(TElemType e, BiTree L, BiTree R); // 创建一颗二叉树T，其中根节点的值为e，L和R分别作为左子树和右子树
    void DestroyBiTree(BiTree &T); // 销毁二叉树
    Status BiTreeEmpty(BiTree T); // 对二叉树判空。若空则返回TRUE，否则返回FALSE
    Status BreakBiTree(BiTree &T, BiTree &L, BiTree &R);  // 将一颗二叉树T分解成根、左子树和右子树三个部分
    Status ReplaceLeft(BiTree &T, BiTree &LT); // 替换左子树。若T非空，则用LT替换T的左子树，并用LT返回T的原有左子树
    Status ReplaceRight(BiTree &T, BiTree &RT); // 替换右子树。若T非空，则用RT替换T的右子树，并用RT返回T的原有右子树
    Status InOrderTraverse(BiTree T, Status (* visit)(TElemType e)); // 中序递归遍历二叉树
    BiTNode * GoFarLeft(BiTree T, LStack &S); // 从T结点出发,沿左分支走到底，沿途结点的指针入栈S，返回左下结点的指针
    void InorderTraverse_I(BiTree T, Status( * visit)(TElemType e)); // 中序非递归遍历
    int BiTreeDepth(BiTree T); // 二叉树深度
    void CountLeaf(BiTree T, int &count); // 二叉树的叶子结点计数

    return 0;
}

// 创建一颗二叉树T，其中根节点的值为e，L和R分别作为左子树和右子树
BiTree MakeBiTree(TElemType e, BiTree L, BiTree R) {
    BiTree t;
    t = (BiTree)malloc(sizeof(BiTree));
    if (t == NULL) return NULL;

    t->data = e; // 根结点的值为e
    t->lchild = L; // L作为t的左子树
    t->rchild = R; // R作为t的右子树

    return t;
}

void DestroyBiTree(BiTree &T) {
    if (T != NULL) {
        DestroyBiTree(T->lchild); // 递归销毁左子树
        DestroyBiTree(T->rchild); // 递归销毁右子树
        free(T); // 释放根结点
    }
}

int BiTreeDepth(BiTree T) {
    int depthLeft, depthRight;
    if (T == NULL) return 0;
    else {
        depthLeft = BiTreeDepth(T->lchild); // 求左子树的深度
        depthRight = BiTreeDepth(T->rchild); // 求右子树的深度
        return 1+(depthLeft > depthRight ? depthLeft : depthRight); // 左右子树深度的较大值+1
    }
}

void CountLeaf(BiTree T, int &count) {
    if (T != NULL) {
        if (T->lchild == NULL && T->rchild == NULL) count++; // 对叶子节点计数
        CountLeaf(T->lchild, count); // 对左子树进行递归计数
        CountLeaf(T->rchild, count); // 对右子树进行递归计数
    }
}

Status ReplaceLeft(BiTree &T, BiTree &LT) {
    BiTree temp;
    if (T == NULL) return ERROR; // 树为空
    temp = T->lchild;
    T->lchild = LT; // LT作为T的左子树
    LT = temp; // LT返回T的先前左子树
    return OK;
}

Status ReplaceRight(BiTree &T, BiTree &RT) {
    BiTree temp;
    if (T == NULL) return ERROR; // 数为空
    temp = T->rchild;
    T->rchild = RT; // RT作为T的右子树
    RT = temp; // RT返回T的先前右子树
    return OK;
}

// 中序遍历二叉树T，visit是对数据元素操作的应用函数
Status InOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    if (T == NULL) return OK;

    if (InOrderTraverse(T->lchild, visit) == ERROR) return ERROR; // 递归遍历T的左子树
    
    if (visit(T->data) == ERROR) return ERROR; // 访问节点的数据域
    
    return InOrderTraverse(T->rchild, visit); // 递归遍历T的右子树
}

BiTNode * GoFarLeft(BiTree T, LStack &S) {
    if (T == NULL) return NULL;
    while (T->lchild != NULL) {
        Push_LS(S, T);
        T= T->lchild;
    }
    return T;
}

void InorderTraverse_I(BiTree T, Status( * visit)(TElemType e)) {
    LStack S;
    InitStack_LS(S);
    BiTree p = GoFarLeft(T, S);
    while (p != NULL) {
        visit(p->data); // 访问结点
        if (p->rchild != NULL) {
            p = GoFarLeft(p->rchild, S); // 令p指向其右孩子为根的子树的最左下节点
        } else if (StackEmpty_LS(S) != TRUE) {
            Pop_LS(S, p); // 栈不为空时退栈
        } else {
            p = NULL;
        }
    }
}
