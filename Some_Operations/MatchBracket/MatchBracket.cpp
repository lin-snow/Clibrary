#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define INCREMENT 5

typedef enum Status {
    OK = 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

typedef char ElemType;

typedef struct {
    ElemType * elem;
    int top;
    int size;
    int increment;
} SqStack;

int main() {
    system("cls");

    // 函数原型
    Status Matching(char * exp, int n);
    Status InitStack_Sq(SqStack &S, int size, int inc); // 初始化顺序栈S
    Status StackEmpty_Sq(SqStack S); // 判断栈S是否为空，若空则返回TRUE,否则返回FALSE
    Status Push_Sq(SqStack &S, ElemType e); // 元素e压入栈S
    Status Pop_Sq(SqStack &S, ElemType &e); // 栈S的栈顶元素出栈，并用e返回
    Status GetTop_Sq(SqStack S, ElemType &e); // 取栈S的栈顶元素，并用e返回

    system("pause");
    return 0;
}

Status InitStack_Sq(SqStack &S, int size, int inc) {
    S.elem = (ElemType *)malloc(size * sizeof(ElemType)); // 分配存储空间
    if (S.elem == NULL) return OVERFLOW;
    S.top = 0; // 置S为空栈
    S.size = size; // 初始容量值
    S.increment = inc; // 初始增量值
    return OK;
}

Status StackEmpty_Sq(SqStack S) {
    if (S.top < 0) return ERROR;
    else if (S.top == 0) return TRUE;
    else return FALSE;
}

Status Push_Sq(SqStack &S, ElemType e) {
    ElemType * newBase;
    if (S.top >= S.size) { // 若栈顶位标已经达到了所分配的容量，则栈满，扩容
        newBase = (ElemType *)realloc(S.elem, (S.size + S.increment) * sizeof(ElemType));
        if (newBase == NULL) return OVERFLOW;
        S.elem = newBase;
        S.size += S.increment;
    } 

    S.elem[S.top++] = e; // 入栈
    return OK;
}

Status Pop_Sq(SqStack &S, ElemType &e) {
    if (StackEmpty_Sq(S)) return OVERFLOW;

    e = S.elem[--S.top];
    return OK;
}

Status GetTop_Sq(SqStack S, ElemType &e) {
    if (StackEmpty_Sq(S)) return OVERFLOW;

    e = S.elem[S.top - 1];
    return OK;
}

Status Matching(char * exp, int n) {
    SqStack matchStack;
    if (!InitStack_Sq(matchStack, MAXSIZE, INCREMENT)) {
        return FALSE;
    }

    ElemType e;
    int i = 0;
    while (i < n) {
        switch (exp[i]) {
            case '(':
            case '[':
            case '{': 
                if (!Push_Sq(matchStack, exp[i++])) return FALSE;
                break;
            case ')':
            case ']':
            case '}':   
                if (StackEmpty_Sq(matchStack) == TRUE) {
                    return FALSE;
                } else {
                    GetTop_Sq(matchStack, e);
                    if((e == '(' && exp[i] == ')') || (e == '[' && exp[i] == ']') || (e == '{' && exp[i] == '}')) {
                        Pop_Sq(matchStack, e); i++;
                    } else return FALSE;
                }
                break;
        }
    }

    if (StackEmpty_Sq(matchStack) == TRUE) return TRUE;
    else return FALSE;
}