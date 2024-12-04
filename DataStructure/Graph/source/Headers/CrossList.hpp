//--------------------------------------------十字链表--------------------------------------------
#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Iterator.h"
#include "Common.hpp"

#include "Graph.h"

#include <queue>
#include <utility>

// 插入一个顶点
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::insertVertex(vertex<DataType>* theVertex) {
    // 将顶点插入到十字链表的最后一个位置
    // 检查十字链表是否为空
    if (xList == nullptr) { // 为空，创建一个十字链表
        xList = new VexNode<vertex<DataType>, WeightType>* [1]; // 创建一个新的数组
        xList[0] = new VexNode<vertex<DataType>, WeightType>(theVertex); // 创建一个新的节点
    } else {
        // 创建一个新的数组
        VexNode<vertex<DataType>, WeightType>** temp = new VexNode<vertex<DataType>, WeightType>* [g.numberOfVertices() + 1];
        for (int i = 0; i < g.numberOfVertices() + 1; i++) {
            temp[i] = nullptr;
        }

        // 复制原来的十字链表
        for (int i = 0; i < g.numberOfVertices(); i++) {
            temp[i] = xList[i];
        }

        // 插入新的节点
        temp[g.numberOfVertices()] = new VexNode<vertex<DataType>, WeightType>(theVertex);

        // 删除原来的十字链表
        delete [] xList;

        // 指向新的十字链表
        xList = temp;
    }
}

// 删除一个顶点
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::eraseVertex(int v) {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return;
    }

    // 新建一个新的十字链表
    VexNode<vertex<DataType>, WeightType>** temp = new VexNode<vertex<DataType>, WeightType>* [g.numberOfVertices() - 1];

    // 复制原来的十字链表
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        if (i < v) {
            temp[i] = xList[i];
        } else if (i >= v) {
            temp[i] = xList[i + 1];
        }
    }

    // 把headVex大于v的索引减一
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        if (temp[i]->firstOut != nullptr) {
            ArcBox<WeightType>* curNode = temp[i]->firstOut;
            while (curNode != nullptr) {
                if (curNode->headVex > v) {
                    curNode->headVex--;
                }
                curNode = curNode->tailLink;
            }
        }
    }

    // 把tailVex大于v的索引减一
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        if (temp[i]->firstIn != nullptr) {
            ArcBox<WeightType>* curNode = temp[i]->firstIn;
            while (curNode != nullptr) {
                if (curNode->tailVex > v) {
                    curNode->tailVex--;
                }
                curNode = curNode->headLink;
            }
        }
    }

    // 删除新十字链表中的所有指向待删除顶点的边 
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        ArcBox<WeightType>* curNode = temp[i]->firstOut;
        ArcBox<WeightType>* preNode = nullptr;
        while (curNode != nullptr) {
            if (curNode->headVex == v) {
                if (preNode == nullptr) {
                    temp[i]->firstOut = curNode->tailLink;
                } else {
                    preNode->tailLink = curNode->tailLink;
                }
                delete curNode;
                curNode = preNode;
            }
            preNode = curNode;
            if (curNode != nullptr) {
                curNode = curNode->tailLink;
            }
        }
    }

    // 更新新十字链表的所有入边
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        ArcBox<WeightType>* curNode = temp[i]->firstIn;
        ArcBox<WeightType>* preNode = nullptr;
        while (curNode != nullptr) {
            if (curNode->tailVex == v) {
                if (preNode == nullptr) {
                    temp[i]->firstIn = curNode->headLink;
                } else {
                    preNode->headLink = curNode->headLink;
                }
                delete curNode;
                curNode = preNode;
            }
            preNode = curNode;
            if (curNode != nullptr) {
                curNode = curNode->headLink;
            }
        }
    }

    // 删除原来的十字链表
    delete [] xList;

    // 指向新的十字链表
    xList = temp;

    return;
}

// 存在一条边
template <typename DataType, typename WeightType>
bool CrossList<DataType, WeightType>::existEdge(int v1, int v2) const {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return false;
    }

    // 检查顶点索引是否有效
    if (v1 < 0 || v1 >= g.numberOfVertices() || v2 < 0 || v2 >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return false;
    }

    // 检查边是否存在
    ArcBox<WeightType>* curNode = xList[v1]->firstOut;
    while (curNode != nullptr) {
        if (curNode->headVex == v2) {
            return true;
        }
        curNode = curNode->tailLink;
    }

    return false;
}

