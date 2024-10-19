#pragma once

/* 有向加权图实现 */
#include <iostream>
#include <string>
#include <iomanip>
#include <cfloat>
#include "Graph.hpp"
#include "Common.cpp"

//----------------------------------有向加权图类重写的方法-------------------------------------

// 构造函数
template <typename DataType, typename WeightType>
WDGraph<DataType, WeightType>::WDGraph(WeightType theNoEdge) {
    n = 0; // 顶点的数量
    e = 0; // 边的数量
    noEdge = theNoEdge; // 无边的标志
    vertexList = new arrayList<vertex<DataType>*>(10); // 初始化顶点列表
    edgeList = new arrayList<edge<WeightType>*>(10); // 初始化边列表
    a = nullptr; // 初始化邻接矩阵
    adjacencyTable = nullptr; // 初始化邻接表
    xList = nullptr; // 初始化十字链表
    isDirected = true; // 是有向图
    isWeighted = true; // 是加权图
};

// 析构函数
template <typename DataType, typename WeightType>
WDGraph<DataType, WeightType>::~WDGraph() {

}

// 是否存在顶点
template <typename DataType, typename WeightType>
bool WDGraph<DataType, WeightType>::existsVertex(int v) const {
    if (v < 0 || v >= n) { // 顶点索引无效
        std::ostringstream s;
        s << "Invalid vertex index! (" << v << ")";
        throw illegalParameterValue(s.str());
    }

    return true;
}

// 添加一个顶点
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::insertVertex(DataType theData) {
    // 插入顶点(插入到顶点列表的末尾)
    vertex<DataType>* v = new vertex<DataType>(n, theData);
    vertexList->insert(n, v);

    // 顶点数量加1
    n++;

    // 更新邻接矩阵
    if (a != nullptr) {
        // 删除原来的邻接矩阵
        deleteAdjacencyMatrix();

        // 生成新的邻接矩阵
        genAdjacencyMatrix();
    }
}

// 删除一个顶点 (交换并删除顶点，使得顶点ID连续)
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::eraseVertex(int v) {
    if (!existsVertex(v)) { // 检查顶点是否存在
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    // 交换顶点
    vertex<DataType>* temp = vertexList->get(n-1); // 最后一个顶点
    
    // vertexList->get(v)->ID = temp->ID; // 交换ID
    vertexList->get(v)->data = temp->data; // 交换数据

    // 更新边列表
    // 把原先与顶点v相关的边删除
    for (int i = 0; i < e; i++) {
        if ((edgeList->get(i))->fromID == v || (edgeList->get(i))->toID == v) {
            edgeList->erase(i);
            e--;
        }
    }

    // 把原先与最后一个顶点相关的边更新为顶点v
    for (int i = 0; i < e; i++) {
        if ((edgeList->get(i))->fromID == n-1) {
            (edgeList->get(i))->fromID = v;
        }

        if ((edgeList->get(i))->toID == n-1) {
            (edgeList->get(i))->toID = v;
        }
    }

    // 删除最后一个顶点
    vertexList->erase(n-1);

    // 顶点数量减1
    n--;

    return;
}

// 返回顶点的数量
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::numberOfVertices() const {
    return n;
}

// 返回边的数量
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::numberOfEdges() const {
    return e;
}

// 返回是否是有向图
template <typename DataType, typename WeightType>
bool WDGraph<DataType, WeightType>::directed() const {
    return isDirected;
}

// 返回是否是加权图
template <typename DataType, typename WeightType>
bool WDGraph<DataType, WeightType>::weighted() const {
    return isWeighted;
}

// 返回边(v1, v2)在图中时，返回值是true
template <typename DataType, typename WeightType>
bool WDGraph<DataType, WeightType>::existsEdge(int v1, int v2) const {
    checkVertexIndex(v1, v2); // 检查顶点的索引是否合法

    for (int i = 0; i < e; i++) {
        if ((*(edgeList->get(i))).fromID == v1 && (*(edgeList->get(i))).toID == v2) {
            return true;
        }
    }
    return false;
}

// 插入一条边
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::insertEdge(edge<WeightType>* theEdge) {
    checkVertexIndex(theEdge->fromID, theEdge->toID); // 检查顶点的索引是否合法

    int v1 = theEdge->fromID;
    int v2 = theEdge->toID;

    // 检查边是否存在
    if (existsEdge(v1, v2)) {
        std::cout << "Edge (" << v1 << ", " << v2 << ")" << " already exists!" << std::endl;
    }

    // 插入边
    edgeList->insert(e, theEdge);
    e++; // 边的数量加1

    // 更新邻接矩阵
    if (a != nullptr)
        a[v1][v2] = theEdge->weight;

    return;
}

// 删除一条边
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::eraseEdge(int v1, int v2) {
    checkVertexIndex(v1, v2); // 检查顶点的索引是否合法

    // 查找边(v1, v2)的索引
    int i = 0;
    for (i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            break;
        }
    }

    // 未找到边(v1, v2)
    if (i == e) {
        std::cout << "Edge (" << v1 << ", " << v2 << ")" << " does not exist!" << std::endl;
        return;
    }

    // 删除边
    edgeList->erase(i);

    // 边的数量减1
    e--;

    // 更新邻接矩阵
    if (a != nullptr)
        a[v1][v2] = noEdge;

    return;
}

