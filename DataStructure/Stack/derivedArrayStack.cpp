template <class T>
class stack {
    public:
        virtual ~stack() = default;
        virtual bool empty() const = 0; // 返回true，当且仅当栈为空
        virtual int size() const = 0; // 返回栈中元素的个数
        virtual T& top() = 0; // 返回栈顶元素的引用
        virtual void pop() = 0; // 删除栈顶元素
        virtual void push(const T& theElement) = 0; // 将元素theElement压入栈顶
};

template <class T>
class derivedArrayStack : private arrayList<T>, public stack<T> {
    public:
        derivedArrayStack(int initialCapacity = 10):
            arrayList<T> (initialCapacity) {}
        bool empty() const {return arrayList<T>::empty();}
        int size() const {return arrayList<T>::size();} 
        T& top() {
            // if (arrayList<T>::empty)
            //     throw stackEmpty();
            // else get(arrayList<T>::size() - 1);
            try {return get(arrayList<T>::size() - 1)}
            catch (illegalIndex) {
                throw stackEmpty();
            }
        }
        void pop() {
            if (arrayList<T>::empty)
                throw stackEmpty();
            erase(arrayList<T>::size() - 1);
        }
        void push(const T& theElement) {
            insert(arrayList<T>::size(), theElement);
        }
};                       

template <class T>
class arrayStack : public stack<T> {
    public:
        arrayStack(int initialCapacity = 10);
        ~arrayStack() {delete [] stack;}
        bool empty() const {return stackTop == -1}
        int size() const {return (stackTop + 1);}
        T& top() {
            if (stackTop == -1)
                throw stackEmpty();
            return stack[stackTop];
        }
        void pop() {
            if (stackTop == -1)
                throw stackEmpty();
            stack[stackTop--].~T(); // T的析构函数
        }
        void push(const T& theElement);
    private:
        int stackTop; // 当前栈顶
        int arrayLength; // 栈容量
        T* stack; // 元素数组
};

template <class T>
arrayStack<T>::arrayStack(int initialCapacity) { // 构造函数    
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0 ";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template <class T>
void arrayStack<T>::push(const T& theElement) {
    // 将元素theElement压入栈
    if (stackTop == arrayLength - 1) {
        // 空间已满，容量增加
        changLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 在栈顶压入
    stack[++stackTop] = theElement;
}

// ------------------linkedStack---------------------
template <class T>
class linkedStack : public stack<T> {
    public:
        linkedStack(int initialCapacity = 10) {
            stackTop = NULL;
            stackSize = 0;
        }
        ~linkedStack();
        bool empty() const {return stackSize;}
        T& top() {
            if (stackSize == 0)
                throw stackEmpty();
            return stackTop->element;
        }
        void pop();
        void push(const T& theElement) {
            stackTop = new chainNode<T>(theElement, stackTop);
            stackSize++;
        }

    private:
        chainNode<T>* stackTop; // 栈顶指针
        int stackSize; // 栈中元素个数
};

template <class T>
linkedStack<T>::~linkedStack() {
    // 析构函数
    while (stackTop != NULL) {
        // 删除节点
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template <class T>
void linkedStack<T>::pop() {
    // 删除栈顶结点
    if (stackSize == 0)
        throw stackEmpty();

    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTOp = nextNode;
    stackSize--;
}


