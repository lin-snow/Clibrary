// --------------------------------------- 测试实现 ---------------------------------------
#pragma once

#include <iostream>
#include <string>
#include <cfloat>
#include "Common.hpp"
#include "Graph.h"

#include <fstream>

// 添加顶点
void addVertex(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 向图中添加自定义顶点  ->                                " << std::endl;
    if (graph.numberOfVertices() != 0) {
        graph.printVertices();
    }

    std::string myVertex;
    std::cout << " 请输入自定义顶点的数据: "; std::cin >> myVertex;
    graph.insertVertex(myVertex);
    std::cout << " 顶点 " << myVertex << " 已经添加到图中 " << std::endl;
}

// 添加边
void addEdge(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 向图中添加自定义边  ->                                " << std::endl;
    if (graph.numberOfEdges() != 0) {
        graph.printEdges();
    }
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int from, to;
    float weight;
    std::cout << " 请输入边的起点ID: "; std::cin >> from;
    std::cout << " 请输入边的终点ID: "; std::cin >> to;
    std::cout << " 请输入边的权重: "; std::cin >> weight;
    edge<float>* myEdge = new edge<float>(from, to, weight);
    graph.insertEdge(myEdge);
}

// 删除顶点
void deleteVertex(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 从图中删除顶点  ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int v;
    std::cout << " 请输入要删除的顶点ID: "; std::cin >> v;
    graph.eraseVertex(v);

    std::cout << "按回车继续..." << std::endl;
    getchar();
}

// 删除边
void deleteEdge(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 从图中删除边  ->                                " << std::endl;
    if (graph.numberOfEdges() == 0) {
        std::cout << "当前图中没有边！" << std::endl;
        std::cout << "请先添加边！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printEdges();
    }

    int v1, v2;
    std::cout << " 请输入要删除的边的起点ID: "; std::cin >> v1;
    std::cout << " 请输入要删除的边的终点ID: "; std::cin >> v2;
    graph.eraseEdge(v1, v2);

    std::cout << "按回车继续..." << std::endl;
    getchar();
}

// 更新顶点
void updateVertex(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 更新顶点  ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int v; std::string data;
    std::cout << " 请输入要更新的顶点ID: "; std::cin >> v;
    std::cout << " 请输入新的数据: "; std::cin >> data;
    graph.updateVertex(v, data);

    std::cout << "按回车继续..." << std::endl;
    getchar();
}

// 更新边的权重
void updateEdge(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 更新边的权重  ->                                " << std::endl;
    if (graph.numberOfEdges() == 0) {
        std::cout << "当前图中没有边！" << std::endl;
        std::cout << "请先添加边！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printEdges();
    }

    int v1, v2, weight;
    std::cout << " 请输入要更新的边的起点ID: "; std::cin >> v1;
    std::cout << " 请输入要更新的边的终点ID: "; std::cin >> v2;
    std::cout << " 请输入新的权重: "; std::cin >> weight;
    graph.setWeight(v1, v2, weight);

    std::cout << "按回车继续..." << std::endl;
    getchar();
}

// 打印图
void printGraph(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    graph.printGraph();
}

// 求顶点的度
void degreeOfVertex(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 求顶点的度 ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int v;
    std::cout << " 请输入要求度的顶点ID: "; std::cin >> v;
    std::cout << " 顶点 " << v << " 的度为 " << graph.degree(v) << std::endl;
    std::cout << " 顶点 " << v << " 的出度为 " << graph.outDegree(v) << std::endl;
    std::cout << " 顶点 " << v << " 的入度为 " << graph.inDegree(v) << std::endl;
    std::cout << " 得到的顶点的度、出度和入度来自于所有存储结构计算得到，结果一致性已得到验证才会输出！ " << std::endl;

    std::cout << "按回车继续..." << std::endl;
    getchar();
}

// 广度优先搜索
void BFS(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 广度优先搜索 ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int v;
    std::cout << " 请输入要进行广度优先搜索的起点ID: "; std::cin >> v;
    int reach[graph.numberOfVertices()];
    graph.BFS(v, reach, 4);
}

// 深度优先搜索
void DFS(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 深度优先搜索 ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int v;
    std::cout << " 请输入要进行深度优先搜索的起点ID: "; std::cin >> v;
    int reach[graph.numberOfVertices()];
    graph.DFS(v, reach, 4);
}

// 查找路径
void findPath(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 查找路径 ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int theSource, theDestination;
    std::cout << " 请输入源顶点ID: "; std::cin >> theSource;
    std::cout << " 请输入目标顶点ID: "; std::cin >> theDestination;
    graph.findPath(theSource, theDestination);
}