// 返回顶点的入度
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::inDegree(int v) const {
    if (!existsVertex(v)) { // 检查顶点是否存在
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    int degree = 0;

    for (int i = 0; i < e; i++) {
        if ((*(edgeList->get(i))).fromID != v && (*(edgeList->get(i))).toID == v) {
            degree++;
        }
    }

    return degree;
}

// 返回顶点的出度
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::outDegree(int v) const {
    if (!existsVertex(v)) { // 检查顶点是否存在
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    int degree = 0;

    for (int i = 0; i < e; i++) {
        if ((*(edgeList->get(i))).fromID == v && (*(edgeList->get(i))).toID != v) {
            degree++;
        }
    }

    return degree;
}

// 返回顶点的度
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::degree(int v) const {
    if (!existsVertex(v)) { // 检查顶点是否存在
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    int degree = 0;
    int inD = inDegree(v);
    int outD = outDegree(v);

    degree = inD + outD;
    return degree;
}

//----------------------------------有向加权图类重写的方法-------------------------------------

//----------------------------------其他方法--------------------------------------

// 检查顶点的索引是否合法
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::checkVertexIndex(int v1, int v2) const {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2 ) {
        std::ostringstream s;
        s << "Invalid vertex index! (" << v1 << ", " << v2 << ")";
        throw illegalParameterValue(s.str()); // 顶点索引无效
    }
}

// 返回顶点的数据
template <typename DataType, typename WeightType>
DataType WDGraph<DataType, WeightType>::getVertex(int v) const {
    if (!existsVertex(v)) { // 检查顶点是否存在
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    return vertexList->get(v)->data;
}

// 设置顶点的数据
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::setVertex(int v, DataType theData) {
    if (!existsVertex(v)) { // 检查顶点是否存在
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    vertexList->get(v)->data = theData;
}

// 返回边的权重
template <typename DataType, typename WeightType>
WeightType WDGraph<DataType, WeightType>::getWeight(int v1, int v2) const {
    checkVertexIndex(v1, v2); // 检查顶点的索引是否合法

    for (int i = 0; i < e; i++) {
        if ((*(edgeList->get(i))).fromID == v1 && (*(edgeList->get(i))).toID == v2) {
            return (*(edgeList->get(i))).weight;
        }
    }

    return noEdge;
}

// 设置边的权重
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::setWeight(int v1, int v2, WeightType theWeight) {
    checkVertexIndex(v1, v2); // 检查顶点的索引是否合法

    for (int i = 0; i < e; i++) {
        if ((*(edgeList->get(i))).fromID == v1 && (*(edgeList->get(i))).toID == v2) {
            (*(edgeList->get(i))).weight = theWeight;
            return;
        }
    }

    std::cout << "Edge (" << v1 << ", " << v2 << ")" << " does not exist!" << std::endl;
    return;
}

// 打印图
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printGraph() {
    // 输出图的基本信息
    std::cout << " 图的基本信息如下: " << std::endl;
    std::cout << " 图的类型为: " << (directed() ? "有向图" : "无向图") << "," << (weighted() ? "加权图" : "无权图")  << std::endl;
    std::cout << " 顶点的数量为: " << numberOfVertices() << std::endl;
    std::cout << " 边的数量为: " << numberOfEdges() << std::endl;
    std::cout << " 无边的标志为: " << noEdge; if (noEdge == -DBL_MAX) { std::cout << " (即为负无穷) " << std::endl; } else { std::cout << std::endl; }

    // 输出顶点的信息
    std::cout << " 顶点的信息如下: " << std::endl;
    for (int i = 0; i < numberOfVertices(); i++) {
        std::cout << " Vertex " << i << ": " << " ID: " << vertexList->get(i)->ID << " Data: " << vertexList->get(i)->data << std::endl;
    }

    return; 
}

// 清空图
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::clear() {
    if (vertexList != nullptr) {
        vertexList->~arrayList();
    }

    if (edgeList != nullptr) {
        edgeList->~arrayList();
    }

    if (a != nullptr) {
        deleteAdjacencyMatrix();
    }

    if (adjacencyTable != nullptr) {
        deleteAdjacencyTable();
    }

    if (xList != nullptr) {
        deleteCrossList();
    }

    n = 0;
    e = 0;
}

//----------------------------------其他方法--------------------------------------

//-------------------------------------边列表存储结构--------------------------------------
// 打印边列表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printEdgeList() const {
    std::cout << "当前的边列表为: " << std::endl;
    for (int i = 0; i < e; i++) {
        std::cout << "Edge " << i << ": " << edgeList->get(i)->fromID << " -> " << edgeList->get(i)->toID << " weight: " << edgeList->get(i)->weight << std::endl;
    }
}

//-------------------------------------邻接矩阵存储结构--------------------------------------

// 生成邻接矩阵
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::genAdjacencyMatrix() {
    // 创建邻接矩阵
    a = new WeightType* [n]; // 创建邻接矩阵 (顶点ID从0开始)    

    // 创建二维数组
    for (int i = 0; i < n; i++) {
        a[i] = new WeightType[n]; 
    }

    // 初始化邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = noEdge; // 无边
        }
    }

    // 设置邻接矩阵的值
    for (int i = 0; i < e; i++) { // 遍历边列表edgeList
        int v1 = edgeList->get(i)->fromID;
        int v2 = edgeList->get(i)->toID;

        a[v1][v2] =  edgeList->get(i)->weight;
    }

    return;
}

// 删除邻接矩阵
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::deleteAdjacencyMatrix() {
    if (a != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] a[i];
        }

        delete [] a;
    }

    a = nullptr;

    return;
}

