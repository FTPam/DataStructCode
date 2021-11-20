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
//从队列删除元素，并返回该元素的地址
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
	node->data = NULL;
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
	//如果遇到字符#，则表示无该节点
	if (ch == '#') {
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
//连续输出num次字符
void printx(char data, int num) {
	for (int i = 0; i < num; i++) {
		printf("%c", data);
	}
}
//data为该层的元素数组，layer为层号
void printLayer(elemType data[], int layer, int depth) {
	//layerMax为当前层的元素个数
	int layerMax = (int)(pow(2.0, layer - 1));
	//firstBlank为第一个字符前面的空格数，gap为中间每个字符间的空格数
	int firstBlank = pow(2.0, depth - layer + 1) - 2, gap = (int)(pow(2.0, depth - layer + 2)) - 1;
	// ----------以下部分输出线条-----------
	// 如果是第一层（根节点），则不输出头顶上的线条
	if (layer != 1) {
		//此循环用于输出第一行线条，两个元素为一组
		printx(' ', firstBlank);
		for (int i = 0; i < layerMax; i = i + 2) {
			//若data[i]不是空节点，则输出它头上的线
			if (data[i]) {
				printx('_', gap / 2 + 1);
			}
			else {
				printx(' ', gap / 2 + 1);
			}
			//若data[i]和data[i+1]不同时为空，则输出中间的竖线，否则输出空格占位
			if (data[i] || data[i + 1]) {
				printx('|', 1);
			}
			else {
				printf(" ");
			}
			//若data[i+1]不是空节点，则输出它头上的横线
			if (data[i + 1]) {
				printx('_', gap / 2 + 1);
			}
			else {
				printx(' ', gap / 2 + 1);
			}
			//若后面还有元素，则输出空格
			if (i + 2 < layerMax) {
				printx(' ', gap);
			}
		}
		printf("\n");
		//此循环用于输出第二行线条
		printx(' ', firstBlank);
		for (int i = 0; i < layerMax; i = i + 2) {
			//若data[i]不是空节点，则输出它头上的竖线
			if (data[i]) {
				printf("|");
			}
			else {
				printf(" ");
			}
			printx(' ', gap);
			//若data[i+1]不是空节点，则输出它头上的竖线
			if (data[i + 1]) {
				printf("|");
			}
			else {
				printf(" ");
			}
			if (i + 2 < layerMax) {
				printx(' ', gap);
			}
		}
		printf("\n");
	}

	//---------以下部分输出字符------------
	//输出第一个字符前面的空格
	if (layer != depth) {
		printx(' ', firstBlank);
	}
	//输出该层所有元素
	for (int i = 0; i < layerMax; i++) {
		if (data[i]) {
			printf("%c", data[i]);
		}
		else {
			printf(" ");
		}
		printx(' ', gap);
	}
	printf("\n");
}

//层序遍历获取每一层的信息，并传给printLayer进行打印
void printTree(bitTree bt, int depth) {
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
		//其含义是假装这是一棵满二叉树，便于printLayer打印
		if (!node->data) {
			insertElem(&bitQueue, emptyNode);
			insertElem(&bitQueue, emptyNode);
		}
		else {
			// 将左右孩子入队
			// 若无左右孩子，则在当前层数小于二叉树层数时入队空结点
			// 如果当前已经到最后一层，那么久不要再补空节点了，否则就会无限进行下去
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
			printLayer(data, layer, depth);
			i = 0;
			layer++;
		}
	}
}
//主函数
int main() {
	//构造二叉树
	printf("请输入要构造的二叉树\n");
	printf("程序依次读入单个字符，遇到*则置空\n");
	bitTree* tree = preOrderCreateTree();
	//获取二叉树深度
	int depth = getDepth(tree, 1);
	//打印二叉树的字符图形
	printTree(tree, depth);
}