// 最短路径算法
void shortestPath(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 最短路径算法 ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int start;
    std::cout << " 请输入起始顶点ID: "; 
    std::cin >> start;
    graph.shortestPath(start);
    return;
}

// 拓补排序
void topologicalSort(WDGraph<std::string, float>& graph) {
    system("cls");
    std::cout << "                                 <- 拓补排序 ->                                " << std::endl;
    graph.topologicalSort();
    return;
}

// 最小生成树
void minimumSpanningTree(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 最小生成树算法 ->                                " << std::endl;
    if (graph.numberOfVertices() == 0) {
        std::cout << "当前图中没有顶点！" << std::endl;
        std::cout << "请先添加顶点！" << std::endl;
        system("pause");
        return;
    } else {
        graph.printVertices();
    }

    int start;
    std::cout << " 请输入起始顶点ID: ";
    std::cin >> start;
    graph.MST(start);
    return;
}

// 清空图
void clear(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 清空图 ->                                " << std::endl;
    std::cout << " 清空图中 ... " << std::endl;
    graph.clear();
    ProgressBar(); // 更新进度条
    std::cout << " 清空完毕" << std::endl;
}

// 退出程序
void exitProgram() {
    system("cls"); // 清屏
    std::cout << " 退出程序 " << std::endl;
    exit(0);
}

// 关于
void about() {
    system("cls"); // 清屏

    std::cout << "|---------------------------------------------------------------|" << std::endl;
    std::cout << "|           __   ___         _____       ____                   |" << std::endl;
    std::cout << "|          / /  <  /___     / ___/____  / __ \\_      __         " << std::endl;
    std::cout << "|         / /   / / __ \\    \\__ \\/ __ \\/ / / / | /| / /      " << std::endl;
    std::cout << "|        / /___/ / / / /   ___/ / / / / /_/ /| |/ |/ /          |" << std::endl;
    std::cout << "|       /_____/_/_/ /_/   /____/_/ /_/\\____/ |__/|__/           " << std::endl;
    std::cout << "|---------------------------------------------------------------|" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQ!!!QQ!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQ!!!QQ!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQQQQQQQQQQQ!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQ&&QQQ&&&QQQQQQQQQQQ!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQQQQQQQQQQQQ&&QQQ&&&QQQQQQQQQQQ!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQQQQQQQ&&QQQ&&&&&QQQ&&&&&&QQQQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&QQ&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQQQQ&&&&&TTTTTT&&&&&&&&TTTTTQQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQQQQ&&&&&TTTTTT&&&&&&&&TTTTTQQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQ&&&&&&&&QQQ666&&&&&&&&QQQ66QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQ&&&&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQ&&&&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!QQQQQ&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&QQQQQQ&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&QQQQQQ&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&QQQQQQQQ&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&&&&&&&&&&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ777&&&&&&&&&&&&&&&&&&&QQ!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&77&&&QQQQQQQQQQQQQQ!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&77&&&QQQQQQQQQQQQQQ!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&777QQQ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!QQQ&&&&&&&&QQQ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

    std::cout << "|---------------------------------------------------------------|" << std::endl;

    std::cout << "作者: L1nSn0w" << std::endl;
    std::cout << "版本: 1.0" << std::endl;
    std::cout << "日期: 2024.11.4" << std::endl;
    std::cout << "联系or反馈: hi@linsnow.cn" << std::endl;
    std::cout << "项目地址: https://github.com/lin-snow/Clibrary/tree/main/DataStructure/Graph " << std::endl;
    std::cout << "感谢您的使用！" << std::endl;

    std::cout << "|---------------------------------------------------------------|" << std::endl;

    getchar();
    return;
}

// 把图保存到txt文件中
void saveGraph(WDGraph<std::string, float>& graph) {
    // 保存顶点列表
    std::ofstream out("Data/graph_Vertex.txt");
    if (!out) {
        std::cerr << "无法打开文件" << std::endl;
        exit(1);
    }

    for (int i = 0; i < graph.numberOfVertices(); i++) {
        out << graph.getVertex(i)->data;
        if (i != graph.numberOfVertices() - 1) {
            out << std::endl; // 防止最后一行多一个换行符
        }
    }

    // 保存边列表
    std::ofstream out2("Data/graph_Edge.txt");
    if (!out2) {
        std::cerr << "无法打开文件" << std::endl;
        exit(1);
    }

    for (int i = 0; i < graph.numberOfEdges(); i++) {
        out2 << graph.getEdgeList(i)->fromID << " " << graph.getEdgeList(i)->toID << " " << graph.getEdgeList(i)->weight;
        if (i != graph.numberOfEdges() - 1) {
            out2 << std::endl; // 防止最后一行多一个换行符
        }
    }

    out.close();
    out2.close();

    // 保存进度条
    std::cout << " 保存图中 ... " << std::endl;
    ProgressBar();
    std::cout << " 保存完毕" << std::endl;
    system("pause");

    return;
}