// 返回邻接矩阵
template <typename DataType, typename WeightType>
WeightType** WDGraph<DataType, WeightType>::getAdjacencyMatrix() const {
    return a;
}

// 打印邻接矩阵
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printAdjacencyMatrix() const{
    if (a == nullptr) {
        std::cout << "Adjacency matrix is empty!" << std::endl;
        return;
    }

    // 计算每列的最大宽度
    int* width = new int[n];
    for (int i = 0; i < n; i++) {
        width[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w = 0;
            w = std::to_string(a[i][j]).size();
            if (w > width[j]) {
                width[j] = w;
            }
        }
    }

    // 打印邻接矩阵
    std::cout << "Adjacency matrix: " << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << i << " : ";
        for (int j = 0; j < n; j++) {
            std::cout << std::left << " | " << std::setw(width[j]) << a[i][j] << " | ";
        }
        std::cout << std::endl;
    }

    return;
}

//-------------------------------------邻接矩阵存储结构--------------------------------------

//-------------------------------------迭代器--------------------------------------

// 迭代器构造函数
template <typename DataType, typename WeightType>
myIterator<DataType, WeightType>::myIterator(WeightType* theRow, WeightType theNoEdge, int numberOfVertices) {
    row = theRow;
    noEdge = theNoEdge;
    n = numberOfVertices;
    currentVertex = 0;
}

