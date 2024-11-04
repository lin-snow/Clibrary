#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Iterator.h"
#include "Common.hpp"

#include "Graph.h"

#include "AdjacencyMatrix.hpp"
//---------------------------------------- 图类 (构造与析构) ---------------------------------------------

// 构造函数
template <typename DataType, typename WeightType>
WDGraph<DataType, WeightType>::WDGraph(WeightType theNoEdge, bool theDirected, bool theWeighted) {
    n = 0; // 顶点的数量
    e = 0; // 边的数量
    isDirected = theDirected; // 是有向图
    isWeighted = theWeighted; // 是加权图
    noEdge = theNoEdge; // 无边的标志
    vertexList = new arrayList<vertex<DataType>*>(10); // 初始化顶点列表
    edgeList = new arrayList<edge<WeightType>*>(10); // 初始化边列表

    adjacencyMatrix = new AdjacencyMatrix<DataType, WeightType>(*this); // 初始化邻接矩阵
    adjacencyTable = new AdjacencyTable<DataType, WeightType>(*this); // 初始化邻接表
    crossList = new CrossList<DataType, WeightType>(*this); // 初始化十字链表
};

// 析构函数
template <typename DataType, typename WeightType>
WDGraph<DataType, WeightType>::~WDGraph() {

}

//------------------------------------------ 图类 (构造与析构) ---------------------------------------------

//------------------------------------------ 图类 (图本身的方法) -------------------------------------------
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

//------------------------------------------ 图类 (图本身的方法) -------------------------------------------

//------------------------------------------ 图类 (顶点的方法) -------------------------------------------
// 插入一个顶点
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::insertVertex(DataType theData) {
    vertex<DataType>* theVertex = new vertex<DataType>(n, theData); // 创建一个新的顶点
    vertexList->insert(n, theVertex); // 将新的顶点插入到顶点列表中

    // 邻接矩阵存储结构
    adjacencyMatrix->insertVertex(theVertex); // 插入一个顶点

    // 邻接表存储结构
    adjacencyTable->insertVertex(theVertex); // 插入一个顶点

    // 十字链表存储结构
    crossList->insertVertex(theVertex); // 插入一个顶点

    n++; // 顶点数量加一

    return;
}

// 删除一个顶点
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::eraseVertex(int v) {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return;
    }

    // 邻接矩阵存储结构
    adjacencyMatrix->eraseVertex(v); // 删除一个顶点

    // 邻接表存储结构
    adjacencyTable->eraseVertex(v); // 删除一个顶点

    // 十字链表存储结构
    crossList->eraseVertex(v);

    // 删除边
    int delCount = 0;
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v) delCount++;
        if (edgeList->get(i)->toID == v) delCount++;
    }

    int* delEdges = new int[delCount];
    for (int i = 0, j = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v || edgeList->get(i)->toID == v) {
            delEdges[j] = i;
            j++;
        }
    }

    for (int i = 0; i < delCount; i++) {
        edgeList->erase(delEdges[i]-i);
    }

    e -= delCount;

    // 把所有大于v的顶点索引减一
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID > v) edgeList->get(i)->fromID--;
        if (edgeList->get(i)->toID > v) edgeList->get(i)->toID--;
    }

    delete [] delEdges;

    // 删除顶点
    vertexList->erase(v); // 删除一个顶点

    n--; // 顶点数量减一

    std::cout << "顶点 " << v << " 删除成功!" << std::endl;

    return;
}

// 更新一个顶点
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::updateVertex(int v, DataType theData) {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return;
    }

    // 更新顶点
    vertexList->get(v)->data = theData;

    std::cout << "顶点 " << v << " 更新成功!" << std::endl;

    return;
}

// 打印一个顶点
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printVertex(int v) const {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return;
    }

    // 打印顶点
    std::cout << "Vertex " << v << ": " << vertexList->get(v)->data << std::endl;

    return;
}

// 获取一个顶点
template <typename DataType, typename WeightType>
vertex<DataType>* WDGraph<DataType, WeightType>::getVertex(int v) const {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index!" << std::endl;
        return nullptr;
    }

    return vertexList->get(v);
}
//------------------------------------------ 图类 (顶点的方法) -------------------------------------------

