#include <iostream>
#include "BinaryTree.cpp"

// 链表二叉树的节点结构
template<class T>
struct BinaryTreeNode {
    T element;
    BinaryTreeNode<T> * leftChild,
                      * rightChild;
    
    BinaryTreeNode() {
        leftChild = rightChild = NULL;
    }

    BinaryTreeNode(const T& theElement) {
        element(theElement);
        leftChild = rightChild = NULL;
    }

    BinaryTreeNode(const T& theElement, BinaryTreeNode * theLeftChild, BinaryTreeNode * theRightChild) {
        element(theElement);
        leftChild(theLeftChild);
        rightChild(theRightChild);
    }
};

// 前序遍历
template <class T>
void preOrder(BinaryTreeNode<T> *t) {
    if (t != NULL) {
        visit(t); // 访问树根
        preOrder(t->leftChild); // 访问左子树
        preOrder(t->rightChild); // 访问右子树
    }
}

// 中序遍历
template <class T>
void inOrder(BinaryTreeNode<T> *t) {
    if (t != NULL) {
        inOrder(t->leftChild); // 中序遍历左子树
        visit(t); // 访问树根
        inOrder(t->rightChild); // 中序遍历右子树
    }
}

// 后序遍历
template <class T>
void postOrder(BinaryTreeNode<T> *t) {
    if (t != NULL) {
        postOrder(t->leftChild); // 后序遍历左子树
        postOrder(t->rightChild); // 后序遍历右子树
        visit(t); // 访问树根
    }
}

// 访问函数
template <class T>
void visit(BinaryTreeNode<T> *t) {
    cout << t->element << ' ';
}

// 层级遍历
template <class T>
void levelOrder(BinaryTreeNode<T> *t) {
    arrayQueue<BinaryTreeNode<T>*> q;
    while (t != NULL) {
        visit(t); // 访问t

        // 将t的孩子插入队列
        if (t->leftChild != NULL) 
            q.push(t->leftChild);
        if (t->rightChild != NULL) 
            q.push(t->rightChild);

        try {
            t = q.front();
        } catch (queueEmpty) {
            return;
        }
        
        q.pop();
    }
}

// linkedBinaryTree（抽象类BinaryTree的派生类）
template <class E>
class linkedBinaryTree : public BinaryTree<BinaryTreeNode<E> > {
    public:
        linkedBinaryTree() { // 构造函数
            root = NULL;
            treeSize = 0;
        }
        ~linkedBinaryTree() { // 析构函数
            erase();
        }
        bool empty() const {
            return treeSize == 0;
        }
        int size() const {
            return treeSize;
        }
        void preOrder(void (*theVisit)(BinaryTreeNode<E>*)) {
            visit = theVisit;
            preOrder(root);
        }
        void inOrder(void (*theVisit)(BinaryTreeNode<E>* )) {
            visit = theVisit;
            inOrder(root);
        }
        void postOrder(void (*theVisit)(BinaryTreeNode<E>* )) {
            visit = theVisit;
            postOrder(root);
        }
        void levelOrder(void (*theVisit)(BinaryTreeNode<E>* )) {
            visit = theVisit;
            levelOrder(root);
        }
        void erase() {
            postOrder(dispose); // dispose作为函数指针visit方法，在后序遍历中删除二叉树所有节点
            root = NULL;
            treeSize = 0;
        }
        int height() const {
            return height(root);
        }

    private:
        BinaryTreeNode<E> *root; // 指向根的指针
        int treeSize;            // 树的节点个数
        static void (*visit)(BinaryTreeNode<E>* ); // 访问函数
        static void preOrder(BinaryTreeNode<E>* ); // 前序遍历
        static void inOrder(BinaryTreeNode<E>* ); // 中序遍历
        static void postOrder(BinaryTreeNode<E>* ); // 后序遍历
        static void dispose(BinaryTreeNode<E>* t) delete t;
        static int height(BinaryTreeNode<E>* t); // 求树的高度
};

// 类linkedBinaryTree的私有前序遍历方法
template <class E>
void linkedBinaryTree<E>::preOrder(BinaryTreeNode<E> *t) {
    if (t != NULL) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

// 类linkedBinaryTree的私有中序遍历方法
template <class E>
void linkedBinaryTree<E>::inOrder(BinaryTreeNode<E> *t) {
    if (t != NULL) {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

// 类linkedBinaryTree的私有后序遍历方法
template <class E>
void linkedBinaryTree<E>::postOrder(BinaryTreeNode<E> *t) {
    if (t != NULL) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

// 返回根为*t的树的高度
template <class E>
int linkedBinaryTree<E>::height(BinaryTreeNode<E> *t) {
    if (t == NULL) return 0; // 空树的高度为0
    int hl = height(t->leftChild); // 左子树的高度
    int hr = height(t->rightChild); // 右子树的高度
    if (hl > hr) 
        return ++hl;
    else 
        return ++hr;
}