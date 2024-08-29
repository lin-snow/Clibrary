#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    // 函数原型
    void calculateChickenRabbit(int totalAnimals, int totalLegs); 

    // 鸡和兔子的总数 、 腿的总数
    int totalAnimals, totalLegs;

    // 输入鸡和兔子的总数
    printf("Please input the total number of animals: ");
    scanf("%d", &totalAnimals);

    // 输入腿的总数
    printf("Please input the total number of Legs: ");
    scanf("%d", &totalLegs);

    // 调用函数
    calculateChickenRabbit(totalAnimals, totalLegs);

    system("pause");
    return 0;
}

// 函数定义
void calculateChickenRabbit(int totalAnimals, int totalLegs) {
    // 定义变量： 鸡的数量、兔子的数量
    int chicken, rabbits;

    // 计算兔子的数量
    rabbits = (totalLegs - 2 * totalAnimals) / 2;

    // 计算鸡的数量
    chicken = totalAnimals - rabbits;

    // 检查是否有效
    if (chicken >= 0 && rabbits >= 0 && (2 * chicken + 4 * rabbits) == totalLegs) {
        printf("The number of chickens is %d. \n the number of rabbits is %d\n", chicken, rabbits);
    } else {
        printf("No solution\n");
    }
}   