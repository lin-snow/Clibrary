#pragma once

// 边类
template <typename weightType> // 权重的数据类型： int, float, double
class edge {
    public:
        int fromID; // 边连接的一个顶点的ID
        int toID; // 边连接的另一个顶点的ID
        weightType weight; // 边的权重

        // 构造函数
        edge(int theFromID, int theToID, weightType theWeight)
            : fromID(theFromID), toID(theToID), weight(theWeight) {}

        // 析构函数
        ~edge() {};
};

// 十字链表边类
template <typename WeightType>
class ArcBox {
    public:
        ArcBox(int theTailVex, int theHeadVex, WeightType theWeight)
            : tailVex(theTailVex), headVex(theHeadVex), headLink(nullptr), tailLink(nullptr), weight(theWeight) {}; // 构造函数
        int tailVex, headVex; // 弧尾和弧头对应的顶点的位置
        ArcBox<WeightType>* headLink, *tailLink; // 分别指向弧头相同和弧尾相同的下一条弧
        WeightType weight; // 边的权重
};