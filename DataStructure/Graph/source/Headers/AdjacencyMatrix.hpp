//--------------------------------------------邻接矩阵--------------------------------------------
#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Iterator.h"
#include "Common.hpp"

#include <iomanip>
#include <queue>
#include <utility>

#include "Graph.h"

// 插入一个顶点
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::insertVertex(vertex<DataType>* theVertex) {
    // 将顶点插入到邻接矩阵的最后一行和最后一列
    // 检查邻接矩阵是否为空
    if (a == nullptr) { // 为空，创建一个邻接矩阵
        a = new WeightType* [1]; // 创建一个新的二维数组
        a[0] = new WeightType [1]; // 创建一个新的一维数组
        a[0][0] = g.noEdge; // 初始化邻接矩阵
    } else { // 不为空
        // 创建一个新的二维数组
        WeightType** temp = new WeightType* [g.numberOfVertices() + 1];
        for (int i = 0; i < g.numberOfVertices() + 1; i++) {
            temp[i] = new WeightType [g.numberOfVertices() + 1];
        }

        // 复制原来的邻接矩阵
        for (int i = 0; i < g.numberOfVertices(); i++) {
            for (int j = 0; j < g.numberOfVertices(); j++) {
                temp[i][j] = a[i][j];
            }
        }

        // 初始化新的一行和一列
        for (int i = 0; i < g.numberOfVertices() + 1; i++) {
            temp[i][g.numberOfVertices()] = g.noEdge;
            temp[g.numberOfVertices()][i] = g.noEdge;
        }

        // 删除原来的邻接矩阵
        for (int i = 0; i < g.numberOfVertices(); i++) {
            delete [] a[i];
        }
        delete [] a;

        // 指向新的邻接矩阵
        a = temp;
    }

    return;
}

// 删除一个顶点
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::eraseVertex(int v) {
    // 删除一个顶点
    // 检查邻接矩阵是否为空
    if (a == nullptr) {
        std::cout << "当前邻接矩阵为空！" << std::endl;
        return;
    }

    // 检查顶点索引是否有效
    if (v < 0 || v >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return;
    }

    // 创建一个新的二维数组
    WeightType** temp = new WeightType* [g.numberOfVertices() - 1];
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        temp[i] = new WeightType [g.numberOfVertices() - 1];
    }

    // 复制原来的邻接矩阵
    for (int i = 0; i < g.numberOfVertices() - 1; i++) {
        for (int j = 0; j < g.numberOfVertices() - 1; j++) {
            if (i < v && j < v) {
                temp[i][j] = a[i][j];
            } else if (i < v && j >= v) {
                temp[i][j] = a[i][j + 1];
            } else if (i >= v && j < v) {
                temp[i][j] = a[i + 1][j];
            } else {
                temp[i][j] = a[i + 1][j + 1];
            }
        }
    }

    // 删除原来的邻接矩阵
    for (int i = 0; i < g.numberOfVertices(); i++) {
        delete [] a[i];
    }
    delete [] a;

    // // 指向新的邻接矩阵
    a = temp;

    return;
}

// 是否存在边
template <typename DataType, typename WeightType>
bool AdjacencyMatrix<DataType, WeightType>::existEdge(int v1, int v2) const {
    // 检查邻接矩阵是否为空
    if (a == nullptr) {
        std::cout << "当前邻接矩阵为空！" << std::endl;
        return false;
    }

    // 检查顶点索引是否有效
    if (v1 < 0 || v1 >= g.numberOfVertices() || v2 < 0 || v2 >= g.numberOfVertices()) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return false;
    }

    // 检查边是否存在
    if (a[v1][v2] == g.noEdge) {
        return false;
    } else {
        return true;
    }
}

// 插入一条边
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::insertEdge(edge<WeightType>* theEdge) {
    // 插入一条边
    int fromID = theEdge->fromID;
    int toID = theEdge->toID;

    a[fromID][toID] = theEdge->weight;

    return;
}

// 删除一条边
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::eraseEdge(int v1, int v2) {
    // 删除一条边
    a[v1][v2] = g.noEdge;

    return;
}

// 改变边的权重
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::setWeight(int v1, int v2, WeightType theWeight) {
    // 改变边的权重
    a[v1][v2] = theWeight;

    return;
}

// 返回边的权重
template <typename DataType, typename WeightType>
WeightType AdjacencyMatrix<DataType, WeightType>::getWeight(int v1, int v2) const {
    // 返回边的权重
    return a[v1][v2];
}

