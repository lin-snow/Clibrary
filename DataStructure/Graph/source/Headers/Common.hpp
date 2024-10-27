#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>  // 用于 sleep_for
#include <windows.h>  // 用于设置控制台窗口
#include <string>
#include <stdexcept>

using std::min;

// 异常类
class illegalParameterValue {
    public:
        illegalParameterValue(): // 默认构造函数
            message("Illegal parameter value") {}
        illegalParameterValue(const std::string & theMessage)
            : message(theMessage) {} // 带参数的构造函数

        void outputMessage() { 
            std::cout << message << std::endl;
        }
    private:
        std::string message;
};

//---------------------------------------------------------------------------

// 改变一个一维数组的长度
template <class T>
void changeLength1D(T* & a, int oldLength, int newLength) {
    if (newLength < 0) {
        throw illegalParameterValue("new length must be >= 0");
    }

    T* temp = new T [newLength]; // 新数组
    int number = min(oldLength, newLength); // 需要复制的元素个数
    std::copy(a, a+number, temp); // 将从a 到 a+number之间的数据复制到新数组
    delete [] a; // 释放老数组的内存空间
    a = temp;
}

//--------------------------------线性表基类---------------------------------

// 基类线性表
template <class T>
class linearList {
    public:
        virtual ~linearList() = default; // 虚析构函数
        virtual bool empty() const = 0; // 返回true, 当且仅当线性表为空
        virtual int size() const = 0; // 返回线性表的元素个数
        virtual T& get(int theIndex) const = 0; // 返回索引为theIndex的元素的引用
        virtual int indexOf(const T& theElement) const = 0; // 返回元素theElement第一次出现的索引
        virtual void erase(int theIndex) = 0; // 删除索引为theIndex的元素
        virtual void insert(int theIndex, const T& theElement) = 0; // 在索引theIndex处插入元素theElement
        
};

//--------------------------------线性表基类---------------------------------

//--------------------------------线性数组类---------------------------------

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
        bool empty() const {return listSize == 0;}
        int size() const {return listSize;}
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);

        // 其他方法
        int capacity() const {return arrayLength;}

    protected:
        void checkIndex(int theIndex) const; // 若索引无效，则抛出异常
        T* element; // 存储线性元素的一维数组
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
    std::copy(theList.element, theList.element+listSize, element);
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
    int theIndex = (int) (std::find(element, element + listSize, theElement) - element);

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
    std::copy(element+theIndex+1, element+listSize, element+theIndex);

    element[--listSize].~T(); // 调用析构函数
}

template <class T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    // 在索引theIndex 处插入元素theElement
    if (theIndex < 0 || theIndex > listSize) {
        // 无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
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

//--------------------------------线性数组类---------------------------------

//--------------------------------线性队列类---------------------------------
template <class T>
class arrayQueue {
    public:
        arrayQueue(int initialCapacity); // 构造函数
        ~arrayQueue(); // 析构函数

        // ADT方法
        bool empty() const;
        int size() const;
        T& front();
        T& back();
        void dequeue();
        void enqueue(const T& theElement);

    private:
        int queueSize; // 队列的元素个数
        int arrayLength; // 数组的容量
        T* element; // 存储队列元素的一维数组
};

// 构造函数
template <class T>
arrayQueue<T>::arrayQueue(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0! ";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity;
    queueSize = 0;
    element = new T[arrayLength];
}

// 析构函数
template <class T>
arrayQueue<T>::~arrayQueue() {
    delete [] element;

    element = nullptr;
}

// 判断队列是否为空
template <class T>
bool arrayQueue<T>::empty() const {
    return queueSize == 0;
}

// 返回队列的元素个数
template <class T>
int arrayQueue<T>::size() const {
    return queueSize;
}

// 返回队列的首元素
template <class T>
T& arrayQueue<T>::front() {
    if (queueSize == 0) {
        throw illegalParameterValue("The queue is empty!");
    }

    return element[0];
}

// 返回队列的尾元素
template <class T>
T& arrayQueue<T>::back() {
    if (queueSize == 0) {
        throw illegalParameterValue("The queue is empty!");
    }

    return element[queueSize-1];
}

// 删除队列的首元素
template <class T>
void arrayQueue<T>::dequeue() {
    if (queueSize == 0) {
        throw illegalParameterValue("The queue is empty!");
    }

    // 删除首元素
    std::copy(element+1, element+queueSize, element);
    queueSize--;

    return;
}

// 入队
template <class T>
void arrayQueue<T>::enqueue(const T& theElement) {
    if (queueSize == arrayLength) {
        // 数组空间已满， 数组长度增加
        changeLength1D(element, arrayLength, 2*arrayLength);
        arrayLength *= 2;
    }

    // 入队
    element[queueSize] = theElement;
    queueSize++;

    return;
}

//--------------------------------线性队列类---------------------------------

//---------------------------------- 其他 ----------------------------------
// 更新进度条函数
static void updateProgressBar(int progress, int total) {
    int barWidth = 50;  // 进度条长度
    float percent = (float)progress / total;

    // 使用 \r 回到行首，避免换行
    std::cout << "\r[";
    int pos = barWidth * percent;  // 当前进度对应的 # 数量

    // 打印进度条内容
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            std::cout << "#";
        else
            std::cout << " ";
    }

    std::cout << "] " << int(percent * 100) << "%";  // 显示百分比

    std::cout.flush();  // 强制刷新输出
}

// 进度条函数
static void ProgressBar() {
    int total = 100;

    // 模拟任务进度
    for (int i = 0; i <= total; ++i) {
        updateProgressBar(i, total);
        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 延时50ms
    }

    std::cout << std::endl;
}

//---------------------------------- 其他 ----------------------------------