// 迭代器next函数 (返回下一个顶点，以及边的权重，若不存在，则返回-1)
template <typename DataType, typename WeightType>
int myIterator<DataType, WeightType>::next(WeightType& theWeight) {
    // 寻找下一个邻接顶点
    for (int j = currentVertex; j < n; j++)
        if (row[j] != noEdge) {
            currentVertex = j + 1;
            theWeight = row[j];
            return j;
        }

    // 不存在邻接顶点
    currentVertex = n;
    return -1;
}

//-------------------------------------迭代器--------------------------------------

//---------------------------------图的遍历---------------------------------

// 广度优先搜索
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::BFS(int v, int reach[], int label) {
    // 检查顶点v是否合法
    if (existsVertex(v) == false) {
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    // 检查label是否为0
    if (label == 0) {
        std::ostringstream s;
        s << "Label should not be 0!" << std::endl;
        throw illegalParameterValue(s.str());
    }

    // 初始化reach数组
    for (int i = 0; i < n; i++) {
        reach[i] = 0; // 把没有访问过的顶点标记为0
    }

    arrayQueue<int> q(n); // 创建队列  

    q.enqueue(v); // 把当前传入的顶点v入队
    reach[v] = label; // 标记为已访问
    
    WeightType weight; // 暂存边的权重
    while (q.empty() == false) {
        int w = q.front(); // 取出队列元素
        q.dequeue(); // 出队

        // 当前正在访问
        std::cout << "访问顶点:  " << w << std::endl;

        // 标记所有未访问的邻接于顶点w的顶点
        myIterator<DataType, WeightType>* iw  = iterator(w); // 获取顶点w的迭代器
        int u;
        while ((u = iw->next(weight)) != -1) 
            if (reach[u] == 0) { // 顶点u未访问
                q.enqueue(u); // 入队
                reach[u] = label; // 标记为已访问
            } 
        

        delete iw; // 删除迭代器
    }
}

// 深度优先搜索
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::DFS(int v, int reach[], int label) {
    // 检查顶点v是否合法
    if (existsVertex(v) == false) {
        std::ostringstream s;
        s << "Vertex " << v << " does not exist!";
        throw illegalParameterValue(s.str());
    }

    // 检查label是否为0
    if (label == 0) {
        std::ostringstream s;
        s << "Label should not be 0!" << std::endl;
        throw illegalParameterValue(s.str());
    }

    // 初始化reach数组
    for (int i = 0; i < n; i++) {
        reach[i] = 0; // 把没有访问过的顶点标记为0
    }

    // 访问顶点v
    std::cout << "访问顶点: " << v << std::endl;

    // 递归深度优先搜索
    rDFS(v, reach, label);
}

// 递归深度优先搜索
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::rDFS(int v, int reach[], int label) {
    reach[v] = label; // 标记为已访问
    myIterator<DataType, WeightType>* iv = iterator(v); // 获取顶点v的迭代器
    int u;
    WeightType weight;
    while ((u = iv->next(weight)) != -1) // 访问与v相邻的顶点
        if (reach[u] == 0) { // 顶点u未访问
            std::cout << "访问顶点: " << u << std::endl;
            rDFS(u, reach, label); // 递归访问顶点u
        }

     delete iv; // 删除迭代器
}

//---------------------------------图的遍历---------------------------------

//---------------------------------查找路径---------------------------------

// 查找路径
template <typename DataType, typename WeightType>
int* WDGraph<DataType, WeightType>::findPath(int theSource, int theDestination) {
    // 寻找一条从顶点theSource到顶点theDestination的路径，返回一个数组Path, 从索引1开始表示路径， Path[0]表示路径的长度
    // 若不存在这样的路径，则返回nullptr

    // 为寻找路径的递归算法初始化
    int n = numberOfVertices(); // 顶点的数量
    int* path = new int [n + 1]; 
    path[1] = theSource; // 路径的第一个顶点是theSource
    int length = 1; // 路径的长度
    int destination = theDestination; // 目标顶点
    int* reach = new int [n + 1]; // 标记数组
    for (int i = 0; i <= n; i++) {
        reach[i] = 0; // 初始化为0
    } 

    // 搜索路径
    if (theSource == theDestination || rFindPath(theSource, reach, path, length, destination)) {
        // 找到一条路径
        path[0] = length - 1; // 路径的长度
    } else {
        delete [] path; // 删除路径数组
        path = nullptr;
    }

    delete [] reach; // 删除标记数组
    return path;
}

// 递归查找路径
template <typename DataType, typename WeightType>
bool WDGraph<DataType, WeightType>::rFindPath(int s, int reach[], int path[], int& length, int destination) {
    // 从顶点s开始实施深度优先搜索
    // 顶点s不应该等于终点
    // 当且仅当一条路径找到了，返回true

    reach[s] = 1; // 标记顶点s为已访问
    myIterator<DataType, WeightType>* is = iterator(s); // 获取顶点s的迭代器
    int u;
    WeightType weight;
    while ((u = is->next(weight)) != 0) {
        // 访问s的一个邻接顶点
        if (reach[u] == 0) { // u是一个没有到达的顶点
            path[++length] = u; // 路径中加入u
            if (u == destination || rFindPath(u, reach, path, length, destination)) {
                return true;
            }
            // 从顶点u到终点没有路径
            length--; // 从路径中删除u
        }
    }
    
    delete is;
    return false;
}

//---------------------------------查找路径---------------------------------

//----------------------------邻接表存储结构-----------------------------
// 邻接表构造函数
template <typename vertexType, typename WeightType>
adjacencyTableNode<vertexType, WeightType>::adjacencyTableNode(vertexType* theVertex) {
    vertex = theVertex;
    next = nullptr;
}

// 生成邻接表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::genAdjacencyTable() {
    // 创建邻接表
    adjacencyTable = new adjacencyTableNode<vertex<DataType>, WeightType>* [n]; // 创建邻接表 (顶点ID从0开始)

    // 初始化邻接表 (将顶点列表中每个顶点设置到邻接表中)
    for (int i = 0; i < numberOfVertices(); i++) {
        adjacencyTable[i] = new adjacencyTableNode<vertex<DataType>, WeightType>(vertexList->get(i));
        adjacencyTable[i]->next = nullptr;
    }

    // 设置邻接表的值
    for (int i = 0; i < e; i++) { // 遍历边列表edgeList
        int v1 = edgeList->get(i)->fromID;
        int v2 = edgeList->get(i)->toID;
        WeightType theWeight = edgeList->get(i)->weight;

        // 创建邻接表节点
        adjacencyTableNode<vertex<DataType>, WeightType>* node = new adjacencyTableNode<vertex<DataType>, WeightType>(vertexList->get(v2));

        // 插入到邻接表中
        adjacencyTableNode<vertex<DataType>, WeightType>* temp = adjacencyTable[v1];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
        temp->weight = theWeight;
    }   
}

