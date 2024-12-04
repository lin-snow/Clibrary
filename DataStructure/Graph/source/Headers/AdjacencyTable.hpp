//--------------------------------------------邻接表--------------------------------------------
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
void AdjacencyTable<DataType, WeightType>::insertVertex(vertex<DataType>* theVertex) {
    // 将顶点插入到邻接表的最后一个位置
    // 检查邻接表是否为空
    if (adjacencyTable == nullptr) { // 为空，创建一个邻接表
        adjacencyTable = new adjacencyTableNode<vertex<DataType>, WeightType>* [1]; // 创建一个新的数组
        adjacencyTable[0] = new adjacencyTableNode<vertex<DataType>, WeightType>(theVertex, g.noEdge); // 创建一个新的节点
    } else {
        // 创建一个新的数组
        adjacencyTableNode<vertex<DataType>, WeightType>** temp = new adjacencyTableNode<vertex<DataType>, WeightType>* [g.numberOfVertices() + 1];
        for (int i = 0; i < g.numberOfVertices() + 1; i++) {
            temp[i] = nullptr;
        }

        // 复制原来的邻接表
        for (int i = 0; i < g.numberOfVertices(); i++) {
            temp[i] = adjacencyTable[i];
        }

        // 插入新的节点
        temp[g.numberOfVertices()] = new adjacencyTableNode<vertex<DataType>, WeightType>(theVertex, g.noEdge);

        // 删除原来的邻接表
        delete [] adjacencyTable;

        // 指向新的邻接表
        adjacencyTable = temp;
    }

    return;
}

// 删除一个顶点
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::eraseVertex(int v) {
    // 检查邻接表是否为空
    if (adjacencyTable == nullptr) {
        std::cout << "当前邻接表为空！" << std::endl;
        return;
    }

    // 检查顶点索引是否有效
    if (v < 0 || v >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! " << v << std::endl;
    }

    // 待删除顶点
    vertex<DataType>* VexToDel = g.vertexList->get(v);

    // 创建一个新的邻接表
    adjacencyTableNode<vertex<DataType>, WeightType>** temp = new adjacencyTableNode<vertex<DataType>, WeightType>* [g.numberOfVertices() - 1];
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        temp[i] = nullptr;
    }

    // 复制原来的邻接表
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        if (i < v) {
            temp[i] = adjacencyTable[i];
        } else if (i >= v) {
            temp[i] = adjacencyTable[i + 1];
        }
    }

    // 删除新邻接表中的所有指向待删除顶点的边
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        adjacencyTableNode<vertex<DataType>, WeightType>* curNode = temp[i];
        adjacencyTableNode<vertex<DataType>, WeightType>* preNode = nullptr;
        while (curNode != nullptr) {
            if (curNode->vertex == VexToDel) {
                if (preNode == nullptr) {
                    temp[i]->next = curNode->next;
                    temp[i]->weight = curNode->weight;
                } else {
                    preNode->next = curNode->next;
                    preNode->weight = curNode->weight;
                }
                delete curNode;
                curNode = preNode;
            }
            preNode = curNode;
            curNode = curNode->next;
        }
    }

    // 删除原来的邻接表
    delete [] adjacencyTable;

    // 指向新的邻接表
    adjacencyTable = temp;

    return;
} 

// 存在一条边
template <typename DataType, typename WeightType>
bool AdjacencyTable<DataType, WeightType>::existEdge(int v1, int v2) const {
    // 检查邻接表是否为空
    if (adjacencyTable == nullptr) {
        std::cout << "当前邻接表为空！" << std::endl;
        return false;
    }

    // 检查顶点索引是否有效
    if (v1 < 0 || v1 >= g.numberOfVertices() || v2 < 0 || v2 >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return false;
    }

    adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[v1];
    while (curNode->next != nullptr) {
        if (curNode->next->vertex == g.vertexList->get(v2)) {
            return true;
        }
        curNode = curNode->next;
    }

    return false;
}

// 插入一条边
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::insertEdge(edge<WeightType>* theEdge) {
    // 插入一条边
    int v1 = theEdge->fromID;
    int v2 = theEdge->toID;
    WeightType theWeight = theEdge->weight;

    // 创建邻接表节点
    adjacencyTableNode<vertex<DataType>, WeightType>* newNode = new adjacencyTableNode<vertex<DataType>, WeightType>(g.vertexList->get(v2), g.noEdge);

    // 插入到邻接表
    adjacencyTableNode<vertex<DataType>, WeightType>* temp = adjacencyTable[v1];
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    temp->weight = theWeight;
    
    return;
}

// 删除一条边
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::eraseEdge(int v1, int v2) {
    adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[v1];

    while (curNode->next != nullptr) {
        if (curNode->next->vertex == g.vertexList->get(v2)) {
            adjacencyTableNode<vertex<DataType>, WeightType>* tempNode = curNode->next;
            curNode->next = curNode->next->next;
            delete tempNode;
            return;
        }
    }
}

// 改变边的权重
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::setWeight(int v1, int v2, WeightType theWeight) {
    adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[v1];

    while (curNode->next != nullptr) {
        if (curNode->next->vertex == g.vertexList->get(v2)) {
            curNode->weight = theWeight;
            return;
        }
    }
}

