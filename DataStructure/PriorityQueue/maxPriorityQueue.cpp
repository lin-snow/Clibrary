// 抽象数据类型 maxPriorityQueue
template <class T>
class maxPriorityQueue {
    public:
    virtual ~maxPriorityQueue() {}
    virtual bool empty() const = 0; // 返回true当且仅当队列为空
    virtual int size() const = 0; // 返回队列中的元素个数
    virtual const T& top() = 0; // 返回优先级最大的元素的引用
    virtual void pop() = 0; //删除队首元素
    virtual void push(const T& theElement) = 0; // 插入元素 theElement
};


