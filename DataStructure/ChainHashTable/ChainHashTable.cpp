#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Status {
    OK = 1,
    TRUE = 1,
    ERROR = 0,
    FALSE = 0,
    OVERFLOW = -1
} Status;

// 定义哈希表节点结构体
typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

// 定义哈希表结构体
typedef struct {
    Node* * table;
    int size;
} HashTable;


// 哈希函数
unsigned int hash(const char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }

    return hash % size;
}

// 初始化哈希表
HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (hashTable == NULL) return NULL;
    hashTable->size = size;
    hashTable->table = (Node**)malloc(sizeof(Node*) * size);
    if (hashTable->table == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

// 插入键值对
void insert(HashTable& hashTable, const char* key, int value) {
    unsigned int index = hash(key, hashTable.size);
    Node* node = hashTable.table[index];

    // 检查是否存在相同的值
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            // 如果键已经存在,更新键值
            node->value = value;
            return;
        }
    }

    // 如果键不存在，插入新节点
    Node* newNode = hashTable.table[index];
    if (newNode == NULL) return;

    // 手动分配内存并复制字符串
    newNode->key = (char*)malloc(strlen(key) + 1);
    if (newNode->key == NULL) {
        free(newNode);
        return;
    }
    strcpy(newNode->key, key);

    newNode->value = value;
    newNode->next = hashTable.table[index];
    hashTable.table[index] = newNode;

    return;
}

// 查找键值对
Node* searchKey(HashTable& hashTable, const char* key) {
    unsigned int index = hash(key, hashTable.size);
    Node* node = hashTable.table[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node; 
        }
        node =node->next;
    }

    return NULL; // 未找到
}

// 删除键值对
Status deleteKey(HashTable& hashTable, const char * key) {
    unsigned int index = hash(key, hashTable.size);
    Node* node = hashTable.table[index];
    Node* prev = NULL;
    while (node != NULL && strcmp(node->key, key) != 0) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) return FALSE; // 未找到
    if (prev == NULL) {
        hashTable.table[index] = node->next;
    } else {
        prev->next = node->next;
    }
    free(node->key);
    free(node);
    node = NULL;

    return OK;
}

// 销毁哈希表
Status destroyHashTable(HashTable& hashTable) {
    for (int i = 0; i < hashTable.size; i++) {
        Node* node = hashTable.table[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }

    free(hashTable.table);
    free(&hashTable);

    return OK;
}

int main() {
    system("cls");


    system("pause");
    return 0;
}