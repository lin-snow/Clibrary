#include <ostream>

template <class T>
struct chainNode {
    // 数据成员
    T element;
    chainNode<T> *next;

    // 方法
    chainNode() {}
    chainNode(const T& element) {this->element = element}
    chainNode(const T& element, chainNode<T>* next) {
        this->element = element;
        this-next = next;
    }
};

template <class T>
class chain : linearList<T> {
    public:
        // 构造函数
        chain(int initialCapacity = 10);
        chain(const chain<T>&);
        ~chain();

        // 抽象数据类型ADT的方法
        bool empty() const {return listSize == 0;}
        int size() const {return listSize;}
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out) const;

    protected:
        void checkIndex(int theIndex) const; // 如果索引无效，抛出异常
        chainNode<T>* firstNode; // 指向链表第一个节点的指针
        int listSize; 
};

template <class T>
chain<T>::chain(int initialCapacity) {
    // 构造函数 
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0 ";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T>& theList) {
    // 复制构造函数
    listSize = theList.listSize;

    if (listSize == 0) {
        // 链表theList 为空
        firstNode = NULL;
        return;
    }

    // 链表theList 异常
    chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element); // 复制链表theList的首元素
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode; // 当前链表*this 的最后一个节点

    while (sourceNode != NULL) {
        // 复制剩余元素
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
}

template <class T>
chain<T>::~chain() {
    // 链表析构函数，删除链表的所有节点
    while (firstNode != NULL) {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
T& chain<T>::get(int theIndex) const {
    // 返回索引为theIndex的元素
    // 若该元素不存在，则抛出异常
    checkIndex(theIndex);

    // 移向所需要的节点
    chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) 
        currentNode = currentNode->next;
    return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T& theElement) const {
    // 返回元素theElement 首次出现时的索引
    // 若该元素不存在，则返回 -1

    // 搜索链表寻找元素 theElement
    chainNode<T>* currentNode = firstNode;
    int index = 0; // 当前节点的索引
    while (currentNode != NULL && currentNode->element != theElement) {
        // 移向下一个节点
        currentNode = currentNode->next;
        index++;
    }

    // 确定是否找到元素
    if (currentNode == NULL) 
        return -1;
    else 
        return index;
}

template <class T>
void chain<T>::erase(int theIndex) {
    // 删除索引为theIndex的元素
    // 若该元素不存在，则抛出异常
    checkIndex(theIndex);

    // 索引有效，需找要删除的节点
    chainNode<T>* deleteNode;
    if (theIndex == 0) {
        // 删除链表的首节点
        deleteNode = firstNode;
        firstNode = firstNode->next; 
    } else {
        // 用指针p指向要删除节点的前驱节点
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) 
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next;
    }

    listSize--;
    delete deleteNode;
}

template <class T>
void chain<T>::insert(int theIndex, const T& theElement) {
    // 在索引为theIndex 的位置插入元素theElement
    if (theIndex < 0 || theIndex > listSize) {
        // 索引无效
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0) 
        // 在链表头插入
        firstNode = new chainNode<T>(theElement, firstNode);
    else {
        // 寻找新元素的前驱
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        
        // 在p之后插入
        p-next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template <class T>
void chain<T>::output(std::ostream& out) const {
    // 把链表放入输出流
    for (chainNode<T>* currentNode = firstNode;
                       currentNode != NULL;
                       currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// 重载<<
template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x) {
    x.output(out);
    return out;
}

