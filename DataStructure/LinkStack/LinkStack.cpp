#include <stdio.h>
#include <stdlib.h>

typedef enum Status {
    ERROR = 0,
    SUCCESS = 1
} Status;

typedef int ElemType;

typedef struct StackNode {
    ElemType data;
    struct StackNode* next;
} StackNode;

typedef struct LinkStack {
    StackNode* top;
    int count;
} LinkStack;

int main() {
    system("cls"); // 清屏

    // 链栈
    Status initLStack(LinkStack* s); // 初始化栈
    Status isEmptyLStack(LinkStack* s); // 判断栈是否为空
    StackNode* getTopNode(LinkStack* s); // 得到栈顶元素 
    Status clearLStack(LinkStack* s); // 清空栈
    Status destroyLStack(LinkStack* s); // 销毁栈
    int LStackLenght(LinkStack* s); // 检测栈长度
    Status pushLStack(LinkStack* s, ElemType e); // 入栈
    StackNode* popLStack(LinkStack* s); // 出栈
    Status printLStack(LinkStack* s); // 打印栈

    
    system("pause");
    return 0;
}

// 初始化栈
Status initLStack(LinkStack* s) {
    s->top = NULL;
    s->count = 0;
    if (s->top == NULL && s->count == 0) {
        return SUCCESS;
    } else {
        return ERROR;
    }
}

// 判断栈是否为空
Status isEmptyLStack(LinkStack* s) {
    if (s->count == 0) {
        // 空栈
        return SUCCESS;
    } else if (s > 0) {
        // 不是空栈
        return ERROR;
    }
}

// 得到栈顶元素
StackNode* getTopNode(LinkStack* s) {
    // 判断栈是否为空
    if (isEmptyLStack(s) == SUCCESS) {
        // 为空
        printf("This Stack is Empty!!!\n");
        return NULL;
    }

    // 获取栈顶元素
    if (s->top != NULL) {
        return s->top;
    }
}

// 清空栈
Status clearLStack(LinkStack* s) {
    if (isEmptyLStack(s)) {
        printf("The LinkStack is Empty!\n");
        return SUCCESS;
    }

    // 开始清空
    StackNode* FreePTR = s->top;
    while(FreePTR != NULL) {
        s->top = s->top->next;
        free(FreePTR);
        FreePTR = s->top;
        s->count--;
    }
    return SUCCESS;
}

// 销毁栈
Status destroyLStack(LinkStack* s) {
    // 先清空栈的内容
    if(clearLStack(s) == SUCCESS) {
        // 销毁栈
        free(s);
        s = NULL;
        return SUCCESS;
    }
}

// 检测栈的长度
int LStackLenght(LinkStack* s) {
    int length = 0;
    StackNode* Counter = s->top;
    while (Counter != NULL) {
        length++;
        Counter = Counter->next;
    }
    if (length == s->count) {
        return length;
    } else {
        printf("The LinkStack has wrong!!!\n");
        return -1;
    }
}

// 入栈
Status pushLStack(LinkStack* s, ElemType e) {
    // 创建结点
    StackNode* MyStackNode = (StackNode*)malloc(sizeof(StackNode));
    // 检查是否分配成功
    if (MyStackNode == NULL) {
        perror("malloc failed!!!\n");
        return ERROR;
    }

    MyStackNode->data = e;

    // 检查栈是否为空
    if (isEmptyLStack(s) == SUCCESS) {
        MyStackNode->next = NULL;
    } else {
        MyStackNode->next = s->top;
    }

    // 将栈顶指针移动到栈顶
    s->top = MyStackNode;
    // 栈内结点数加一
    s->count++;
    
    return SUCCESS;
}

// 出栈
StackNode* popLStack(LinkStack* s) {
    // 检查是否为空栈
    if (isEmptyLStack(s) == SUCCESS) {
        printf("The LinkStack is Empty!!!\n");
        return NULL;
    }

    StackNode* tempNode = s->top;
    s->top = s->top->next;

    return tempNode;
}

// 打印栈
Status printLStack(LinkStack* s) {
    // 检查是否为空栈
    if(isEmptyLStack(s) == NULL) {
        printf("The LinkStack is Empty!\n");
        return ERROR;
    } 

    StackNode* aPTR = s->top;
    while (aPTR != NULL) {
        printf("%2d \n", aPTR->data);
        aPTR = aPTR->next;
    }

    return SUCCESS;
}