// 从txt文件中读取图
void loadGraph(WDGraph<std::string, float>& graph) {
    // 读取顶点列表
    std::ifstream in("Data/graph_Vertex.txt");
    if (!in) {
        std::cerr << "无法打开文件" << std::endl;
        exit(1);
    }

    while (!in.eof()) {
        std::string data;
        in >> data;
        graph.insertVertex(data);
    }

    // 读取边列表
    std::ifstream in2("Data/graph_Edge.txt");
    if (!in2) {
        std::cerr << "无法打开文件" << std::endl;
        exit(1);
    }

    while (!in2.eof()) {
        int from, to;
        float weight;
        in2 >> from >> to >> weight;
        graph.insertEdge(new edge<float>(from, to, weight));
    }

    in.close();
    in2.close();

    return;
}

void showMenu(WDGraph<std::string, float>& graph) {
    system("cls"); 

    std::cout << " |----------------------------------------------------------------------------------|" << std::endl;
    std::cout << " |                    Hello, Welcome to the Graph Data Structure Test!              |" << std::endl;
    std::cout << " |----------------------------------------------------------------------------------|" << std::endl;
    std::cout << "  1.  添加顶点                                                                        "  << std::endl;
    std::cout << "  2.  添加边                                                                          "  << std::endl;
    std::cout << "  3.  删除顶点                                                                        " << std::endl;
    std::cout << "  4.  删除边                                                                          " << std::endl;
    std::cout << "  5.  更新顶点                                                                        " << std::endl;
    std::cout << "  6.  更新边的权重                                                                     " << std::endl;
    std::cout << "  7.  打印图                                                                          " << std::endl;
    std::cout << "  8.  求顶点的度                                                                       " << std::endl;
    std::cout << "  9.  广度优先搜索                                                                     " << std::endl;
    std::cout << "  10. 深度优先搜索                                                                     " << std::endl;
    std::cout << "  11. 查找路径                                                                        " << std::endl;
    std::cout << "  12. 最短路径算法                                                                     " << std::endl;
    std::cout << "  13. 拓补排序算法                                                                     " << std::endl;
    std::cout << "  14. 最小生成树算法(仅适用无向图)                                                        " << std::endl;
    std::cout << "  15. 清空图                                                                          " << std::endl;
    std::cout << "  16. 保存图到文件中                                                                    " << std::endl;
    std::cout << "  17. 退出                                                                            " << std::endl;
    std::cout << "  18. 关于                                                                            " << std::endl;
    std::cout << " |----------------------------------------------------------------------------------|" << std::endl;

    std::cout << " 请输入您要进行的操作 (1 - 18): ";

    int choice;
    std::cin >> choice;

    // 判断输入的合法性
    while ((choice < 1 || choice > 18) || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << " 请输入正确的选项 (1 - 18): ";
        std::cin >> choice;
    }

    switch (choice) {
        case 1:
            system("cls"); // 清屏
            addVertex(graph);
            break;
        case 2:
            system("cls"); // 清屏
            addEdge(graph);
            break;
        case 3:
            system("cls"); // 清屏
            deleteVertex(graph);
            break;
        case 4:
            system("cls"); // 清屏
            deleteEdge(graph);
            break;
        case 5:
            system("cls"); // 清屏
            updateVertex(graph);
            break;
        case 6:
            system("cls"); // 清屏
            updateEdge(graph);
            break;
        case 7:
            system("cls"); // 清屏
            printGraph(graph);
            break;
        case 8:
            system("cls"); // 清屏
            degreeOfVertex(graph);
            break;
        case 9:
            system("cls"); // 清屏
            BFS(graph);
            break;
        case 10:
            system("cls"); // 清屏
            DFS(graph);
            break;
        case 11:
            system("cls"); // 清屏
            findPath(graph);
            break;
        case 12:
            system("cls"); // 清屏
            shortestPath(graph);
            break;
        case 13:
            system("cls"); // 清屏
            topologicalSort(graph);
            break;
        case 14:
            system("cls"); // 清屏
            minimumSpanningTree(graph);
            break;
        case 15:
            system("cls"); // 清屏
            clear(graph);
            break;
        case 16:
            system("cls"); // 清屏
            saveGraph(graph);
            break;
        case 17:
            system("cls"); // 清屏
            exit(0);
            break;
        case 18:
            system("cls"); // 清屏
            about();
            break;
        default:
            exit(0);
            break;
    }

    std::cout << "按回车继续..." << std::endl;
    getchar();

    return;
}

