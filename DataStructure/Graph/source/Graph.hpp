#pragma once

#include "Common.cpp" 

// 顶点类
template <typename DataType> // 顶点的数据类型
class vertex {
    public: 
        int ID; // 顶点在图中的编号
        DataType data; // 顶点的数据

        // 构造函数
        vertex(int theID, DataType theData) 
            : ID(theID), data(theData) {}

        // 析构函数
        ~vertex() {};
};

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

// 迭代器类
template <typename DataType, typename WeightType>
class myIterator {
    public :
        myIterator(WeightType* theRow, WeightType theNoEdge, int numberOfVertices);
        ~myIterator() {};
        int next(WeightType& theWeight); // 返回写一个邻接顶点的ID和权重

    protected:
        WeightType* row; // 邻接矩阵的一行
        WeightType noEdge; // 无边的标志
        int n; // 顶点的数量
        int currentVertex; // 当前顶点的ID
};

// 邻接表类
template <typename vertexType, typename WeightType>
class adjacencyTableNode {
    public:
        adjacencyTableNode(vertexType* theVertex); // 构造函数
            
        vertexType* vertex; // 顶点
        WeightType weight; // 边的权重
        adjacencyTableNode<vertexType, WeightType>* next; // 下一个邻接顶点
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

// 十字链表顶点类
template <typename vertexType, typename WeightType>
class VexNode {
    public:
        VexNode(vertexType* theVertex)
            : vertex(theVertex), firstIn(nullptr), firstOut(nullptr) {}; // 构造函数

        vertexType* vertex; // 顶点
        ArcBox<WeightType>* firstIn, *firstOut; // 分别指向该顶点第一条入弧和出弧
};

// 图的抽象类
template <typename DataType, typename WeightType> // 顶点数据类型，边权重数据类型
class graph {
    public:
        virtual ~graph() {}; // 虚析构函数

        virtual int numberOfVertices() const = 0; // 返回顶点的数量
        virtual int numberOfEdges() const = 0; // 返回边的数量
        virtual bool existsVertex(int) const = 0; // 当且仅当顶点v在图中时，返回值是true
        virtual void insertVertex(DataType) = 0; // 添加一个节点 
        virtual bool existsEdge(int, int) const = 0; // 当且仅当边(v1, v2)在图中时，返回值是true
        virtual void insertEdge(edge<WeightType>*) = 0; // 插入一条边
        virtual void eraseEdge(int, int) = 0; // 删除一条边
        virtual int degree(int) const = 0; // 返回顶点的度
        virtual int inDegree(int) const = 0; // 返回顶点的入度
        virtual int outDegree(int) const = 0; // 返回顶点的出度

        // 其他方法
        virtual bool directed() const = 0; // 当且仅当是有向图时，返回值是true
        virtual bool weighted() const = 0; // 当且仅当是加权图时，返回值是true

        

    private:
        int n; // 顶点的数量
        int e; // 边的数量
        arrayList<vertex<DataType>*>* vertexList; // 顶点列表
        arrayList<edge<WeightType>*>* edgeList; // 边列表
        WeightType noEdge; // 无边的标志
};


// 有向加权图类
template <typename DataType, typename WeightType>
class WDGraph : public graph<DataType, WeightType> {
    public:
        WDGraph(WeightType theNoEdge); // 构造函数
        ~WDGraph(); // 析构函数

        // 重写的方法
        int numberOfVertices() const; // 返回顶点的数量
        int numberOfEdges() const; // 返回边的数量
        bool directed() const; // 当且仅当是有向图时，返回值是true
        bool weighted() const; // 当且仅当是加权图时，返回值是true
        bool existsVertex(int v) const; // 当且仅当顶点v在图中时，返回值是true
        void insertVertex(DataType theData); // 添加一个节点
        void eraseVertex(int v); // 删除一个节点
        bool existsEdge(int v1, int v2) const; // 当且仅当边(v1, v2)在图中时，返回值是true
        void insertEdge(edge<WeightType>*); // 插入一条边
        void eraseEdge(int v1, int v2); // 删除一条边
        int degree(int v) const; // 返回顶点的度
        int inDegree(int v) const; // 返回顶点的入度
        int outDegree(int ) const; // 返回顶点的出度

        // 其他方法
        void printGraph(); // 打印图
        void checkVertexIndex(int v1, int v2) const; // 检查顶点的索引是否合法
        DataType getVertex(int v) const; // 返回顶点的数据
        void setVertex(int v, DataType theData); // 设置顶点的数据
        WeightType getWeight(int v1, int v2) const; // 返回边的权重
        void setWeight(int v1, int v2, WeightType theWeight); // 设置边的权重
        void clear(); // 清空图

        // 边列表存储结构
        void printEdgeList() const; // 打印边列表

        // 邻接矩阵存储结构
        void genAdjacencyMatrix(); // 生成邻接矩阵
        void deleteAdjacencyMatrix(); // 删除邻接矩阵
        void printAdjacencyMatrix() const; // 打印邻接矩阵
        WeightType** getAdjacencyMatrix() const; // 返回邻接矩阵
        
        // 邻接表存储结构
        void genAdjacencyTable(); // 生成邻接表
        void deleteAdjacencyTable(); // 删除邻接表
        void printAdjacencyTable() const; // 打印邻接表

        // 十字链表存储结构
        void genCrossList(); // 生成十字链表
        void deleteCrossList(); // 删除十字链表
        void printCrossList() const; // 打印十字链表

        // 图的遍历
        void BFS(int v, int reach[], int label); // 广度优先搜索
        void DFS(int v, int reach[], int label); // 深度优先搜索
        void rDFS(int v, int reach[], int label); // 递归深度优先搜索
        
        // 查找路径
        int* findPath(int theSource, int theDestination); // 返回从源顶点到目标顶点的路径
        bool rFindPath(int s, int reach[], int path[], int& length, int destination); // 递归查找路径

        // 迭代器
        myIterator<DataType, WeightType>* iterator(int theVertex) { // 返回顶点的迭代器
            if (existsVertex(theVertex) == false) {
                std::ostringstream s;
                s << "Vertex " << theVertex << " does not exist!";
                throw illegalParameterValue(s.str());
            }
            genAdjacencyMatrix(); // 生成最新邻接矩阵(用于迭代器)
            return new myIterator<DataType, WeightType>(a[theVertex], noEdge, n); // 返回顶点的迭代器
        }; 

    protected:
        int n; // 顶点的数量
        int e; // 边的数量
        arrayList<vertex<DataType>*>* vertexList; // 顶点列表   (从0开始存储，顶点编号从0开始)
        arrayList<edge<WeightType>*>* edgeList; // 边列表      (从0开始存储)
        WeightType** a; // 邻接矩阵(一组连续的类型为（WeightType*）的指针数组)
        adjacencyTableNode<vertex<DataType>, WeightType>** adjacencyTable; // 邻接表
        VexNode<vertex<DataType>, WeightType>** xList; // 十字链表
        WeightType noEdge; // 无边的标志
        

        bool isDirected; // 是否是有向图
        bool isWeighted; // 是否是加权图

};

