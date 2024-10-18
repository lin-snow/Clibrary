#include "Graph.hpp"
#include "Common.cpp"
#include "Exception.cpp"
#include "Graph.cpp"
#include <iostream>
#include <string>

int main() {
    // noEdge 设置为-9999.0， DataType 为 std::string, WeightType 为 float
    float noEdge = -9999.0; // 无边的标志

    std::cout << "hello world" << std::endl;


    arrayList<int>* a = new arrayList<int>(10);
    a->insert(0, 1);
    printf("%d\n", a->get(0));

    WDGraph<std::string, float> g(noEdge);

    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");

    edge<float>* e = new edge<float>(0, 1, 1.0);
    g.insertEdge(e);

    e = new edge<float>(0, 2, 2.0);
    g.insertEdge(e);

    e = new edge<float>(0, 3, 3.0);
    g.insertEdge(e);

    e = new edge<float>(0, 4, 4.0);
    g.insertEdge(e);

    e = new edge<float>(1, 2, 5.0);
    g.insertEdge(e);

    e = new edge<float>(3, 2, 6.0);
    g.insertEdge(e);

    e = new edge<float>(1, 3, 7.0);
    g.insertEdge(e);

    e = new edge<float>(2, 3, 8.0);
    g.insertEdge(e);

    e = new edge<float>(2, 4, 9.0);
    g.insertEdge(e);

    e = new edge<float>(3, 4, 10.0);
    g.insertEdge(e);

    // g.eraseVertex(4);

    // g.eraseEdge(0, 2);


    g.setWeight(0, 1, g.getWeight(0, 2) + 1.0);

    g.genAdjacencyMatrix();

    if (g.existsEdge(0, 1)) {
        std::cout << "Edge (0, 1) exists!" << std::endl;
    }

    g.printGraph();   

    g.printAdjacencyMatrix();

    int* reach = new int[g.numberOfVertices()];
    // g.BFS(0, reach, 1);
    // myIterator<std::string, float>* iw  = g.iterator(1); // 获取顶点w的迭代器
    // int u = iw->next(noEdge);
    // printf("u = %d\n", u);
    // g.DFS(0, reach, 1);

    int* path = g.findPath(0, 4);
    if (path != nullptr) {
        std::cout << "Path: ";
        for (int i = 1; i <= path[0]; i++) {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }

    g.genAdjacencyTable();
    g.printAdjacencyTable();
    g.deleteAdjacencyTable();

    g.genCrossList();
    g.printCrossList();
    g.deleteCrossList();


    system("pause");
    

    return 0;
}