// 返回顶点的入度
template <typename DataType, typename WeightType>
int AdjacencyMatrix<DataType, WeightType>::inDegree(int v) const {
    // 返回顶点的入度
    int inDegree = 0;
    for (int i = 0; i < g.numberOfVertices(); i++) {
        if (a[i][v] != g.noEdge) {
            inDegree++;
        }
    }

    return inDegree;
}

// 返回顶点的出度
template <typename DataType, typename WeightType>
int AdjacencyMatrix<DataType, WeightType>::outDegree(int v) const {
    // 返回顶点的出度
    int outDegree = 0;
    for (int i = 0; i < g.numberOfVertices(); i++) {
        if (a[v][i] != g.noEdge) {
            outDegree++;
        }
    }

    return outDegree;
}

// 返回顶点的度
template <typename DataType, typename WeightType>
int AdjacencyMatrix<DataType, WeightType>::degree(int v) const {
    // 返回顶点的度
    return inDegree(v) + outDegree(v);
}

// 打印邻接矩阵
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::printAdjacencyMatrix() const {
    // 检查邻接矩阵是否为空
    if (a == nullptr) {
        std::cout << "当前邻接矩阵为空！" << std::endl;
        return;
    }

    // 计算每列的最大宽度
    int* width = new int[g.numberOfVertices()];
    for (int i = 0; i < g.numberOfVertices(); i++) {
        width[i] = 0;
    }
    for (int i = 0; i < g.numberOfVertices(); i++) {
        for (int j = 0; j < g.numberOfVertices(); j++) {
            int w = 0;
            w = std::to_string(a[i][j]).size();
            if (w > width[j]) {
                width[j] = w;
            }
        }
    }

    // 打印邻接矩阵
    std::cout << "当前邻接矩阵为: " << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < g.numberOfVertices(); i++) {
        std::cout << i << "(" << g.getVertex(i)->data << ")" <<" : ";
        for (int j = 0; j < g.numberOfVertices(); j++) {
            std::cout << std::left << " | " << std::setw(width[j]) << a[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}

// 删除邻接矩阵
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::deleteAdjacencyMatrix() {
    // 删除邻接矩阵
    if (a != nullptr) {
        for (int i = 0; i < g.numberOfVertices(); i++) {
            delete [] a[i];
        }
        delete [] a;
    }

    return;
}

// 返回邻接矩阵迭代器
template <typename DataType, typename WeightType>
Iterator_AM<DataType, WeightType>* AdjacencyMatrix<DataType, WeightType>::myIterator(int theVertex) { // 返回顶点的迭代器
    if (theVertex < 0 || theVertex >= g.numberOfVertices()) {
        std::ostringstream s;
        s << "Invalid vertex index! " << theVertex;
        throw illegalParameterValue(s.str()); // 顶点索引无效
    }
    return new Iterator_AM<DataType, WeightType>(a[theVertex], g.noEdge, g.numberOfVertices()); // 返回顶点的迭代器
} 

// 广度优先搜索
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::BFS(int v, int reach[], int label) {
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
        Iterator_AM<DataType, WeightType>* iw = myIterator(w);
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
}

// 深度优先搜索
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::DFS(int v, int reach[], int label) {
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
void AdjacencyMatrix<DataType, WeightType>::rDFS(int v, int reach[], int label) {
    reach[v] = label;
    Iterator_AM<DataType, WeightType>* iv = myIterator(v);
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
int* AdjacencyMatrix<DataType, WeightType>::findPath(int theSource, int theDestination) {
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
bool AdjacencyMatrix<DataType, WeightType>::rFindPath(int s, int reach[], int path[], int & length, int destination) {
    // 从顶点s开始实施深度优先搜索
    // 顶点s不应该等于终点
    // 当且仅当一条路径找到了，返回true

    reach[s] = 1; // 标记顶点s
    Iterator_AM<DataType, WeightType>* is = myIterator(s);
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
void AdjacencyMatrix<DataType, WeightType>::dijkstra(int start, WeightType* dist) {
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
        Iterator_AM<DataType, WeightType>* iv = myIterator(curVertex);
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
void AdjacencyMatrix<DataType, WeightType>::topologicalSort() {
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
        Iterator_AM<DataType, WeightType>* iv = myIterator(v);
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
void AdjacencyMatrix<DataType, WeightType>::prim(int start, WeightType* miniCost) {
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
        Iterator_AM<DataType, WeightType>* iv = myIterator(u);
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


// 清空邻接矩阵
template <typename DataType, typename WeightType>
void AdjacencyMatrix<DataType, WeightType>::clear() {
    // 清空邻接矩阵
    if (a != nullptr) {
        for (int i = 0; i < g.numberOfVertices(); i++) {
            delete [] a[i];
        }
        delete [] a;
    }

    return;
}

//--------------------------------------------邻接矩阵--------------------------------------------