// 插入一条边
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::insertEdge(edge<WeightType>* theEdge) {
    int v1 = theEdge->fromID;
    int v2 = theEdge->toID;

    // 插入边
    ArcBox<WeightType>* theArc = new ArcBox<WeightType>(v1, v2, theEdge->weight);
    theArc->tailVex = v1;
    theArc->headVex = v2;
    if (xList[v1]->firstOut == nullptr) {
        xList[v1]->firstOut = theArc;
    } else {
        ArcBox<WeightType>* curNode = xList[v1]->firstOut;
        while (curNode->tailLink != nullptr) {
            curNode = curNode->tailLink;
        }
        curNode->tailLink = theArc;
    }

    // 插入入边
    theArc = new ArcBox<WeightType>(v1, v2, theEdge->weight);
    theArc->tailVex = v1;
    theArc->headVex = v2;
    if (xList[v2]->firstIn == nullptr) {
        xList[v2]->firstIn = theArc;
    } else {
        ArcBox<WeightType>* curNode = xList[v2]->firstIn;
        while (curNode->headLink != nullptr) {
            curNode = curNode->headLink;
        }
        curNode->headLink = theArc;
    }

    return;
}

// 删除一条边
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::eraseEdge(int v1, int v2) {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return;
    }

    // 删除边
    ArcBox<WeightType>* curNode = xList[v1]->firstOut;
    ArcBox<WeightType>* preNode = nullptr;
    while (curNode != nullptr) {
        if (curNode->headVex == v2) {
            if (preNode == nullptr) {
                xList[v1]->firstOut = curNode->tailLink;
            } else {
                preNode->tailLink = curNode->tailLink;
            }
            delete curNode;
            return;
        }
        preNode = curNode;
        curNode = curNode->tailLink;
    }
    
    return;
}

// 改变边的权重
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::setWeight(int v1, int v2, WeightType theWeight) {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return;
    }

    // 改变边的权重
    ArcBox<WeightType>* curNode = xList[v1]->firstOut;
    while (curNode != nullptr) {
        if (curNode->headVex == v2) {
            curNode->weight = theWeight;
            return;
        }
        curNode = curNode->tailLink;
    }

    return;
}

// 返回边的权重
template <typename DataType, typename WeightType>
WeightType CrossList<DataType, WeightType>::getWeight(int v1, int v2) const {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return g.noEdge;
    }

    // 返回边的权重
    ArcBox<WeightType>* curNode = xList[v1]->firstOut;
    while (curNode != nullptr) {
        if (curNode->headVex == v2) {
            return curNode->weight;
        }
        curNode = curNode->tailLink;
    }

    return g.noEdge;
}

// 返回顶点的入度
template <typename DataType, typename WeightType>
int CrossList<DataType, WeightType>::inDegree(int v) const {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return -1;
    }

    // 返回顶点的入度
    int inDegree = 0;
    // for (int i = 0; i < g.numberOfVertices(); i++) {
    //     if (i == v) {
    //         continue;
    //     }
    //     ArcBox<WeightType>* curNode = xList[i]->firstOut;
    //     while (curNode != nullptr) {
    //         if (curNode->headVex == v) {
    //             inDegree++;
    //         }
    //         curNode = curNode->tailLink;
    //     }
    // }

    // 利用入边链表
    ArcBox<WeightType>* curNode = xList[v]->firstIn;
    while (curNode != nullptr) {
        inDegree++;
        curNode = curNode->headLink;
    }

    return inDegree;
}

// 返回顶点的出度
template <typename DataType, typename WeightType>
int CrossList<DataType, WeightType>::outDegree(int v) const {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return -1;
    }

    // 返回顶点的出度
    int outDegree = 0;
    ArcBox<WeightType>* curNode = xList[v]->firstOut;
    while (curNode != nullptr) {
        outDegree++;
        curNode = curNode->tailLink;
    }

    return outDegree;
}

// 返回顶点的度
template <typename DataType, typename WeightType>
int CrossList<DataType, WeightType>::degree(int v) const {
    // 检查十字链表是否为空
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return -1;
    }

    // 返回顶点的度
    return inDegree(v) + outDegree(v);
}

// 打印十字链表
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::printCrossList() const {
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return;
    }

    std::cout << "当前十字链表为: " << std::endl;
    for (int i = 0; i < g.numberOfVertices(); i++) {
        std::cout << "顶点 " << i << "(" << g.vertexList->get(i)->data << "):";
        ArcBox<WeightType>* temp = xList[i]->firstOut;
        while (temp != nullptr) {
            std::cout << "[" << temp->tailVex << ", " << temp->headVex << "(" << g.vertexList->get(temp->headVex)->data << ")" << ", " << temp->weight << "] ";

            // tailLink
            temp = temp->tailLink;
            if (temp != nullptr) {
                std::cout << " --> ";
            }
        }
        std::cout << std::endl;
    }
}

