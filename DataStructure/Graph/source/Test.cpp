 //#pragma execution_character_set("gbk") // 使用vs编译时使用的编码

#include "Graph.hpp"
#include "Common.cpp"
#include "Exception.cpp"
#include "Graph.cpp"
#include <iostream>
#include <string>
#include <cfloat>
#include <windows.h>

int main() {
    //--------------------------------- 图数据结构的测试 ---------------------------------
    system("cls"); // 清屏
    SetConsoleOutputCP(65001); // 设置控制台输出为UTF-8编码 (默认g++编译时使用)
     
    // system("mode con cols=400 lines=70"); // 设置控制台窗口大小

    // 创建一个有向加权图用于测试， 无边的标志为-DBL_MAX， 顶点数据类型为std::string， 边权重数据类型为float
    float noEdge = -DBL_MAX; 
    WDGraph<std::string, float> g(noEdge);

    std::cout << "|---------------------------------- 图数据结构的测试 ( 开始 ) ---------------------------------|" << std::endl;
    std::cout << "                            <- 用于测试的图的初始信息为  ->                          " << std::endl;
    std::cout << " 图的类型为: " << (g.directed() ? "有向图" : "无向图") << "," << (g.weighted() ? "加权图" : "无权图")  << std::endl; 
    std::cout << " 边的权重类型为：" << " float " << std::endl;
    std::cout << " 无边的标志为：" << noEdge << " (即为负无穷) " << std::endl << std::endl;
    std::cout << " 默认存储结构：" << " 边列表存储 " << std::endl;
    std::cout << " 支持的额外的存储结构有: " << " 邻接矩阵, 邻接表, 十字链表 " << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试添加顶点
    std::cout << "                                 <- 添加必要的顶点  ->                                " << std::endl;
    g.insertVertex("A"); g.insertVertex("B"); g.insertVertex("C"); g.insertVertex("D"); g.insertVertex("E"); g.insertVertex("F");
    std::cout << " 顶点 A, B, C, D, E, F 已经添加到图中 " << std::endl;
    std::cout << " 顶点的数量为: " << g.numberOfVertices() << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试添加边
    std::cout << "                                 <- 添加必要的边  ->                                " << std::endl;
    edge<float>* e1 = new edge<float>(0, 1, 1.0); g.insertEdge(e1); // A -> B
    edge<float>* e2 = new edge<float>(0, 2, 2.0); g.insertEdge(e2); // A -> C
    edge<float>* e3 = new edge<float>(1, 2, 3.0); g.insertEdge(e3); // B -> C
    edge<float>* e4 = new edge<float>(1, 3, 4.0); g.insertEdge(e4); // B -> D
    edge<float>* e5 = new edge<float>(2, 3, 5.0); g.insertEdge(e5); // C -> D
    edge<float>* e6 = new edge<float>(3, 4, 6.0); g.insertEdge(e6); // D -> E
    edge<float>* e7 = new edge<float>(4, 5, 7.0); g.insertEdge(e7); // E -> F
    edge<float>* e8 = new edge<float>(5, 0, 8.0); g.insertEdge(e8); // F -> A
    edge<float>* e9 = new edge<float>(5, 1, 9.0); g.insertEdge(e9); // F -> B
    std::cout << " 边 A -> B, A -> C, B -> C, B -> D, C -> D, D -> E, E -> F, F -> A 已经添加到图中 " << std::endl;
    std::cout << " 边的数量为: " << g.numberOfEdges() << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试打印图
    std::cout << "                                 <- 打印图  ->                                " << std::endl;
    g.printGraph();
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试设置顶点的数据
    std::cout << "                                 <- 设置顶点的数据  ->                                " << std::endl;
    g.setVertex(0, "AA"); // 设置顶点 A 的数据为 AA
    std::cout << " 顶点 A 的数据已经设置为 AA " << std::endl;
    std::cout << " 顶点 A 的数据为: " << g.getVertex(0) << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试设置边的权重
    std::cout << "                                 <- 设置边的权重  ->                                " << std::endl;
    g.setWeight(0, 1, 10.0); // 设置边 A -> B 的权重为 10.0
    std::cout << " 边 A -> B 的权重已经设置为 10.0 " << std::endl;
    std::cout << " 边 A -> B 的权重为: " << g.getWeight(0, 1) << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;
    

    // 测试删除边
    std::cout << "                                 <- 删除边  ->                                " << std::endl;
    g.eraseEdge(0, 1); // 删除边 A -> B
    std::cout << " 边 A -> B 已经从图中删除 " << std::endl;
    std::cout << " 边的数量为: " << g.numberOfEdges() << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试删除顶点
    std::cout << "                                 <- 删除顶点  ->                                " << std::endl;
    g.eraseVertex(0); // 删除顶点 A
    std::cout << " 顶点 A 已经从图中删除 " << std::endl;
    std::cout << " 顶点的数量为: " << g.numberOfVertices() << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试打印图
    std::cout << "                                 <- 打印图  ->                                " << std::endl;
    g.printGraph();
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试顶点的度
    std::cout << "                                 <- 顶点的度  ->                                " << std::endl;
    std::cout << " 顶点ID为 1 的度为: " << g.degree(1) << std::endl;
    std::cout << " 顶点ID为 1 的出度为: " << g.outDegree(1) << std::endl;
    std::cout << " 顶点ID为 1 的入度为: " << g.inDegree(1) << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试边列表存储结构
    std::cout << "                                 <- 边列表存储结构  ->                                " << std::endl;
    std::cout << " 加载边列表中 ... " << std::endl;
    ProgressBar(); // 更新进度条
    g.printEdgeList();
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试邻接矩阵存储结构
    std::cout << "                                 <- 邻接矩阵存储结构  ->                                " << std::endl;
    std::cout << " 生成邻接矩阵中 ... " << std::endl;
    g.genAdjacencyMatrix();
    ProgressBar(); // 更新进度条
    std::cout << " 生成完毕" << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试打印邻接矩阵
    std::cout << "                                 <- 打印邻接矩阵  ->                                " << std::endl;
    g.printAdjacencyMatrix();
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试删除邻接矩阵
    std::cout << "                                 <- 删除邻接矩阵  ->                                " << std::endl;
    std::cout << " 删除邻接矩阵中 ... " << std::endl;
    g.deleteAdjacencyMatrix();
    ProgressBar(); // 更新进度条
    std::cout << " 删除完毕" << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;
    
    // 测试邻接表存储结构
    std::cout << "                                 <- 邻接表存储结构  ->                                " << std::endl;
    std::cout << " 生成邻接表中 ... " << std::endl;
    g.genAdjacencyTable();
    ProgressBar(); // 更新进度条
    std::cout << " 生成完毕" << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试打印邻接表
    std::cout << "                                 <- 打印邻接表  ->                                " << std::endl;
    g.printAdjacencyTable();
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试删除邻接表
    std::cout << "                                 <- 删除邻接表  ->                                " << std::endl;
    std::cout << " 删除邻接表中 ... " << std::endl;
    g.deleteAdjacencyTable();
    ProgressBar(); // 更新进度条
    std::cout << " 删除完毕" << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试十字链表存储结构
    std::cout << "                                 <- 十字链表存储结构  ->                                " << std::endl;
    std::cout << " 生成十字链表中 ... " << std::endl;
    g.genCrossList();
    ProgressBar(); // 更新进度条
    std::cout << " 生成完毕" << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试打印十字链表
    std::cout << "                                 <- 打印十字链表  ->                                " << std::endl;
    g.printCrossList();
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试删除十字链表
    std::cout << "                                 <- 删除十字链表  ->                                " << std::endl;
    std::cout << " 删除十字链表中 ... " << std::endl;
    g.deleteCrossList();
    ProgressBar(); // 更新进度条
    std::cout << " 删除完毕" << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试图的遍历
    // 广度优先搜索
    std::cout << "                                 <- 图的遍历  ->                                " << std::endl;
    std::cout << " 广度优先搜索: " << std::endl;
    int* reach = new int[g.numberOfVertices()]; // 标记数组，用于标记顶点是否已经被访问过
    int label = 1; // 标记
    std::cout << " 从顶点 1 开始遍历: " << std::endl;
    g.BFS(1, reach, label); // 从顶点 1 开始遍历
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 深度优先搜索
    std::cout << " 深度优先搜索: " << std::endl;
    std::cout << " 从顶点 1 开始遍历: " << std::endl;
    g.DFS(1, reach, label); // 从顶点 1 开始遍历
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试查找路径
    std::cout << "                                 <- 查找路径  ->                                " << std::endl;
    std::cout << " 查找路径中..." << std::endl;
    ProgressBar(); // 更新进度条
    std::cout << " 查找完毕" << std::endl;
    int theSource = 1, theDestination = 4;
    std::cout << " 从顶点 " << theSource << "到" << theDestination << " 的路径为: " << std::endl;
    int* path = g.findPath(theSource, theDestination);
    if (path != nullptr) {
        std::cout << " 路径的长度为: " << path[0] << std::endl;
        std::cout << " 路径为: ";
        for (int i = 1; i <= path[0]; i++) {
            std::cout << path[i] << " -> ";
        }
        std::cout << theDestination <<std::endl;
    } else {
        std::cout << " 不存在这样的路径 " << std::endl;
    }
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 测试清空图
    std::cout << "                                 <- 清空图  ->                                " << std::endl;
    std::cout << " 清空图中 ... " << std::endl;
    g.clear();
    ProgressBar(); // 更新进度条
    std::cout << " 清空完毕" << std::endl;

    std::cout << "|---------------------------------- 图数据结构的测试结束 ( 结束 ) ---------------------------------|" << std::endl;

    system("pause");

    return 0;
}