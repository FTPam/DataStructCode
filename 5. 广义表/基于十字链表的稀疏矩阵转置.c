#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//定义矩阵元素的数据类型
typedef int elemType;
//定义稀疏矩阵的节点结构体
typedef struct MartrixNode {
    int row, col;
    elemType data;
    struct MartrixNode* right, * down;
}mNode;
//定义十字链表结构体
typedef struct crossList {
    mNode* cHead, * rHead;
    int row, col, nonZero;
}cList, list;
//创建并返回一个十字链表的节点
mNode* createNode(int row, int col, elemType data) {
    mNode *node = (mNode*)malloc(sizeof(mNode));
    if (node == NULL)
        exit(0);
    node->row = row;
    node->col = col;
    node->data = data;
    node->right = NULL;
    node->down = NULL;
    return node;
}
//建立十字链表
cList* createList(int row, int col) {
    cList *h= (cList*)malloc(sizeof(cList));
    if (h == NULL)
        exit(0);
    h->row = row;
    h->col = col;
    h->nonZero = 0;
    //分配一连串的行头节点空间,
    mNode* down = (mNode*)malloc(row * sizeof(mNode));
    //分配一连串的列头节点空间
    mNode* right = (mNode*)malloc(col * sizeof(mNode));
    //判断空间是否分配成功
    if (!down || !right) {
        printf("error00000: STACK OVERFLOW");
        exit(0);
    }
    //分配成功则开始初始化
    h->cHead = right;
    for (int i = 0; i < col; i++) {
        right[i].down = &right[i];
        right[i].row = -1;
    }
    h->rHead = down;
    for (int i = 0; i < row; i++) {
        down[i].right = &down[i];
        down[i].col = -1;
    }
    return h;
}
//插入结点
void insertList(list* head, int row, int col, elemType data) {
    //检验输入合法性
    if (row<1 || col<1 || row>head->row || col>head->col) {
        printf("error00001, at colomn=%d, row=%d", col, row);
        exit(0);
    }
    mNode* node = createNode(row, col, data);
    //处理数据便于后续运算
    row--;
    col--;
    //从列头节点去找插入位置的行
    mNode* prRow = &head->rHead[row], * pRow = prRow->right;
    while (col >= prRow->col && pRow != &head->rHead[row]) {
        prRow = pRow;
        pRow = pRow->right;
    }
    //从行头节点去找插入位置的列
    mNode* prCol = &head->cHead[col], * pCol = prCol->down;
    while (row >= prCol->row && pCol!= &head->cHead[col]) {
        prCol = pCol;
        pCol = pCol->down;
    }
    //处理结点间的链接
    prCol->down = node;
    prRow->right = node;
    node->down = pCol;
    node->right = pRow;
    head->nonZero++;
}
//转置矩阵
void transList(list* head) {
    mNode* newRight = head->rHead;
    mNode* newDown = head->cHead;
    //先将所有结点的row、col、down、right数据对调
    for (int i = 0; i < head->row; i++) {
        mNode* pr = head->rHead + i;
        mNode* p = pr->right;
        while (p != pr) {
            int t = p->row;
            p->row = p->col;
            p->col = t;
            mNode* down = p->down;
            p->down = p->right;
            p->right = down;
            p = p->down;
        }
        pr = &head->rHead[i];
    }
    //然后修改行列头节点的指向
    for (int i = 0; i < head->col; i++) {
        mNode* p = head->cHead + i;
        mNode* down = p->down;
        p->down = p->right;
        p->right = down;
    }
    for (int i = 0; i < head->row; i++) {
        mNode* p = head->rHead + i;
        mNode* down = p->down;
        p->down = p->right;
        p->right = down;
    }
    //最后修改总头节点
    mNode *newRHead = head->cHead;
    head->cHead = head->rHead;
    head->rHead = newRHead;
}
//主函数
int main() {
    const char sourceFileName[] = "MatrixSource.txt";
    const char outputFileName[] = "TransposedMatrix.txt";
    FILE* mSource, * mOutput = fopen(outputFileName, "w");
    int row, col, nonZero;
    //判断文件是否打开失败
    if ((mSource = fopen(sourceFileName, "a+")) == NULL) {
        puts("Failed to open the source file!");
        exit(0);
    }
    //获取矩阵规模以及非零元个数
    fscanf(mSource, "%d %d %d", &row, &col, &nonZero);
    //避免非零元素个数大于矩阵规模
    nonZero = nonZero > row * col ? row * col : nonZero;
    //建立十字链表并写入数据
    cList *list = createList(row, col);
    for (int i = 0; i < nonZero && !feof(mSource); i++) {
        int row, col, data;
        fscanf(mSource, "%d %d %d\n", &row, &col, &data);
        insertList(list, row, col, data);
    }
    fclose(mSource);
    //转置矩阵
    transList(list);
    //将转置后的矩阵写入新文件
    for (int i = 0; i < list->row; i++) {
        mNode* pr = list->rHead + i;
        mNode* p = pr->right;
        while (p != pr) {
            fprintf(mOutput, "%d %d %d\n", p->row, p->col, p->data);
            p = p->right;
        }
        pr = &list->rHead[i];
    }
    printf("转置成功，操作结束！");
}
