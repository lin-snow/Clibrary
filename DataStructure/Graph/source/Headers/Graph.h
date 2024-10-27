#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Iterator.h"
#include "Common.hpp"

// 图存储结构模板声明
template <typename DataType, typename WeightType>
class AdjacencyMatrix;

template <typename DataType, typename WeightType>
class AdjacencyTable;

template <typename DataType, typename WeightType>
class CrossList;

// 有向加权图类
template <typename DataType, typename WeightType>
class WDGraph {
    public:
        WDGraph(WeightType theNoEdge); // 构造函数
        ~WDGraph(); // 析构函数

        // 图本身的方法
        int numberOfVertices() const; // 返回顶点的数量
        int numberOfEdges() const; // 返回边的数量
        bool directed() const; // 当且仅当是有向图时，返回值是true
        bool weighted() const; // 当且仅当是加权图时，返回值是true

        // 顶点的方法
        void insertVertex(DataType theData); // 插入一个顶点
        void eraseVertex(int v); // 删除一个顶点
        void updateVertex(int v, DataType theData); // 更新一个顶点
        void printVertex(int v) const; // 打印一个顶点
        vertex<DataType>* getVertex(int v) const; // 获取一个顶点

        // 边的方法
        bool existEdge(int v1, int v2) const; // 当且仅当边(v1, v2)在图中时，返回值是true
        void insertEdge(edge<WeightType>* theEdge); // 插入一条边
        void eraseEdge(int v1, int v2); // 删除一条边
        void setWeight(int v1, int v2, WeightType theWeight); // 改变边的权重
        void printEdge(int v1, int v2) const; // 打印一条边
        edge<WeightType>* getEdge(int v1, int v2) const; // 获取一条边
        WeightType getWeight(int v1, int v2) const; // 返回边的权重

        // 求度
        int inDegree(int v) const; // 返回顶点的入度
        int outDegree(int v) const; // 返回顶点的出度
        int degree(int v) const; // 返回顶点的度

        // 图的遍历
        void BFS(int v, int reach[], int label); // 广度优先搜索
        void DFS(int v, int reach[], int label); // 深度优先搜索
        
        // 路径查找
        void findPath(int theSource, int theDestination); // 返回从源顶点到目标顶点的路径

        // 其他
        void printEdges() const; // 打印边列表
        void printVertices() const; // 打印顶点列表
        void printGraph() const; // 打印图
        void clear(); // 清空图

    protected:
        // 图的属性
        int n; // 顶点的数量
        int e; // 边的数量
        bool isDirected; // 是否是有向图
        bool isWeighted; // 是否是加权图
        WeightType noEdge; // 无边的标志
        arrayList<vertex<DataType>*>* vertexList; // 顶点列表 (从0开始存储，存储图中所有的顶点)
        arrayList<edge<WeightType>*>* edgeList; // 边列表 (从0开始存储，存储图中所有的边)
        
        // 图的存储结构
        friend class AdjacencyMatrix<DataType, WeightType>; // 邻接矩阵类
        AdjacencyMatrix<DataType, WeightType>* adjacencyMatrix; // 邻接矩阵

        friend class AdjacencyTable<DataType, WeightType>; // 邻接表类
        AdjacencyTable<DataType, WeightType>* adjacencyTable; // 邻接表

        friend class CrossList<DataType, WeightType>; // 十字链表类
        CrossList<DataType, WeightType>* crossList; // 十字链表
};

// 邻接矩阵类
template <typename DataType, typename WeightType>
class AdjacencyMatrix {
    public: 
        AdjacencyMatrix(WDGraph<DataType, WeightType>& g) : g(g) { // 构造函数
            a = nullptr;
        }

        // 基本操作方法
        void insertVertex(vertex<DataType>* theVertex); // 插入一个顶点
        void eraseVertex(int v); // 删除一个顶点
        bool existEdge(int v1, int v2) const; // 当且仅当边(v1, v2)在图中时，返回值是true
        void insertEdge(edge<WeightType>* theEdge); // 插入一条边
        void eraseEdge(int v1, int v2); // 删除一条边
        void setWeight(int v1, int v2, WeightType theWeight); // 改变边的权重
        WeightType getWeight(int v1, int v2) const; // 返回边的权重
        int inDegree(int v) const; // 返回顶点的入度
        int outDegree(int v) const; // 返回顶点的出度
        int degree(int v) const; // 返回顶点的度
        void printAdjacencyMatrix() const; // 打印邻接矩阵
        void deleteAdjacencyMatrix(); // 删除邻接矩阵
        

        // 返回迭代器
        Iterator_AM<DataType, WeightType>* myIterator(int theVertex);