// 返回边的权重
template <typename DataType, typename WeightType>
WeightType AdjacencyTable<DataType, WeightType>::getWeight(int v1, int v2) const {
    adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[v1];

    while (curNode->next != nullptr) {
        if (curNode->next->vertex == g.vertexList->get(v2)) {
            return curNode->weight;
        }
    }

    return g.noEdge;
}

// 返回顶点的入度
template <typename DataType, typename WeightType>
int AdjacencyTable<DataType, WeightType>::inDegree(int v) const {
    int inDegree = 0;

    for (int i = 0; i < g.numberOfVertices(); i++) {
        if (i == v) {
            continue;
        }
        adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[i];
        while (curNode->next != nullptr) {
            if (curNode->next->vertex == g.vertexList->get(v)) {
                inDegree++;
            }
            curNode = curNode->next;
        }
    }

    return inDegree;
}

// 返回顶点的出度
template <typename DataType, typename WeightType>
int AdjacencyTable<DataType, WeightType>::outDegree(int v) const {
    int outDegree = 0;

    adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[v];
    while (curNode->next != nullptr) {
        outDegree++;
        curNode = curNode->next;
    }

    return outDegree;
}

// 返回顶点的度
template <typename DataType, typename WeightType>
int AdjacencyTable<DataType, WeightType>::degree(int v) const {
    return inDegree(v) + outDegree(v);
}

// 打印邻接表
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::printAdjacencyTable() const {
    if (adjacencyTable == nullptr) {
        std::cout << "当前邻接表为空！" << std::endl;
        return;
    }

    std::cout << "当前邻接表为: " << std::endl;
    for (int i = 0; i < g.numberOfVertices(); i++) {
        std::cout << "顶点 " << i << "(" << g.vertexList->get(i)->data << "):";
        adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[i];
        while (curNode->next != nullptr) {
            std::cout << " --" << "(" << curNode->weight << ")" << "-> ";
            std::cout << curNode->next->vertex->data;
            curNode = curNode->next;
        }
        std::cout << std::endl;
    }

    return;
}

// 删除邻接表
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::deleteAdjacencyTable() {
    if (adjacencyTable == nullptr) {
        return;
    }

    for (int i = 0; i < g.numberOfVertices(); i++) {
        adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[i];
        while (curNode != nullptr) {
            adjacencyTableNode<vertex<DataType>, WeightType>* tempNode = curNode;
            curNode = curNode->next;
            delete tempNode;
        }
    }

    delete [] adjacencyTable;
    adjacencyTable = nullptr;

    return;
}

// 返回迭代器
template <typename DataType, typename WeightType>
Iterator_AT<DataType, WeightType>* AdjacencyTable<DataType, WeightType>::myIterator(int theVertex) {
    if (theVertex < 0 || theVertex >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! " << theVertex << std::endl;
        return nullptr;
    }

    return new Iterator_AT<DataType, WeightType>(adjacencyTable[theVertex], g.noEdge, g.vertexList);
}

// 广度优先搜索
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::BFS(int v, int reach[], int label) {
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
        Iterator_AT<DataType, WeightType>* iw = myIterator(w);
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
            std::cout << "访问顶点: " << i << std::endl;
            reach[i] = label;
        }
    }
}

// 深度优先搜索
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::DFS(int v, int reach[], int label) {
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
void AdjacencyTable<DataType, WeightType>::rDFS(int v, int reach[], int label) {
    reach[v] = label;
    Iterator_AT<DataType, WeightType>* iv = myIterator(v);
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
int* AdjacencyTable<DataType, WeightType>::findPath(int theSource, int theDestination) {
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
bool AdjacencyTable<DataType, WeightType>::rFindPath(int s, int reach[], int path[], int & length, int destination) {
    // 从顶点s开始实施深度优先搜索
    // 顶点s不应该等于终点
    // 当且仅当一条路径找到了，返回true

    reach[s] = 1; // 标记顶点s
    Iterator_AT<DataType, WeightType>* is = myIterator(s);
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
void AdjacencyTable<DataType, WeightType>::dijkstra(int start, WeightType* dist) {
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
        Iterator_AT<DataType, WeightType>* iv = myIterator(curVertex);
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
void AdjacencyTable<DataType, WeightType>::topologicalSort() {
    arrayList<int> theInDegree(g.n); // 入度数组
    for (int i = 0; i < g.n; i++) theInDegree.insert(i, 0); // 初始化为0
    //计算每个顶点的入度
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
        Iterator_AT<DataType, WeightType>* iv = myIterator(v);
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
void AdjacencyTable<DataType, WeightType>::prim(int start, WeightType* miniCost) {
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
        Iterator_AT<DataType, WeightType>* iv = myIterator(u);
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

// 清空邻接表
template <typename DataType, typename WeightType>
void AdjacencyTable<DataType, WeightType>::clear() {
    if (adjacencyTable == nullptr) {
        return;
    }

    for (int i = 0; i < g.numberOfVertices(); i++) {
        adjacencyTableNode<vertex<DataType>, WeightType>* curNode = adjacencyTable[i];
        while (curNode != nullptr) {
            adjacencyTableNode<vertex<DataType>, WeightType>* tempNode = curNode;
            curNode = curNode->next;
            delete tempNode;
        }
    }

    delete [] adjacencyTable;
    adjacencyTable = nullptr;

    return;
}

//--------------------------------------------邻接表--------------------------------------------