// 删除十字链表
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::deleteCrossList() {
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return;
    }

    for (int i = 0; i < g.numberOfVertices(); i++) {
        ArcBox<WeightType>* curNode = xList[i]->firstOut;
        ArcBox<WeightType>* preNode = nullptr;
        while (curNode != nullptr) {
            preNode = curNode;
            curNode = curNode->tailLink;
            delete preNode;
        }
        delete xList[i];
    }
    delete [] xList;

    xList = nullptr;

    return;
}

// 返回迭代器
template <typename DataType, typename WeightType>
Iterator_CL<DataType, WeightType>* CrossList<DataType, WeightType>::myIterator(int theVertex) {
    if (theVertex < 0 || theVertex >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! " << theVertex << std::endl;
        return nullptr;
    }

    return new Iterator_CL<DataType, WeightType>(xList[theVertex]->firstOut, g.noEdge, g.vertexList);
}

// 广度优先搜索
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::BFS(int v, int reach[], int label) {
    // 初始化reach数组
    for (int i = 0; i < g.numberOfVertices(); i++) {
        reach[i] = 0;
    }

    // 创建一个队列
    arrayQueue<int> q(g.numberOfVertices());

    // 标记顶点v
    reach[v] = label;
    q.enqueue(v);


    // 访问顶点v
    WeightType weight;
    while (!q.empty()) {
        int w = q.front();
        q.dequeue();

        // 当前正在访问
        std::cout << "访问顶点: " << w << std::endl;

        // 标记所有未访问的邻接顶点
        Iterator_CL<DataType, WeightType>* iw = myIterator(w);
        int u;
        while ((u = iw->next(weight)) != -1) {
            if (reach[u] == 0) {
                reach[u] = label; // 标记顶点u
                q.enqueue(u); // 将顶点u入队
            }
        }

        delete iw; // 删除迭代器
    }

    // 访问剩余的未访问的顶点
    for (int i = 0; i < g.numberOfVertices(); i++) {
        if (reach[i] == 0) {
            // 访问顶点i
            std::cout << "访问顶点: " << i << std::endl;
            reach[i] = label;
        }
    }

    return;
}

// 深度优先搜索
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::DFS(int v, int reach[], int label) {
    // 初始化reach数组
    for (int i = 0; i < g.numberOfVertices(); i++) {
        reach[i] = 0;
    }

    // 访问顶点
    std::cout << "访问顶点: " << v << std::endl;

    // 递归深度优先搜索
    rDFS(v, reach, label);

    // 访问剩余的未访问的顶点
    for (int i = 0; i < g.numberOfVertices(); i++) {
        if (reach[i] == 0) {
            std::cout << "访问顶点: " << i << std::endl;
            reach[i] = label;
        }
    }
}

// 递归深度优先搜索
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::rDFS(int v, int reach[], int label) {
    reach[v] = label;
    Iterator_CL<DataType, WeightType>* iv = myIterator(v);
    int u;
    WeightType weight;
    while ((u = iv->next(weight)) != -1) { // 访问v相邻的顶点
        if (reach[u] == 0) {
            std::cout << "访问顶点: " << u << std::endl;
            rDFS(u, reach, label);
        }
    }

    delete iv; // 删除迭代器
}

// 查找路径
template <typename DataType, typename WeightType>
int* CrossList<DataType, WeightType>::findPath(int theSource, int theDestination) {
    int n = g.numberOfVertices(); // 顶点的数量
    int* path = new int [n + 1]; // 路径数组
    path[1] = theSource;
    int length = 1; // 路径的长度
    int destination = theDestination; // 目标顶点
    int* reach = new int [n + 1]; // 标记数组
    for (int i = 0; i <= n; i++) {
        reach[i] = 0; // 初始化为0
    }

    // 搜索路径
    if (theSource == theDestination || rFindPath(theSource, reach, path, length, theDestination)) {
        path[0] = length - 1; // 路径的长度 
    } else {
        delete [] path; 
        path = nullptr;
    }

    delete [] reach; // 删除标记数组
    return path;
}

// 递归查找路径
template <typename DataType, typename WeightType>
bool CrossList<DataType, WeightType>::rFindPath(int s, int reach[], int path[], int & length, int destination) {
    // 从顶点s开始实施深度优先搜索
    // 顶点s不应该等于终点
    // 当且仅当一条路径找到了，返回true

    reach[s] = 1; // 标记顶点s
    Iterator_CL<DataType, WeightType>* is = myIterator(s);
    int u;
    WeightType weight;
    while ((u = is->next(weight)) != -1) {
        if (reach[u] == 0) {
            path[++length] = u; // 将顶点u添加到路径中
            if (u == destination || rFindPath(u, reach, path, length, destination) == true) {
                return true;
            }
            // 从顶点u到终点没有路径
            length--; // 从路径中删除u
        }
    }

    delete is; // 删除迭代器
    return false;
}

