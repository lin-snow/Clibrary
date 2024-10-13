void HeapSort(RcdSqList &L) {
    Heap H; int i;
    RcdType e;
    MakeHeap(H, L.rcd, L.length, L.size, 1, greatPrior);
    for (i=H.n, i>0; i--)
        RemoveFirstHeap(H, e); // 堆顶与堆尾结点交换，堆长度减一，筛选新的堆顶结点
}