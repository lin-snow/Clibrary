#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Common.hpp"

// 抽象迭代器类
template <typename DataType, typename WeightType>
class Iterator {
    public :
        virtual int next(WeightType& theWeight) = 0; // 返回下一个邻接顶点的ID和权重

    protected:
        WeightType noEdge; // 无边的标志
        int n; // 顶点的数量
        int currentVertex; // 当前顶点的ID
};

// 邻接矩阵迭代器类
template <typename DataType, typename WeightType>
class Iterator_AM : public Iterator<DataType, WeightType> {
    public :
        Iterator_AM(WeightType* theRow, WeightType theNoEdge, int numberOfVertices)
            : row(theRow), noEdge(theNoEdge), n(numberOfVertices), currentVertex(0) {};
        
        int next(WeightType& theWeight); // 返回下一个邻接顶点

    protected:
        WeightType* row; // 邻接矩阵的一行
        WeightType noEdge; // 无边的标志
        int n; // 顶点的数量
        int currentVertex; // 当前顶点的ID
};

// 邻接表迭代器类
template <typename DataType, typename WeightType>
class Iterator_AT : public Iterator<DataType, WeightType> {
    public :
        Iterator_AT(adjacencyTableNode<vertex<DataType>, WeightType>* theRow, WeightType theNoEdge, arrayList<vertex<DataType>*>* theVertexList)
            : row(theRow), noEdge(theNoEdge), vl(theVertexList) {};
        
        int next(WeightType& theWeight); // 返回下一个邻接顶点

    protected:
        arrayList<vertex<DataType>*>* vl; // 顶点列表
        adjacencyTableNode<vertex<DataType>, WeightType>* row; // 邻接表的一行
        WeightType noEdge; // 无边的标志
};

// 十字链表迭代器类
template <typename DataType, typename WeightType>
class Iterator_CL : public Iterator<DataType, WeightType> {
    public :
        Iterator_CL(ArcBox<WeightType>* theRow, WeightType theNoEdge, arrayList<vertex<DataType>*>* theVertexList)
            : row(theRow), noEdge(theNoEdge), vl(theVertexList) {};
        
        int next(WeightType& theWeight); // 返回下一个邻接顶点

    protected:
        arrayList<vertex<DataType>*>* vl; // 顶点列表
        ArcBox<WeightType>* row; // 十字链表的一行
        WeightType noEdge; // 无边的标志
};

#include "Iterator.hpp"