//------------------------------------------ 图类 (边的方法) -------------------------------------------
// 存在一条边
template <typename DataType, typename WeightType>
bool WDGraph<DataType, WeightType>::existEdge(int v1, int v2) const {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return false;
    }

    bool exist = false;

    // 边列表存储结构
    bool exist_EL = false;
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            exist_EL = true;
        }
    }

    // 邻接矩阵存储结构
    bool exist_AM = adjacencyMatrix->existEdge(v1, v2); 

    // 邻接表存储结构
    bool exist_AT = adjacencyTable->existEdge(v1, v2);

    // 十字链表存储结构
    bool exist_CL = crossList->existEdge(v1, v2);

    if (exist_EL == true && exist_AM == true && exist_AT == true && exist_CL == true) {
        exist = true;
    } else {
        exist = false;
    }

    return exist;
}

// 插入一条边
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::insertEdge(edge<WeightType>* theEdge) {
    if (theEdge->fromID < 0 || theEdge->fromID >= n || theEdge->toID < 0 || theEdge->toID >= n || theEdge->fromID == theEdge->toID) {
        std::cout << "Invalid vertex index! (" << theEdge->fromID << ", " << theEdge->toID << ")" << std::endl;
        system("pause");
        return;
    }

    // 检查边是否存在
    if (existEdge(theEdge->fromID, theEdge->toID) == true) {
        std::cout << "边 (" << theEdge->fromID << ", " << theEdge->toID << ") 已经存在!" << std::endl;
        return;
    }

    // 边列表存储结构
    edgeList->insert(e, theEdge); // 插入一条边
    if (isDirected == false) {
        edge<WeightType>* reverseEdge = new edge<WeightType>(theEdge->toID, theEdge->fromID, theEdge->weight);
        edgeList->insert(e+1, reverseEdge); // 插入一条边
    }

    // 邻接矩阵存储结构
    adjacencyMatrix->insertEdge(theEdge); // 插入一条边
    if (isDirected == false) {
        edge<WeightType>* reverseEdge = new edge<WeightType>(theEdge->toID, theEdge->fromID, theEdge->weight);
        adjacencyMatrix->insertEdge(reverseEdge); // 插入一条边
    }

    // 邻接表存储结构
    adjacencyTable->insertEdge(theEdge); // 插入一条边
    if (isDirected == false) {
        edge<WeightType>* reverseEdge = new edge<WeightType>(theEdge->toID, theEdge->fromID, theEdge->weight);
        adjacencyTable->insertEdge(reverseEdge); // 插入一条边
    }

    // 十字链表存储结构
    crossList->insertEdge(theEdge); // 插入一条边
    if (isDirected == false) {
        edge<WeightType>* reverseEdge = new edge<WeightType>(theEdge->toID, theEdge->fromID, theEdge->weight);
        crossList->insertEdge(reverseEdge); // 插入一条边
    }

    e++; // 边数量加一
    if (isDirected == false) e++; // 无向图边数量加一

    std::cout << "边 (" << theEdge->fromID << ", " << theEdge->toID << ") 添加成功!" << std::endl;

    system("pause");

    return;
}

// 设置边的权重
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::setWeight(int v1, int v2, WeightType theWeight) {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return;
    }

    // 检查边是否存在
    if (existEdge(v1, v2) == false) {
        std::cout << "边 (" << v1 << ", " << v2 << ") 不存在!" << std::endl;
        return;
    }

    // 边列表存储结构
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            edgeList->get(i)->weight = theWeight;
            break;
        }
    }

    // 邻接矩阵存储结构
    adjacencyMatrix->setWeight(v1, v2, theWeight);

    // 邻接表存储结构
    adjacencyTable->setWeight(v1, v2, theWeight);

    // 十字链表存储结构
    crossList->setWeight(v1, v2, theWeight);

    std::cout << "边 (" << v1 << ", " << v2 << ") 的权重设置成功!" << std::endl;

    system("pause");

    return;
}


