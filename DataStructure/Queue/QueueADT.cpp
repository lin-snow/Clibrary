#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
struct Node {
    T element;
    Node<T>* next;

    Node() { // 默认构造
        Node = NULL;
    }

    Node(const T& theElement) { // 带参构造
        element(theElement);
    }

    Node(const T& theElement, Node* theNext) { // 带参构造
        element(theElement);
        next(theNext);
    }
};

template <class T>
class queue {
    public:
        virtual ~queue() = default;
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual T& front() const = 0; // 返回队首元素的引用
        virtual T& back() const = 0; // 返回队尾元素的引用
        virtual T& dequeue() = 0; // 删除队首元素 
        virtual void enqueue(const T& theElement) = 0; // 将元素theElement 加入队尾
};

template <class E>
class linkedQueue: public queue< Node<E> > {
    public:
        linkedQueue() { // 构造函数
            front = back = NULL;
            queueSize = 0;
        }
        ~linkedQueue() {// 析构函数
            erase();
        }
        bool empty() const {return (queueSize == 0);}
        int size() const {return queueSize;}
        T& front() const {
            if (front == NULL) 
                throw queueEmpty();
            return front;
        }
        T& back() const {
            if (back == NULL)
                throw queueEmpty();
            return back;
        }
        T& dequeue() {
            if (queueSize == 0) 
                throw queueEmpty();

            Node<E>* deNode = front;

            if (queueSize == 1) 
                front = back = NULL;
            else 
                front = front->next;
            
            queueSize--;

            return deNode;
        }
        void enqueue(const E& theElement) {
            Node<E>* queueNode = (Node<E>*) new Node<E>(theElement, NULL);
            if (queueNode == NULL) 
                throw std::createError();

            if (queueSize == 0) {
                front = back = queueNode;
            } else {
                back->next = queueNode;
                back = back->next;
            }

            queueSize++;
        }

    private:
        Node<E> * front, // 指向队首的指针
                * back; // 指向队尾的指针
        int queueSize; // 队列的节点数
        
};