// 测试图
void testGraph() {
    system("cls"); // 清屏
    std::cout << "|---------------------------------- 图数据结构的测试 ( 开始 ) ---------------------------------|" << std::endl;
    // 加载测试程序
    ProgressBar();

    // 创建一个有向加权图用于测试， 无边的标志为-DBL_MAX， 顶点数据类型为std::string， 边权重数据类型为float
    float noEdge = DBL_MAX;
    bool theDirected = true;
    bool theWeighted = true;
    std::cout << "                             <- 创建一个用于测试的图  ->                            " << std::endl;
    std::cout << " 是否使用有向图或无向图: (1: 有向图, 0: 无向图): ";
    while (true) {
        int temp;
        std::cin >> temp;
        if (temp == 1) {
            theDirected = true;
            break;
        } else if (temp == 0) {
            theDirected = false;
            break;
        } else {
            std::cout << " 请输入正确的选项 (1 or 0): ";
        }
    }
    std::cout << " 是否使用加权图或无权图: (1: 加权图, 0: 无权图): ";
    while (true) {
        int temp;
        std::cin >> temp;
        if (temp == 1) {
            theWeighted = true;
            break;
        } else if (temp == 0) {
            theWeighted = false;
            break;
        } else {
            std::cout << " 请输入正确的选项 (1 or 0): ";
        }
    }
    std::cout << "创建成功！" << std::endl;
    WDGraph<std::string, float> g(noEdge, theDirected, theWeighted);

    // 是否需要加载已有的图
    std::cout << " 是否需要加载已有的图: (1: 是, 0: 否): ";
    while (true) {
        int temp;
        std::cin >> temp;
        if (temp == 1) {
            loadGraph(g);
            break;
        } else if (temp == 0) {
            break;
        } else {
            std::cout << " 请输入正确的选项 (1 or 0): ";
        }
    }

    std::cout << "                             <- 用于测试的图的初始信息为  ->                          " << std::endl;
    std::cout << " 当前图的顶点数量为: " << g.numberOfVertices() << std::endl;
    std::cout << " 当前图的边数量为: " << g.numberOfEdges() << std::endl;
    std::cout << " 图的类型为: " << (g.directed() ? "有向图" : "无向图") << "," << (g.weighted() ? "加权图" : "无权图")  << std::endl; 
    std::cout << " 边的权重类型为：" << " float " << std::endl;
    std::cout << " 无边的标志为：" << noEdge << " (即为无穷) " << std::endl << std::endl;
    std::cout << " 默认存储结构：" << " 边列表存储 " << std::endl;
    std::cout << " 支持的额外的存储结构有: " << " 邻接矩阵, 邻接表, 十字链表 " << std::endl;
    std::cout << " -------------------------------------------------------------------------------------------" << std::endl << std::endl;

    // 回车开始测试
    std::cout << " 请按回车键开始测试 ... " << std::endl;
    std::cin.get();
    std::cin.get();
    system("cls"); // 清屏
    

    while (true) {
        showMenu(g);
    }
}




// --------------------------------------- 测试实现 ---------------------------------------

/*
//                            _ooOoo_
//                           o8888888o
//                           88" . "88
//                           (| -_- |)
//                            O\ = /O
//                        ____/`---'\____
//                      .   ' \\| |// `.
//                       / \\||| : |||// \
//                     / _||||| -:- |||||- \
//                       | | \\\ - /// | |
//                     | \_| ''\---/'' | |
//                      \ .-\__ `-` ___/-. /
//                   ___`. .' /--.--\ `. . __
//                ."" '< `.___\_<|>_/___.' >'"".
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |
//                 \ \ `-. \_ __\ /__ _/ .-` / /
//         ======`-.____`-.___\_____/___.-`____.-'======
//                            `=---='
//
//         .............................................
//                  佛祖镇楼                  BUG辟易
//          佛曰:
//                  写字楼里写字间，写字间里程序员；
//                  程序人员写程序，又拿程序换酒钱。
//                  酒醒只在网上坐，酒醉还来网下眠；
//                  酒醉酒醒日复日，网上网下年复年。
//                  但愿老死电脑间，不愿鞠躬老板前；
//                  奔驰宝马贵者趣，公交自行程序员。
//                  别人笑我忒疯癫，我笑自己命太贱；
//                  不见满街漂亮妹，哪个归得程序员？
*/