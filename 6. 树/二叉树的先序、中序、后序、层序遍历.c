#pragma warning(disable:4996)
#include <stdio.h>
#define MAX_SIZE 100

//二叉树储存char型数据
typedef char elemType;
//二叉树结构体
typedef struct bitNode {
	elemType data;				//结点数据值
	struct bitNode* LChild, * RChild;	//左右孩子
}bitNode, * bitTree;
//循环队列结构体
typedef struct queue {
	bitNode** base;	//基地址
	int front;		//头指针
	int rear;		//尾指针，指向即将要写入的单元
	int tag;		//1为满，-1为空，0为一般情况
}queue;
//创建并返回一个队列
queue createQueue() {
	queue a;
	a.base = (bitNode*)malloc(MAX_SIZE * sizeof(bitNode));
	if (!a.base) {
		printf("Failed to malloc memory for the software!");
		exit(0);
	}
	//初始化队列
	a.front = 0;
	a.rear = 0;
	a.tag = -1;
	return a;
}
//向队列添加元素，成功则返回1，队满失败则返回0
int insertElem(queue* a, bitNode* node) {
	if (a->tag == 1)		//如果队满，则返回0
		return 0;
	*(a->base + a->rear) = node;
	a->rear = (a->rear + 1) % MAX_SIZE;	//重新定位rear指针
	a->tag = 0;					//此时已经回到一般情况或队满
	if (a->front == a->rear)	//判断是否队满
		a->tag = 1;
	return 1;		//插入成功，返回1
}
//从队列删除元素，返回该元素的地址
bitNode* deleteElem(queue* a) {
	bitNode* node;	//用于储存出队列的元素指针
	if (a->tag == -1)
		return 0;	//队空，返回0
	node = *(a->base + a->front);
	a->front = (a->front + 1) % MAX_SIZE;	//重新定位front指针
	a->tag = 0;					//此时已经回到一般情况或队空
	if (a->front == a->rear)	//判断是否队空
		a->tag = -1;
	return node;				//返回出队列的元素指针
}
//创建一个二叉树的结点并返回其地址
bitNode* createNode() {
	bitNode* node = (bitNode*)malloc(sizeof(bitNode));
	if (node == NULL) {
		printf("STACK OVERFLOW");
		exit(0);
	}
	return node;
}
//先序遍历建立二叉树并返回其根节点地址
//参数表示输入的初始字符，若为空，函数会自动从缓冲区读入一个
bitNode* preOrderCreateTree() {
	bitNode* node;
	char ch;
	ch = getchar();
	//如果遇到字符*或\n，则表示无该节点
	if (ch == '*' || ch == '\n') {
		node = NULL;
	}
	else {
		//递归为该节点接上左右孩子
		node = (bitNode*)malloc(sizeof(bitNode));
		node->data = ch;
		node->LChild = preOrderCreateTree();
		node->RChild = preOrderCreateTree();
	}
	return node;
}
//先序遍历输出
void preOrder(bitTree bt) {
	if (bt == NULL) {
		return 0;
	}
	printf("%c", bt->data);
	preOrder(bt->LChild);
	preOrder(bt->RChild);
}
//中序遍历输出
void inOrder(bitTree bt) {
	if (bt == NULL) {
		return 0;
	}
	inOrder(bt->LChild);
	printf("%c", bt->data);
	inOrder(bt->RChild);
}
//后序遍历
void postOrder(bitTree bt) {
	if (bt == NULL) {
		return 0;
	}
	postOrder(bt->LChild);
	postOrder(bt->RChild);
	printf("%c", bt->data);
}
//层序遍历
void layerOrder(bitTree bt) {
	//检验二叉树是否为空
	if (bt == NULL)
		return 0;
	//建立队列用于辅助输出
	queue bitQueue = createQueue();
	insertElem(&bitQueue, bt);	//根节点入队
	while (bitQueue.tag != -1) {
		//先出队列，输出出队列的元素数据值
		//若该元素有左右孩子，则从左至右依次入队
		bitNode* node = deleteElem(&bitQueue);
		printf("%c", node->data);
		if (node->LChild)
			insertElem(&bitQueue, node->LChild);
		if (node->RChild)
			insertElem(&bitQueue, node->RChild);
	}
}
//主函数
int main() {
	printf("请输入要构造的二叉树\n");
	printf("程序依次读入单个字符，遇到*则置空\n");
	bitTree* tree = preOrderCreateTree();
	printf("\n先序遍历结果：\n");
	preOrder(tree);
	printf("\n中序遍历结果：\n");
	inOrder(tree);
	printf("\n后序遍历结果：\n");
	postOrder(tree);
	printf("\n层序遍历结果：\n");
	layerOrder(tree);
}