// 删除一条边
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::eraseEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2) {
        std::cout << "Invalid vertex index ! (" << v1 << ", " << v2 << ")" << std::endl;
        return;
    }

    // 检查边是否存在
    if (existEdge(v1, v2) == false) {
        std::cout << "边 (" << v1 << ", " << v2 << ") 不存在!" << std::endl;
        return;
    }

    // 边列表存储结构
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            edgeList->erase(i); // 删除一条边
            break;
        }
    }

    // 邻接矩阵存储结构
    adjacencyMatrix->eraseEdge(v1, v2);

    // 邻接表存储结构
    adjacencyTable->eraseEdge(v1, v2);

    // 十字链表存储结构
    crossList->eraseEdge(v1, v2);

    e--; // 边数量减一

    std::cout << "边 (" << v1 << ", " << v2 << ") 删除成功!" << std::endl;

    system("pause");

    return;
}

// 打印一条边
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printEdge(int v1, int v2) const {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return;
    }

    // 边列表存储结构
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            std::cout << "Edge (" << v1 << ", " << v2 << "): " << edgeList->get(i)->weight << std::endl;
            return;
        }
    }

    // 边不存在
    std::cout << "边 (" << v1 << ", " << v2 << ") 不存在!" << std::endl;

    system("pause");
}

// 获取一条边
template <typename DataType, typename WeightType>
edge<WeightType>* WDGraph<DataType, WeightType>::getEdge(int v1, int v2) const {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return nullptr;
    }

    // 边列表存储结构
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            return edgeList->get(i);
        }
    }

    // 边不存在
    std::cout << "边 (" << v1 << ", " << v2 << ") 不存在!" << std::endl;
    system("pause");

    return nullptr;
}

// 返回边的权重
template <typename DataType, typename WeightType>
WeightType WDGraph<DataType, WeightType>::getWeight(int v1, int v2) const {
    if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n || v1 == v2) {
        std::cout << "Invalid vertex index! (" << v1 << ", " << v2 << ")" << std::endl;
        return noEdge;
    }

    // 检查边是否存在
    if (existEdge(v1, v2) == false) {
        std::cout << "边 (" << v1 << ", " << v2 << ") 不存在!" << std::endl;
        return noEdge;
    }

    WeightType weight = noEdge;

    // 边列表存储结构
    WeightType weight_EL;
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v1 && edgeList->get(i)->toID == v2) {
            weight_EL = edgeList->get(i)->weight;
            break;
        }
    }

    // 邻接矩阵存储结构
    WeightType weight_AM = adjacencyMatrix->getWeight(v1, v2);

    // 邻接表存储结构
    WeightType weight_AT = adjacencyTable->getWeight(v1, v2);

    // 十字链表存储结构
    WeightType weight_CL = crossList->getWeight(v1, v2);

    if (weight_EL != weight_AM || weight_EL != weight_AT || weight_AM != weight_AT || weight_EL != weight_CL || weight_AM != weight_CL || weight_AT != weight_CL) {
        std::cout << "Error: weight_EL != weight_AM != weight_AT != weight_CL!" << std::endl;
    } else {
        weight = weight_EL = weight_AM = weight_AT = weight_CL;
        return weight;
    }

    return noEdge;
}

//------------------------------------------ 图类 (边的方法) -------------------------------------------

//------------------------------------------ 图类 (度的方法) -------------------------------------------
// 返回顶点的入度
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::inDegree(int v) const {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return -1;
    }

    int inDegree = 0;

    // 边列表存储结构
    int inDegree_EL = 0;
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->toID == v) 
            inDegree_EL++;
    }

    // 邻接矩阵存储结构
    int inDegree_AM = 0;
    inDegree_AM = adjacencyMatrix->inDegree(v);

    // 邻接表存储结构
    int inDegree_AT = 0;
    inDegree_AT = adjacencyTable->inDegree(v);

    // 十字链表存储结构
    int inDegree_CL = 0;
    inDegree_CL = crossList->inDegree(v);
    
    if (inDegree_EL != inDegree_AM || inDegree_EL != inDegree_AT || inDegree_AM != inDegree_AT || inDegree_EL != inDegree_CL || inDegree_AM != inDegree_CL || inDegree_AT != inDegree_CL) {
        std::cout << "Error: inDegree_EL != inDegree_AM != inDegree_AT != inDegree_CL!" << std::endl;
    } else {
        inDegree = inDegree_EL = inDegree_AM = inDegree_AT = inDegree_CL;
    }

    // printf("inDegree_EL: %d, inDegree_AM: %d, inDegree_AT: %d, inDegree_CL: %d\n", inDegree_EL, inDegree_AM, inDegree_AT, inDegree_CL);

    return inDegree;
}

