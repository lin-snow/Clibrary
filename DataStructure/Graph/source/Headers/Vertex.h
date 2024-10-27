#pragma once

#include "Edge.h"

// 顶点类
template <typename DataType> // 顶点的数据类型
class vertex {
    public: 
        DataType data; // 顶点的数据

        // 构造函数
        vertex(int theID, DataType theData) 
            : data(theData) {}

        // 析构函数
        ~vertex() {};
};

// 邻接表节点类
template <typename vertexType, typename WeightType>
class adjacencyTableNode {
    public:
        adjacencyTableNode(vertexType* theVertex, WeightType theWeight) 
            : vertex(theVertex), weight(theWeight), next(nullptr) {}; // 构造函数
            
        vertexType* vertex; // 顶点
        WeightType weight; // 边的权重
        adjacencyTableNode<vertexType, WeightType>* next; // 下一个邻接顶点
};

// 十字链表顶点类
template <typename vertexType, typename WeightType>
class VexNode {
    public:
        VexNode(vertexType* theVertex)
            : vertex(theVertex), firstIn(nullptr), firstOut(nullptr) {}; // 构造函数

        vertexType* vertex; // 顶点
        ArcBox<WeightType> *firstIn, *firstOut; // 分别指向该顶点第一条入弧和出弧
};