        // // 图的遍历 
        void BFS(int v, int reach[], int label); // 广度优先搜索
        void DFS(int v, int reach[], int label); // 深度优先搜索
        void rDFS(int v, int reach[], int label); // 递归深度优先搜索

        // 路径查找
        int* findPath(int theSource, int theDestination); // 返回从源顶点到目标顶点的路径
        bool rFindPath(int s, int reach[], int path[], int& length, int destination); // 递归查找路径

        // 其他
        void clear(); // 清空邻接矩阵

        // 邻接表存储结构
        WDGraph<DataType, WeightType>& g; // 图
        WeightType** a; // 邻接矩阵(一组连续的类型为（WeightType*）的指针数组)
};

// 邻接表类
template <typename DataType, typename WeightType>
class AdjacencyTable {
    public:
        AdjacencyTable(WDGraph<DataType, WeightType>& g) : g(g) { // 构造函数
            adjacencyTable = nullptr;
        }

        // 基本操作方法
        void insertVertex(vertex<DataType>* theVertex); // 插入一个顶点
        void eraseVertex(int v); // 删除一个顶点
        bool existEdge(int v1, int v2) const; // 当且仅当边(v1, v2)在图中时，返回值是true
        void insertEdge(edge<WeightType>* theEdge); // 插入一条边
        void eraseEdge(int v1, int v2); // 删除一条边
        void setWeight(int v1, int v2, WeightType theWeight); // 改变边的权重
        WeightType getWeight(int v1, int v2) const; // 返回边的权重
        int inDegree(int v) const; // 返回顶点的入度
        int outDegree(int v) const; // 返回顶点的出度
        int degree(int v) const; // 返回顶点的度
        void printAdjacencyTable() const; // 打印邻接表
        void deleteAdjacencyTable(); // 删除邻接表

        // 返回迭代器
        Iterator_AT<DataType, WeightType>* myIterator(int theVertex);

        // 图的遍历
        void BFS(int v, int reach[], int label); // 广度优先搜索
        void DFS(int v, int reach[], int label); // 深度优先搜索
        void rDFS(int v, int reach[], int label); // 递归深度优先搜索

        // 路径查找
        int* findPath(int theSource, int theDestination); // 返回从源顶点到目标顶点的路径
        bool rFindPath(int s, int reach[], int path[], int& length, int destination); // 递归查找路径

        // 其他
        void clear(); // 清空邻接表

        // 邻接表存储结构
        WDGraph<DataType, WeightType>& g; // 图
        adjacencyTableNode<vertex<DataType>, WeightType>** adjacencyTable; // 邻接表
};

template <typename DataType, typename WeightType>
class CrossList {
    public:
        CrossList(WDGraph<DataType, WeightType>& g) : g(g) { // 构造函数
            xList = nullptr;
        }

        // 基本操作方法
        void insertVertex(vertex<DataType>* theVertex); // 插入一个顶点
        void eraseVertex(int v); // 删除一个顶点
        bool existEdge(int v1, int v2) const; // 当且仅当边(v1, v2)在图中时，返回值是true
        void insertEdge(edge<WeightType>* theEdge); // 插入一条边
        void eraseEdge(int v1, int v2); // 删除一条边
        void setWeight(int v1, int v2, WeightType theWeight); // 改变边的权重
        WeightType getWeight(int v1, int v2) const; // 返回边的权重
        int inDegree(int v) const; // 返回顶点的入度
        int outDegree(int v) const; // 返回顶点的出度
        int degree(int v) const; // 返回顶点的度
        void printCrossList() const; // 打印十字链表
        void deleteCrossList(); // 删除十字链表

        // 返回迭代器
        Iterator_CL<DataType, WeightType>* myIterator(int theVertex);

        // 图的遍历
        void BFS(int v, int reach[], int label); // 广度优先搜索
        void DFS(int v, int reach[], int label); // 深度优先搜索
        void rDFS(int v, int reach[], int label); // 递归深度优先搜索

        // 路径查找
        int* findPath(int theSource, int theDestination); // 返回从源顶点到目标顶点的路径
        bool rFindPath(int s, int reach[], int path[], int& length, int destination); // 递归查找路径

        // 其他
        void clear(); // 清空十字链表

        // 十字链表存储结构
        WDGraph<DataType, WeightType>& g; // 图
        VexNode<vertex<DataType>, WeightType>** xList; // 十字链表
};

// 图及其实现
#include "Graph.hpp"
#include "AdjacencyMatrix.hpp"
#include "AdjacencyTable.hpp"
#include "CrossList.hpp"