// 返回顶点的出度
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::outDegree(int v) const {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return -1;
    }

    int outDegree = 0;

    // 边列表存储结构
    int outDegree_EL = 0;
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v)
            outDegree_EL++;
    }

    // 邻接矩阵存储结构
    int outDegree_AM = 0;
    outDegree_AM = adjacencyMatrix->outDegree(v);

    // 邻接表存储结构
    int outDegree_AT = 0;
    outDegree_AT = adjacencyTable->outDegree(v);

    // 十字链表存储结构
    int outDegree_CL = 0;
    outDegree_CL = crossList->outDegree(v);

    // 检查两种存储结构的出度是否相等
    if (outDegree_EL != outDegree_AM || outDegree_EL != outDegree_AT || outDegree_AM != outDegree_AT || outDegree_EL != outDegree_CL || outDegree_AM != outDegree_CL || outDegree_AT != outDegree_CL) {
        std::cout << "Error: outDegree_EL != outDegree_AM != outDegree_AT != outDegree_CL!" << std::endl;
    } else {
        outDegree = outDegree_EL = outDegree_AM = outDegree_AT = outDegree_CL;
    }

    // printf("outDegree_EL: %d, outDegree_AM: %d, outDegree_AT: %d, outDegree_CL: %d\n", outDegree_EL, outDegree_AM, outDegree_AT, outDegree_CL);

    return outDegree;
}

// 返回顶点的度
template <typename DataType, typename WeightType>
int WDGraph<DataType, WeightType>::degree(int v) const {
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        return -1;
    }

    int degree = 0;

    // 边列表存储结构
    int degree_EL = 0;
    for (int i = 0; i < e; i++) {
        if (edgeList->get(i)->fromID == v || edgeList->get(i)->toID == v)
            degree_EL++;
    }

    // 邻接矩阵存储结构
    int degree_AM = 0;
    degree_AM = adjacencyMatrix->degree(v);

    // 邻接表存储结构
    int degree_AT = 0;
    degree_AT = adjacencyTable->degree(v);

    // 十字链表存储结构
    int degree_CL = 0;
    degree_CL = crossList->degree(v);

    // 检查两种存储结构的度是否相等
    if (degree_EL != degree_AM || degree_EL != degree_AT || degree_AM != degree_AT || degree_EL != degree_CL || degree_AM != degree_CL || degree_AT != degree_CL) {
        std::cout << "Error: degree_EL != degree_AM != degree_AT != degree_CL" << std::endl;
    } else {
        degree = degree_EL = degree_AM = degree_AT = degree_CL;
    }

    // printf("degree_EL: %d, degree_AM: %d, degree_AT: %d, degree_CL: %d\n", degree_EL, degree_AM, degree_AT, degree_CL);

    return degree;
}


//------------------------------------------ 图类 (度的方法) -------------------------------------------

//------------------------------------------ 图类 (图的遍历) -------------------------------------------
// 广度优先搜索
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::BFS(int v, int reach[], int label) {
    // 检查顶点索引是否有效
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        system("pause");
        return;
    }

    // 检查label是否有效
    if (label == 0) {
        std::cout << "label should not be 0 !" << label << std::endl;
        system("pause");
        return;
    }

    // 选择想要使用的存储结构的广度优先搜索
    int choice = 0;
    std::cout << "请选择使用的存储结构：" << std::endl;
    std::cout << "1. 邻接矩阵存储结构" << std::endl;
    std::cout << "2. 邻接表存储结构" << std::endl;
    std::cout << "3. 十字链表存储结构" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "使用邻接矩阵存储结构：" << std::endl;
            adjacencyMatrix->BFS(v, reach, label);
            break;
        case 2:
            std::cout << "使用邻接表存储结构：" << std::endl;
            adjacencyTable->BFS(v, reach, label);
            break;
        case 3:
            std::cout << "使用十字链表存储结构：" << std::endl;
            crossList->BFS(v, reach, label);
            break;
        default:
            std::cout << "请输入正确的选项 (1 - 3)! " << choice << std::endl;
            break;
    }

    std::cout << " 请按回车键继续 ... " << std::endl;
    std::cin.get();
    std::cin.get();
    
    return;
}