// 最短路径 (dijkstra算法)
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::dijkstra(int start, WeightType* dist) {
    for (int i = 0; i < g.n; i++) dist[i] = g.noEdge; // 初始化为无穷大
    dist[start] = 0; // 起点距离设置为0

    // 创建一个优先队列
    std::priority_queue<std::pair<WeightType, int>, std::vector<std::pair<WeightType, int>>, std::greater<std::pair<WeightType, int>>> pq;

    // 将起点加入到优先队列
    pq.push(std::make_pair(dist[start], start));

    // dijkstra算法
    while (!pq.empty()) {
        WeightType curDist = pq.top().first; // 当前距离
        int curVertex = pq.top().second; // 当前顶点
        pq.pop(); // 弹出队首元素

        // 遍历当前定点的所有邻接顶点
        Iterator_CL<DataType, WeightType>* iv = myIterator(curVertex);
        int u; WeightType weight;
        while ((u = iv->next(weight)) != -1) {
            if (dist[u] > dist[curVertex] + weight) {
                dist[u] = dist[curVertex] + weight;
                pq.push(std::make_pair(dist[u], u));
            }
        }
        delete iv; // 删除迭代器
    }
}

// 拓补排序
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::topologicalSort() {
    arrayList<int> theInDegree(g.n); // 入度数组
    for (int i = 0; i < g.n; i++) theInDegree.insert(i, 0); // 初始化为0
    // 计算每个顶点的入度
    for (int i = 0; i < g.n; i++)
        theInDegree.get(i) = inDegree(i);

    // 创建一个队列
    arrayQueue<int> q(g.n);

    // 将入度为0的顶点加入到队列
    for (int i = 0; i < g.n; i++) 
        if (theInDegree.get(i) == 0) q.enqueue(i);

    // 拓补排序
    while (!q.empty()) {
        int v = q.front();
        q.dequeue();
        std::cout << v << "(" << g.vertexList->get(v)->data << ")" << " "; // 输出顶点

        // 遍历邻接顶点
        Iterator_CL<DataType, WeightType>* iv = myIterator(v);
        int u; WeightType weight;
        while ((u = iv->next(weight)) != -1) {
            theInDegree.get(u)--;
            if (theInDegree.get(u) == 0) q.enqueue(u); // 如果入度为0,加入队列
        }
        delete iv; // 删除迭代器
    }

    return;
}

// Prim算法
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::prim(int start, WeightType* miniCost) {
    for (int i = 0; i < g.n; i++) miniCost[i] = g.noEdge; // 初始化为无穷大
    miniCost[start] = 0; // 起点边权重设置为0
    arrayList<bool> inMST(g.n);
    for (int i = 0; i < g.n; i++) inMST.insert(i, false); // 初始化为false
    
    // 使用优先队列
    std::priority_queue<std::pair<WeightType, int>, std::vector<std::pair<WeightType, int>>, std::greater<std::pair<WeightType, int>>> pq;
    pq.push(std::make_pair(miniCost[start], start));

    while(!pq.empty()) { // 队列不为空
        int u = pq.top().second; // 当前顶点
        pq.pop();

        // 如果当前顶点已经在最小生成树中， 则跳过
        if (inMST.get(u)) continue;
        inMST.get(u) = true;

        // 遍历当前顶点的所有邻接顶点
        Iterator_CL<DataType, WeightType>* iv = myIterator(u);
        int v; WeightType weight;
        while ((v = iv->next(weight)) != -1) {
            if (!inMST.get(v) && miniCost[v] > weight) { // 如果该边更小且邻接节点不在最小生成树中
                miniCost[v] = weight; // 更新最小边权
                pq.push(std::make_pair(miniCost[v], v)); // 将该边加入到优先队列
            }
        }
        delete iv; // 删除迭代器
    }

    return;
}

// 清空十字链表
template <typename DataType, typename WeightType>
void CrossList<DataType, WeightType>::clear() {
    if (xList == nullptr) {
        std::cout << "当前十字链表为空！" << std::endl;
        return;
    }

    for (int i = 0; i < g.numberOfVertices(); i++) {
        ArcBox<WeightType>* curNode = xList[i]->firstOut;
        ArcBox<WeightType>* preNode = nullptr;
        while (curNode != nullptr) {
            preNode = curNode;
            curNode = curNode->tailLink;
            delete preNode;
        }
        delete xList[i];
    }
    delete [] xList;

    xList = nullptr;

    return;
}

//--------------------------------------------十字链表--------------------------------------------