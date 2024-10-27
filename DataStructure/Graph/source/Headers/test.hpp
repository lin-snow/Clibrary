// --------------------------------------- 测试实现 ---------------------------------------
#pragma once

#include <iostream>
#include <string>
#include <cfloat>
#include "Common.hpp"
#include "Graph.h"


// 添加顶点
void addVertex(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 向图中添加自定义顶点  ->                                " << std::endl;
    std::string myVertex;
    std::cout << " 请输入自定义顶点的数据: "; std::cin >> myVertex;
    graph.insertVertex(myVertex);
    std::cout << " 顶点 " << myVertex << " 已经添加到图中 " << std::endl;
}

// 添加边
void addEdge(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 向图中添加自定义边  ->                                " << std::endl;
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
    int v;
    std::cout << " 请输入要进行广度优先搜索的起点ID: "; std::cin >> v;
    int reach[graph.numberOfVertices()];
    graph.BFS(v, reach, 4);
}

// 深度优先搜索
void DFS(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 深度优先搜索 ->                                " << std::endl;
    int v;
    std::cout << " 请输入要进行深度优先搜索的起点ID: "; std::cin >> v;
    int reach[graph.numberOfVertices()];
    graph.DFS(v, reach, 4);
}

// 查找路径
void findPath(WDGraph<std::string, float>& graph) {
    system("cls"); // 清屏
    std::cout << "                                 <- 查找路径 ->                                " << std::endl;
    int theSource, theDestination;
    std::cout << " 请输入源顶点ID: "; std::cin >> theSource;
    std::cout << " 请输入目标顶点ID: "; std::cin >> theDestination;
    graph.findPath(theSource, theDestination);
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

void showMenu(WDGraph<std::string, float>& graph) {
    system("cls"); 
    std::cout << " 1. 添加顶点" << std::endl;
    std::cout << " 2. 添加边" << std::endl;
    std::cout << " 3. 删除顶点" << std::endl;
    std::cout << " 4. 删除边" << std::endl;
    std::cout << " 5. 更新顶点" << std::endl;
    std::cout << " 6. 更新边的权重 " << std::endl;
    std::cout << " 7. 打印图" << std::endl;
    std::cout << " 8. 求顶点的度" << std::endl;
    std::cout << " 9. 广度优先搜索" << std::endl;
    std::cout << " 10. 深度优先搜索" << std::endl;
    std::cout << " 11. 查找路径" << std::endl;
    std::cout << " 12. 清空图" << std::endl;
    std::cout << " 13. 退出" << std::endl;

    std::cout << " 请输入您要进行的操作 (1 - 13): ";

    int choice;
    std::cin >> choice;

    // 判断输入的合法性
    while (choice < 1 || choice > 13) {
        std::cin.get(); // 清空输入缓冲区
        std::cout << " 请输入正确的选项 (1 - 13): ";
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
            clear(graph);
            break;
        case 13:
            system("cls"); // 清屏
            exit(0);
            break;
        default:
            exit(0);
            break;
    }

    std::cout << "按回车继续..." << std::endl;
    getchar();

    return;
}


// --------------------------------------- 测试实现 ---------------------------------------