// 深度优先搜索
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::DFS(int v, int reach[], int label) {
    // 检查顶点索引是否有效
    if (v < 0 || v >= n) {
        std::cout << "Invalid vertex index! " << v << std::endl;
        system("pause");
        return;
    }

    // 检查label是否有效
    if (label == 0) {
        std::cout << "label should not be 0 !" << label << std::endl;
        system("pause");
        return;
    }

    // 选择想要使用的存储结构的深度优先搜索
    int choice = 0;
    std::cout << "请选择使用的存储结构：" << std::endl;
    std::cout << "1. 邻接矩阵存储结构" << std::endl;
    std::cout << "2. 邻接表存储结构" << std::endl;
    std::cout << "3. 十字链表存储结构" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "使用邻接矩阵存储结构：" << std::endl;
            adjacencyMatrix->DFS(v, reach, label);
            break;
        case 2:
            std::cout << "使用邻接表存储结构：" << std::endl;
            adjacencyTable->DFS(v, reach, label);
            break;
        case 3:
            std::cout << "使用十字链表存储结构：" << std::endl;
            crossList->DFS(v, reach, label);
            break;
        default:
            std::cout << "请输入正确的选项 (1 - 3)! " << choice << std::endl;
            break;
    }

    std::cout << " 请按回车键继续 ... " << std::endl;
    std::cin.get();
    std::cin.get();

    return;
}

//------------------------------------------ 图类 (图的遍历) -------------------------------------------

//------------------------------------------ 图类 (路径查找) -------------------------------------------
// 路径查找
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::findPath(int theSource, int theDestination) {
    // 寻找一条从顶点theSource到顶点theDestination的路径，返回一个数组Path, 从索引1开始表示路径， Path[0]表示路径的长度
    // 若不存在这样的路径，则返回nullptr

    int* path = nullptr;

    // 选择想要使用的存储结构的路径查找
    int choice = 0;
    std::cout << "请选择想要使用的存储结构：" << std::endl;
    std::cout << "1. 邻接矩阵存储结构" << std::endl;
    std::cout << "2. 邻接表存储结构" << std::endl;
    std::cout << "3. 十字链表存储结构" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "使用邻接矩阵存储结构：" << std::endl;
            path = adjacencyMatrix->findPath(theSource, theDestination);
            break;
        case 2:
            std::cout << "使用邻接表存储结构：" << std::endl;
            path = adjacencyTable->findPath(theSource, theDestination);
            break;
        case 3:
            std::cout << "使用十字链表存储结构：" << std::endl;
            path = crossList->findPath(theSource, theDestination);
            break;
        default:
            std::cout << "请输入正确的选项 (1 - 3)! " << choice << std::endl;
            break;
    }

    // 打印路径
    if (path != nullptr) {
        std::cout << " 路径长度为：" << path[0] << std::endl;
        std::cout << " 的路径是： " << std::endl;
        for (int i = 1; i <= path[0]; i++) {
            std::cout << path[i] << " -> ";
        }
        std::cout << theDestination << std::endl;
    } else {
        std::cout << "从顶点 " << theSource << " 到顶点 " << theDestination << " 的路径不存在！" << std::endl;
    }

    std::cout << " 请按回车键继续 ... " << std::endl;
    std::cin.get();
    std::cin.get();

    // 释放内存
    delete[] path;

    return;
}

//------------------------------------------ 图类 (路径查找) -------------------------------------------

