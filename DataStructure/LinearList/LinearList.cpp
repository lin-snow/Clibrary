// 抽象类线性表的定义
#include <ostream>
template <class T>
class linearList {
    public:
        virtual ~linearList() = default; // 虚析构函数
        virtual bool empty() const = 0; // 返回true, 当且仅当线性表为空
        virtual int size() const = 0; // 返回线性表的元素个数
        virtual T& get(int theIndex) const = 0; // 返回索引为theIndex的元素的引用
        virtual int indexOf(const T& theElement) const = 0; // 返回元素theElement第一次出现的索引
        virtual void erase(int theIndex) = 0; // 单蠢索引为theIndex的元素
        virtual void insert(int theIndex, const T& theElement) = 0; // 在索引theIndex处插入元素theElement
        virtual void output(ostream& out) const = 0; // 将线性表插入输出流out      
};

// 改变一个一维数组的长度
template <class T>
void changeLength1D(T* & a, int oldLength, int newLength) {
    if (newLength < 0) {
        throw illegalParameterValue("new length must be >= 0");
    }

    T* temp = new T[newLength]; // 新数组
    int number = min(oldLength, newLength); // 需要复制的元素个数
    copy(a, a+number, temp); // 将从a 到 a+number之间的数据复制到新数组
    delete [] a; // 释放老数组的内存空间
    a = temp;
};

template <class T>
class arrayList : public linearList<T> {
    public: 
        // 构造函数，复制构造函数和析构函数
        arrayList(int initialCapacity = 10);
        arrayList(const arrayList<T> &);
        ~arrayList() {
            delete [] element;
        }

        // ADT 方法
        bool empty const {return listSize == 0};
        int size() const {return listSize};
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const ;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out) const;

        // 其他方法
        int capacity() const {return arrayLength;}

    protected:
        void checkIndex(int theIndex) const; // 若索引无效，则抛出异常
        T* element: // 存储线性元素的一维数组
        int arrayLength; // 一维数组的容量
        int listSize; // 一维数组的元素个数
};

// 类arrayList的构造函数
template <class T>
arrayList<T>::arrayList(int initialCapacity) {
    // 构造函数
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0! ";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0; 
}

template <class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
    // 复制构造函数
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element+listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const {
    // 确定索引theIndex 在 0 和 listSize - 1之间
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

template <class T>
T& arrayList<T>::get(int theIndex) const {
    // 返回索引为theIndex的元素
    // 若此元素不存在，抛出异常
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T& theElement) const {
    // 返回元素theElement第一次出现时的索引
    // 若该元素不存在，则返回 -1

    // 查找元素
    int theIndex = (int) (find(element, element + listSize, theElement) - element);

    // 确定元素theElement是否找到
    if (theIndex == listSize)
        return -1; // 没有找到
    else return theIndex;
}

template <class T>
void arrayList<T>::erase(int theIndex) {
    // 删除其索引为theIndex的元素
    // 如果该元素不存在，则抛出异常
    checkIndex(theIndex);

    // 有效索引,移动其索引大于theIndex的元素
    copy(element+theIndex+1, element+listSize, element+theIndex);

    element[--listSize].~T(); // 调用析构函数
}

template <class T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    // 在索引theIndex 处插入元素theElement
    if (theIndex < 0 || theIndex > listSize) {
        // 无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str())
    }

    // 有效索引, 确定数组是否已满
    if (listSize == arrayLength) {
        // 该数组空间已满，数组长度倍增
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 把元素向右移动一个位置
    std::copy_backward(element+theIndex, element+listSize, element+listSize+1);
    element[theIndex] = theElement;
    listSize++;
}

template <class T>
void arrayList<T>::output(std::ostream& out) const {
    //把线性表插入输出流
    copy(element, element+listSize, std::ostream_iterator<T>(cout, " "));
}

template <class T>
std::ostream &operator<<(std::ostream& out, const arrayList<T>& x) {
    x.output(out);
    return out;
}