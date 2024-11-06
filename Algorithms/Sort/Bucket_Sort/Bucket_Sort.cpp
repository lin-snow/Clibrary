#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls"); // 清屏

    int i, j, k;
    // 有十个人，每个人对应一个分数,分数从1到10
    int score[10] = {10,9,8,7,6,6,6,5,4,3};

    // 有十一个桶，每个桶中的计数初始化为0
    int bucket[11] = {0};

    // 每个分数对应桶的下标，出现多少次桶的计数器就为多少
    for (j = 0; j < 10; j++) {
        bucket[score[j]]++;
    }

    // 从小到大输出各个分数
    for (j = 1; j <= 10; j++) {
        for (k = 0; k < bucket[j]; k++) {
            printf("%2d ", j);
        }
    }

    system("pause");
    return 0;

}