//------------------------------------------ 图类 (最短路径) -------------------------------------------
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::shortestPath(int start) {
    // 检查起始顶点的索引是否有效
    if (start < 0 || start >= n) {
        std::cout << "Invalid vertex index! " << start << std::endl;
        system("pause");
        return;
    }

    WeightType *dist = new WeightType[n]; // 存储从起始顶点到各个顶点的最短路径长度
    for (int i = 0; i < n; i++) dist[i] = noEdge; // 初始化为无穷大
    dist[start] = 0; // 起点距离设置为0

    // 选择想要使用的存储结构的最短路径查找
    int choice = 0;
    std::cout << "1. 邻接矩阵存储结构" << std::endl;
    std::cout << "2. 邻接表存储结构" << std::endl;
    std::cout << "3. 十字链表存储结构" << std::endl;
    std::cout << "请选择想要使用的存储结构：" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "使用邻接矩阵存储结构：" << std::endl;
            adjacencyMatrix->dijkstra(start, dist);
            break;
        case 2:
            std::cout << "使用邻接表存储结构：" << std::endl;
            adjacencyTable->dijkstra(start, dist);
            break;
        case 3:
            std::cout << "使用十字链表存储结构：" << std::endl;
            crossList->dijkstra(start, dist);
            break;
        default:
            std::cout << "请输入正确的选项 (1 - 3)! " << choice << std::endl;
            break;
    }

    // 打印最短路径
    std::cout << "从顶点 " << start << "(" << vertexList->get(start)->data << ")" << " 到各个顶点的最短路径长度为：" << std::endl;
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        if (dist[i] == noEdge) {
            std::cout << "到顶点 " << i << "(" << vertexList->get(i)->data << ")" << " 不存在路径！" << std::endl;
        } else {
            std::cout << "到顶点 " << i << "(" << vertexList->get(i)->data << ")" << " 的最短路径长度为：" << dist[i] << std::endl;
        }
    }

    system("pause");

    return;
}

//------------------------------------------ 图类 (最短路径) -------------------------------------------

//------------------------------------------ 图类 (拓补排序) -------------------------------------------
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::topologicalSort() {
    // 检查当前是否为有向图
    if (directed() == false) {
        std::cout << "当前图为无向图，拓扑排序算法只能应用于有向图！" << std::endl;
        system("pause");
        return;
    }

    // 选择想要使用的存储结构的拓扑排序
    int choice = 0;
    std::cout << "1. 邻接矩阵存储结构" << std::endl;
    std::cout << "2. 邻接表存储结构" << std::endl;
    std::cout << "3. 十字链表存储结构" << std::endl;
    std::cout << "请选择想要使用的存储结构：" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "使用邻接矩阵存储结构：" << std::endl;
            adjacencyMatrix->topologicalSort();
            break;
        case 2:
            std::cout << "使用邻接表存储结构：" << std::endl;
            adjacencyTable->topologicalSort();
            break;
        case 3:
            std::cout << "使用十字链表存储结构：" << std::endl;
            crossList->topologicalSort();
            break;
        default:
            std::cout << "请输入正确的选项 (1 - 3)! " << choice << std::endl;
            break;
    }

    std::cout << std::endl;
    system("pause");

    return;
}
//------------------------------------------ 图类 (拓补排序) -------------------------------------------

