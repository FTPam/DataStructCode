#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
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
	node->data = '*';
	node->LChild = NULL;
	node->RChild = NULL;
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
		node = createNode();
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
//求二叉树中以元素值为x的结点为根的子树的深度
//bt为要查找的二叉树，depth应传入1
int getDepth(bitTree bt, int depth) {
	if (!bt) {
		return depth - 1;
	}	//如果传入的二叉树为空，则返回depth - 1，表示深度并未增加
	//这部分代码是递归求深度
	int LDepth, RDepth;
	LDepth = getDepth(bt->LChild, depth + 1);
	RDepth = getDepth(bt->RChild, depth + 1);
	return LDepth >= RDepth ? LDepth : RDepth;
}
//输出
//data为该层的元素数组，layer为层号
void printTree(elemType data[], int layer, int depth) {
	int i = 0;	//当前位置
	//cLayer即current layer，当前层
	for (int cLayer = 1; cLayer < depth; cLayer++) {
		//layerMax为当前层的最大值
		int layerMax = (int)(pow(2.0, layer - 1));
		//输出第一个字符前面的空格
		if (layer != depth) {
			for (int j = 0; j < pow(2.0, depth - layer + 1) - 2; j++) {
				printf(" ");
			}
		}
		//输出元素间的空格
		while (i != layerMax) {
			printf("%c ", data[i]);
			for (int j = 0; j < (int)(pow(2.0, depth - layer + 2) - 2); j++) {
				printf(" ");
			}
			i++;
		}
		//输出线条
		printf("\n");
	}
}

//层序遍历获取每一层结点的信息
void getLayerInfo(bitTree bt, int depth) {
	//检验二叉树是否为空
	if (bt == NULL)
		return 0;
	//建立队列用于辅助输出
	queue bitQueue = createQueue();
	//layer为当前所在行
	int layer = 1;
	elemType data[MAX_SIZE];	//当前层的数据数组
	int i = 0;	//辅助变量，将数据存入data数组
	insertElem(&bitQueue, bt);	//根节点入队

	//将二叉树以完全二叉树存入队列
	while (bitQueue.tag != -1 && layer <= depth) {
		//结点出队列
		bitNode* node = deleteElem(&bitQueue);
		bitNode* emptyNode = createNode();

		data[i] = node->data;

		//如果当前结点就是一个“空”结点，则直接再入队两个空节点
		if (!node->data) {
			insertElem(&bitQueue, emptyNode);
			insertElem(&bitQueue, emptyNode);
		}
		else {

			//将左右孩子入队，若无左右孩子，则在当前层数小于二叉树层数时入队空结点
			if (node->LChild) {
				insertElem(&bitQueue, node->LChild);
			}
			else if (layer <= depth) {
				insertElem(&bitQueue, emptyNode);
			}

			if (node->RChild) {
				insertElem(&bitQueue, node->RChild);
			}
			else if (layer <= depth) {
				insertElem(&bitQueue, emptyNode);
			}
		}
		//游标向后移动
		i++;
		//判断当前行是否已经结束
		if (i == (int)(pow(2.0, layer - 1))) {
			printTree(data, layer, depth);
			i = 0;
			layer++;
		}
	}
}
//主函数
int main() {
	//将二叉树补为完全二叉树后的数据信息存入数组中
	elemType layer[MAX_SIZE];

	//构造二叉树
	printf("请输入要构造的二叉树\n");
	printf("程序依次读入单个字符，遇到*则置空\n");
	bitTree* tree = preOrderCreateTree();

	int depth = getDepth(tree, 1);
	printf("%d\n", depth);
	getLayerInfo(tree, depth);
}
