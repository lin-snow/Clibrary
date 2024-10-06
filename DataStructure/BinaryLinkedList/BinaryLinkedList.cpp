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
    Status InOrderTraverse(BiTree T, Status (* visit)(TElemType e));

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