typedef int RcdType;
typedef int KeyType;

typedef enum Status {
    OK = 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef struct {
    RcdType *  rcd; // 堆基址
    int n; // 堆长度
    int size; // 堆容量
    int tag; // 小顶堆与大顶堆的标志：tag = 0时为小顶堆， tag = 1时为大顶堆
    int (* prior)(KeyType, KeyType); // 函数变量, 用于关键字优先级比较
} Heap; // 堆类型

int greatPrior(int x, int y) {return x >= y;} // 大顶堆优先函数
int lessPrior(int x, int y) {return x <= y;} // 小顶堆优先函数


Status InitHeap(Heap &H, int size, int tag, int (* prior)(KeyType, KeyType));

// prior为相应的优先函数
// 初建最大容量为size的空堆H, 当tag 为0或1时分别表示小顶堆和大顶堆
void MakeHeap(Heap &H, RcdType * E, int n, int size, int tag, int (* prior)(KeyType, KeyType));

// 销毁堆H
Status DestroyHeap(Heap &H); 

// 对堆H中位置为pos的节点做筛选，将以pos为根的子树调整为子堆
void ShiftDown(Heap &H, int pos);

Status InsertHeap(Heap &H, RcdType e); // 将e插入堆
Status RemoveFirstHeap(Heap &H, RcdType &e); // 删除堆H的堆顶节点， 并用e将其返回
Status RemvoeHeap(Heap &H, int pos, RcdType &e); // 删除位置pos的节点， 用e返回其值


Status swapHeapElem(Heap &H, int i, int j) {
    // 交换堆h中的第i节点和第j节点
    RcdType t;
    if (t <= 0 || i > H.n || j <= 0 || j > H.n) return ERROR;

    t = H.rcd[i]; H.rcd[i] = H.rcd[j]; H.rcd[j] = t;
    return OK;
}

void ShiftDown(Heap &H, int pos) {
    int c, rc;
    while (pos <= H.n/2) { // 若c为pos结点的叶子结点， 循环结束
        c = pos * 2;    // c为pos结点的左孩子位置
        rc = pos * 2 + 1; // rc为pos结点的右孩子位置
        if (rc <= H.n && H.prior(H.rcd[rc], H.rcd[c]))
            c = rc; // 若c为pos结点的左，右孩子中较优先者的位置
        if (H.prior(H.rcd[pos], H.rcd[c]))
            return; // 若pos结点较优先，则筛选结束
        swapHeapElem(H, pos, c); // 否则pos和较优先者c交换位置
        pos = c; // 继续向下调整
    }
}

Status InsertHeap(Heap &H, RcdType e) {
    // 将节点e插入至堆H中
    int curr;
    if (H.n >= H.size-1) return ERROR; // 堆已满，插入失败
    curr = ++H.n; H.rcd[curr] = e; // 将插入元素加到堆尾
    while (curr != 1 && H.prior(H.rcd[curr], H.rcd[curr/2])) { // 非根且大于父节点
        swapHeapElem(curr, curr/2);
        curr /= 2;
    }

    return OK;
}

Status RemoveFirstHeap(Heap &H, RcdType &e) {
    // 删除堆H的堆顶节点， 并用e将其返回
    if (H.n <= 0) return ERROR;
    e = H.rcd[1];
    swapHeapElem(H, 1, H.n); H.n--; // 交换堆顶与堆尾节点，堆长度减一
    if (H.n > 1) ShiftDown(H, 1); // 从堆顶位置向下筛选
    return OK;
}

void MakeHeap(Heap &H, RcdType * E, int n, int size, int tag, int (* prior)(KeyType, KeyType)) {
    // 用E建长度为n的堆H，容量为size, 当tag 为0或1时分别表示小顶堆和大顶堆
    int i;
    H.rcd = E; // E[1..n]是堆的n个起点，0号单元闲置
    H.n = n; H.size = size; H.tag = tag; H.prior = prior;
    for (i = n/2; i > 0; i--) ShiftDown(H, i); // 对以i节点为根的子树进行筛选
}

