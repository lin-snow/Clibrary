//#pragma execution_character_set("gbk") // 使用vs编译时使用的编码

#include <iostream>
#include <string>
#include <cfloat>
#include <windows.h>
#include "./Headers/Graph.h"
#include "./Headers/test.hpp"

int main() {
    system("cls"); // 清屏
    SetConsoleOutputCP(65001); // 设置控制台输出为UTF-8编码 (默认g++编译时使用)

    // 创建一个有向加权图用于测试， 无边的标志为-DBL_MAX， 顶点数据类型为std::string， 边权重数据类型为float
    float noEdge = -DBL_MAX; 
    WDGraph<std::string, float> g(noEdge);

    // 加载测试程序
    ProgressBar();
    // 回车开始测试
    std::cout << " 请按回车键开始测试 ... " << std::endl;
    std::cin.get();
    system("cls"); // 清屏


    std::cout << "|---------------------------------- 图数据结构的测试 ( 开始 ) ---------------------------------|" << std::endl;
    std::cout << "                            <- 用于测试的图的初始信息为  ->                          " << std::endl;
    std::cout << " 当前图的顶点数量为: " << g.numberOfVertices() << std::endl;
    std::cout << " 当前图的边数量为: " << g.numberOfEdges() << std::endl;
    std::cout << " 图的类型为: " << (g.directed() ? "有向图" : "无向图") << "," << (g.weighted() ? "加权图" : "无权图")  << std::endl; 
    std::cout << " 边的权重类型为：" << " float " << std::endl;
    std::cout << " 无边的标志为：" << noEdge << " (即为负无穷) " << std::endl << std::endl;
    std::cout << " 默认存储结构：" << " 边列表存储 " << std::endl;
    std::cout << " 支持的额外的存储结构有: " << " 邻接矩阵, 邻接表, 十字链表 " << std::endl;
    std::cout << " -----------------------------------------------------------------------------------" << std::endl << std::endl;

    // 回车开始测试
    std::cout << " 请按回车键开始测试 ... " << std::endl;
    std::cin.get();
    system("cls"); // 清屏

    while (true) {
        showMenu(g);
    }

    system("pause");
    return 0;
}


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