//------------------------------------------ 图类 (最小生成树) -------------------------------------------
// 最小生成树
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::MST(int start) {
    // 检查当前是否为无向图
    if (directed() == true) {
        std::cout << "当前图为有向图，Prim算法只能应用于无向图！" << std::endl;
        system("pause");
        return;
    }

    // 检查起始顶点的索引是否有效
    if (start < 0 || start >= n) {
        std::cout << "Invalid vertex index! " << start << std::endl;
        return;
    }

    // 创建一个数组，存储从起始顶点到各个顶点的最小权重
    WeightType *miniCost = new WeightType[n];

    // 选择想要使用的存储结构的最小生成树
    int choice = 0;
    std::cout << "1. 邻接矩阵存储结构" << std::endl;
    std::cout << "2. 邻接表存储结构" << std::endl;
    std::cout << "3. 十字链表存储结构" << std::endl;
    std::cout << "请选择想要使用的存储结构：" << std::endl; 
    std::cin >> choice;
    

    switch (choice) {
        case 1:
            std::cout << "使用邻接矩阵存储结构：" << std::endl;
            adjacencyMatrix->prim(start, miniCost);
            break;
        case 2:
            std::cout << "使用邻接表存储结构：" << std::endl;
            adjacencyTable->prim(start, miniCost);
            break;
        case 3:
            std::cout << "使用十字链表存储结构：" << std::endl;
            crossList->prim(start, miniCost);
            break;
        default:
            std::cout << "请输入正确的选项 (1 - 3)! " << choice << std::endl;
            break;
    }

    // 输出最小生成树
    std::cout << "最小生成树的权重为：" << std::endl;
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        if (miniCost[i] == noEdge) {
            std::cout << "顶点 " << i << "(" << vertexList->get(i)->data << ")" << " 不存在路径！" << std::endl;
        } else {
            std::cout << "顶点 " << i << "(" << vertexList->get(i)->data << ")" << " 的最小权重为：" << miniCost[i] << std::endl;
        }
    }

    system("pause");

    return;
}


//------------------------------------------ 图类 (最小生成树) -------------------------------------------

//----------------------------------------------- 其他 ------------------------------------------------
// 打印边列表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printEdges() const {
    std::cout << "当前边列表中有： " << std::endl;
    for (int i = 0; i < e; i++) {
        std::cout << "边 (" << edgeList->get(i)->fromID << " --> " << edgeList->get(i)->toID << "): " << edgeList->get(i)->weight << std::endl;
    }

    return;
}

// 打印顶点列表
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printVertices() const {
    std::cout << "当前顶点列表中有：" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "顶点 ID " << i << ": " << vertexList->get(i)->data << std::endl;
    }

    return;
}

// 打印图
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::printGraph() const {
    std::cout << "|---------------------------------- 当前图的信息为 ---------------------------------|" << std::endl;
    std::cout << " 顶点的数量为：" << n << std::endl;
    std::cout << " 边的数量为：" << e << std::endl;
    std::cout << " 图的类型为: " << (directed() ? "有向图" : "无向图") << "," << (weighted() ? "加权图" : "无权图")  << std::endl; 
    std::cout << " 边的权重类型为：" << " float " << std::endl;
    std::cout << " 无边的标志为：" << noEdge << " (即为负无穷) " << std::endl << std::endl;
    std::cout << " 默认存储结构：" << " 边列表存储 " << std::endl;
    std::cout << " 支持的额外的存储结构有: " << " 邻接矩阵, 邻接表, 十字链表 " << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 输入回车继续
    std::cout << "按回车继续..." << std::endl;
    getchar();

    // 打印顶点列表
    printVertices(); // 打印顶点列表

    // 输入回车继续
    std::cout << "按回车继续..." << std::endl;
    getchar();

    // 打印边列表
    printEdges(); // 打印边列表

    // 输入回车继续
    std::cout << "按回车继续..." << std::endl;
    getchar();

    // 邻接矩阵存储结构
    adjacencyMatrix->printAdjacencyMatrix(); // 打印邻接矩阵

    // 输入回车继续
    std::cout << "按回车继续..." << std::endl;
    getchar();

    // 邻接表存储结构
    adjacencyTable->printAdjacencyTable(); // 打印邻接表

    // 输入回车继续
    std::cout << "按回车继续..." << std::endl;
    getchar();

    // 十字链表存储结构
    crossList->printCrossList(); // 打印十字链表

    // 输入回车继续
    std::cout << "按回车继续..." << std::endl;
    getchar();

    return;
}

// 清空图
template <typename DataType, typename WeightType>
void WDGraph<DataType, WeightType>::clear() {
    // 清空顶点
    vertexList->~arrayList();

    // 清空边
    edgeList->~arrayList();

    // 清空邻接矩阵存储结构
    adjacencyMatrix->clear();

    // 清空邻接表存储结构
    adjacencyTable->clear();

    // 清空十字链表存储结构
    crossList->clear();

    

    n = 0; // 顶点数量清零
    e = 0; // 边数量清零

    return;
}

//----------------------------------------------- 其他 ------------------------------------------------