// 删除邻接表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::deleteAdjacencyTable() {
    if (adjacencyTable != nullptr) {
        for (int i = 0; i < n; i++) {
            adjacencyTableNode<vertex<DataType>, WeightType>* temp = adjacencyTable[i];
            adjacencyTableNode<vertex<DataType>, WeightType>* next = nullptr;
            while (temp != nullptr) {
                next = temp->next;
                delete temp;
                temp = next;
            }
        }
    }

    adjacencyTable = nullptr;
    // std::cout << "Delete adjacency table!" << std::endl;
}

// 打印邻接表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printAdjacencyTable() const {
    if (adjacencyTable == nullptr) {
        std::cout << "Adjacency table is empty!" << std::endl;
        return;
    }

    std::cout << "Adjacency table: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Vertex " << i << ": ";
        adjacencyTableNode<vertex<DataType>, WeightType>* temp = adjacencyTable[i];
        while (temp != nullptr) {
            std::cout << temp->vertex->ID << " ";
            temp = temp->next;
            if (temp != nullptr) {
                std::cout << " --> ";
            }
        }
        std::cout << std::endl;
    }

    return;
}

//----------------------------邻接表存储结构-----------------------------

//----------------------------十字链表存储结构-----------------------------

// 生成十字链表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::genCrossList() {
    // 检查顶点列表和边列表是否为空
    if (vertexList == nullptr || edgeList == nullptr) {
        std::cout << "VertexList or EdgeList is empty!" << std::endl;
        return;
    }

    // 创建十字链表
    if (xList != nullptr) 
        deleteCrossList();
    xList = new VexNode<vertex<DataType>, WeightType>* [n]; // 创建顶点数组

    // 初始化顶点数组
    for (int i = 0; i < n; i++) {
        xList[i] = new VexNode<vertex<DataType>, WeightType>(vertexList->get(i));
        xList[i]->firstIn = nullptr;
        xList[i]->firstOut = nullptr;
    }

    // 构建十字链表
    for (int i = 0; i < e; i++) {
        int v1 = edgeList->get(i)->fromID; // 边的起始顶点
        int v2 = edgeList->get(i)->toID; // 边的终止顶点
        WeightType theWeight = edgeList->get(i)->weight; // 边的权重

        // 创建边节点
        ArcBox<WeightType>* arc = new ArcBox<WeightType>(v1, v2, theWeight);

        // 插入到十字链表
        // 插入到顶点v1的出边链表
        if (xList[v1]->firstOut == nullptr) {
            xList[v1]->firstOut = arc;
        } else {
            ArcBox<WeightType>* temp = xList[v1]->firstOut;
            while (temp->tailLink != nullptr) {
                temp = temp->tailLink;
            }
            temp->tailLink = arc;
        }

        // 插入到顶点v2的入边链表
        if (xList[v2]->firstIn == nullptr) {
            xList[v2]->firstIn = arc;
        } else {
            ArcBox<WeightType>* temp = xList[v2]->firstIn;
            while (temp->headLink != nullptr) {
                temp = temp->headLink;
            }
            temp->headLink = arc;
        }
    }

    return;
}

// 删除十字链表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::deleteCrossList() {
    if (xList != nullptr) {
        for (int i = 0; i < n; i++) {
            ArcBox<WeightType>* temp = xList[i]->firstOut;
            ArcBox<WeightType>* next = nullptr;
            while (temp != nullptr) {
                next = temp->tailLink;
                delete temp;
                temp = next;
            }

            delete xList[i]; // Delete the VexNode object
        }
        delete[] xList; // Delete the array of VexNode pointers
    }

    xList = nullptr;
    // std::cout << "Delete cross list!" << std::endl;
}

// 打印十字链表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printCrossList() const {
    if (xList == nullptr) {
        std::cout << "Cross list is empty!" << std::endl;
        return;
    }

    std::cout << "Cross list: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Vertex " << i << ": ";
        ArcBox<WeightType>* temp = xList[i]->firstOut;
        while (temp != nullptr) {
            std::cout << "(" << temp->tailVex << ", " << temp->headVex << ", " << temp->weight << ") ";
            
            // tailLink
            temp = temp->tailLink;
            if (temp != nullptr) {
                std::cout << " --> ";
            }
        }
        std::cout << std::endl;
    }

    return;
}
//----------------------------十字链表存储结构-----------------------------



