#pragma once

#include "Iterator.h"
#include "Graph.h"
#include "Common.hpp"

// 邻接矩阵迭代器
template <typename DataType, typename WeightType>
int Iterator_AM<DataType, WeightType>::next(WeightType& theWeight) {
    for (int j = currentVertex; j < n; j++) {
        if (row[j] != noEdge) {
            theWeight = row[j];
            currentVertex = j + 1;
            return j;
        }
    }

    return -1;
}

// 邻接表迭代器
template <typename DataType, typename WeightType>
int Iterator_AT<DataType, WeightType>::next(WeightType& theWeight) {
    if (row->next != nullptr) {
        theWeight = row->next->weight;
        row = row->next;
        // 返回row在顶点列表中的index
        return vl->indexOf(row->vertex);
    }

    return -1;
}

// 十字链表迭代器
template <typename DataType, typename WeightType>
int Iterator_CL<DataType, WeightType>::next(WeightType& theWeight) {
    if (row != nullptr) {
        int theNextVex = row->headVex;
        row = row->tailLink;
        return theNextVex;
    }

    return -1;
}

