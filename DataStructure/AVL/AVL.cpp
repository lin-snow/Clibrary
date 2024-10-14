#include <stdio.h>
#include <stdlib.h>

#define LH +1 // 左子树比右子树高，简称左高
#define EH 0 // 左、右子树等高，简称等高
#define RH -1 // 右子树比左子树高，简称右高 

typedef enum Status {
    OK = 1, 
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef int RcdType;

typedef struct BBSTNode {
    RcdType data;
    int bf; // 结点平衡因子
    struct BBSTNode *lchild, *rchild;
} * BBSTree; // 平衡二叉树


// 右旋调整
void R_Rotate(BBSTree &p) { // 对最小失衡子树p作右旋调整
    BBSTree lc = p->lchild; // lc指向p节点的左孩子
    p->lchild = lc->rchild; // lc节点的右子树置为p节点的左子树
    lc->rchild = p;         // 置p节点（原根节点）为lc节点的右孩子
    p = lc;                 // p指向新的根节点
}

// 左旋调整
void L_Rotate(BBSTree &p) { // 对最小失衡子树p作左旋调整
    BBSTree rc = p->rchild; // rc指向p节点的右子树
    p->rchild = rc->lchild; // rc节点的左子树置为p节点的右子树
    rc->lchild = p;         // 置p节点（原根节点）为rc节点的左孩子
    p = rc;                 // p指向新的根结点
}

void LeftBalance(BBSTree &T) { // 实现对树T的左平衡处理
    BBSTree lc, rd; 
    lc = T->lchild; // lc指向T的左孩子
    switch(lc->bf) { // 检查T的左子树的平衡因子，并做相应的处理
        case LH: // LL型，需做右旋调整
            T->bf = lc->bf = EH; R_Rotate(T); break;
        case RH: // 新节点插入在T的左孩子的右子树上属于LR型，做双旋处理
            rd = lc->rchild;
            switch(rd->bf) { // 修改T及其左孩子的平衡因子
                case LH: T->bf = RH; lc->bf = EH; break;
                case EH: T->bf = lc->bf = EH; break;
                case RH: T->bf = EH; lc->bf = LH; break;
            }
            rd->bf = EH;
            L_Rotate(T->lchild); // 对T的左子树做左旋调整
            R_Rotate(T);
            break;
    }

}

Status InsertAVL(BBSTree &T, RcdType e, Status &taller) {
    
}