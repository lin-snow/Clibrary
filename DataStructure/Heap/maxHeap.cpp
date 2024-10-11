template <class T>
class maxHeap {
    public: 
        void initialize(T *theHeap, int theSize) = 0;
        void push(const T& theElement) = 0;
        void pop() = 0;

    private:
        T* heap;
        int arrayLength; // 数组heap的容量
        int heapSize; // 堆的元素个数
};

template <class T>
void maxHeap<T>::initialize(T *theHeap, int theSize) {
    // 在数组[1:theSize] 中建大根堆
    delete [] heap;
    heap = theHeap;
    heapSize = theSize;

    // 堆化
    for (int root = heapSize / 2; root >= 1; root--) {
        T rootElement = heap[root];

        // 为元素rootElement寻找位置
        int child = 2 * root;
        while (child <= heapSize) {
            // heap[child]应该是兄弟中较大者
            if (child < heapSize && heap[child] < heap[child+1])
                child++;
            
            // 可以把元素rootElement放在heap[child/2]吗
            if (rootElement >= heap[child])
                break;

            // 不可以
            heap[child / 2] = heap[child]; // 把孩子向上移
            child *= 2; // 移到下一级
        }
        heap[child / 2] = rootElement;
    }
}

template <class T>
void maxHeap<T>::push(const T& theElement) {
    // 把元素theElement加入堆
    // 必要时增加数组长度
    if (heapSize == arrayLength - 1) {
        // 把数组长度加倍
        changLength1D(heap, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }

    // 为元素theElement 寻找插入位置
    // currentNode 从新叶子向上移动
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] < theElement) {
        // 不能把元素theElement插入在heap[currentNode]
        heap[currentNode] = heap[currentNode / 2]; // 把元素向下移动
        currentNode /= 2;
    }

    heap[currentNode] = theElement;
}

template <class T>
void maxHeap<T>::pop() {
    // 删除最大元素
    // 如果堆为空,抛出异常
    if (heapSize == 0)
        throw queueEmpty()
    
    // 删除最大元素
    heap[1].~T();

    // 删除最后一个元素，然后重新建堆
    T lastElement = heap[heapSize--];

    // 从根开始， 为最后一个元素寻找位置
    int currentNode = 1, child = 2;
    while (child <= heapSize) {
        //heap[child] 应该是currentNode的更大的孩子
        if (child < heapSize && heap[child] < heap[child+1])
            child++;
        
        //  可以把lastElement 放在 heap[currentNode]吗？
        if (lastElement >= heap[child])
            break; // 可以

        // 不可以
        heap[currentNode] = heap[child]; //把孩子child向上移动
        currentNode = child; // 向下移动一层寻找位置
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

