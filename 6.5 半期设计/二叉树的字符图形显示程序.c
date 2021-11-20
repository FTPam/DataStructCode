//代码较长，主要原因是重新实现了循环队列，以及注释很多，核心代码大概在130行左右
#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
#define MAX_SIZE 64

//二叉树储存char型数据
typedef char elemType;
//二叉链表结构体
typedef struct bitNode {
	elemType data;	//结点数据值
	int order;	//存储该结点在完全二叉树中的编号（只在逻辑上操作）
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
	if (a->tag == 1) {
		printf("二叉树深度超出程序所能计算的上限");
		exit(0);
	}
	*(a->base + a->rear) = node;
	a->rear = (a->rear + 1) % MAX_SIZE;	//重新定位rear指针
	a->tag = 0;					//此时已经回到一般情况或队满
	if (a->front == a->rear)	//判断是否队满
		a->tag = 1;
	return 1;		//插入成功，返回1
}
//获取队列最前端的元素地址
bitNode* getTop(queue* a) {
	if (a->tag == -1)
		return NULL;	//队空返回空指针
	return *(a->base + a->front);	//否则返回队列顶部元素
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
//data为该层的元素数组，layer为层号, length为实际有效结点数量
void printLayer(bitTree data[], int layer, int depth, int length) {
	//在data末尾创建一个尾结点，用于避免数组越界
	data[length] = createNode();
	data[length]->order = -1;
	int cp = 0; //data数组游标
	//layerStart为当前层的起始编号，layerMax为当前层中最大编号
	int layerStart = (int)(pow(2.0, layer - 1)), layerMax = (int)(pow(2.0, layer) - 1);
	//firstBlank为第一个字符前面的空格数，gap为中间每个字符间的空格数
	int firstBlank = pow(2.0, depth - layer + 1) - 2, gap = (int)(pow(2.0, depth - layer + 2)) - 1;
	// ----------以下部分输出线条-----------
	// 如果是第一层（根节点），则不输出头顶上的线条
	if (layer != 1) {
		//此循环用于输出第一行线条，两个元素为一组
		printx(' ', firstBlank);
		for (int i = layerStart, cp = 0; i < layerMax; i = i + 2) {
			//若当前位置有元素，则输出横线，否则输出空格占位
			if (i == data[cp]->order) {
				printx('_', gap / 2 + 1);
			}
			else {
				printx(' ', gap / 2 + 1);
			}
			//若i和i+1不同时为空，则输出中间的竖线，否则输出空格占位
			if (data[cp]->order == i || data[cp]->order == i + 1) {
				printx('|', 1);
			}
			else {
				printf(" ");
			}
			if (i == data[cp]->order) {
				cp++;
			}
			//若当前位置有元素，则输出横线，否则输出空格占位
			if (data[cp]->order == i + 1) {
				printx('_', gap / 2 + 1);
				cp++;
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
		for (int i = layerStart, cp = 0; i < layerMax; i = i + 2) {
			//若当前位置有元素，则输出它头顶的竖线，否则输出空格占位
			if (i == data[cp]->order) {
				printf("|");
				cp++;
			}
			else {
				printf(" ");
			}
			printx(' ', gap);
			//若当前位置有元素，则输出它头顶的竖线，否则输出空格占位
			if (i + 1 == data[cp]->order) {
				printf("|");
				cp++;
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
	for (int i = layerStart, cp = 0; i <= layerMax; i++) {
		if (i == data[cp]->order) {
			printf("%c", data[cp]->data);
			cp++;
		}
		else {
			printf(" ");
		}
		if (i != layerMax) {
			printx(' ', gap);
		}
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
	bitTree data[MAX_SIZE];	//当前层的元素数组
	int length = 0; //当前行实际结点数量
	bt->order = 1;	//初始化根节点，根节点的序号为1
	insertElem(&bitQueue, bt);	//根节点入队

	//将二叉树以完全二叉树存入队列
	while (1) {
		//判断该队列顶部结点是否已经超出当前行，或者已经到末端
		if (!getTop(&bitQueue)) {
			printLayer(data, layer, depth, length);
			break;
		}
		if (getTop(&bitQueue)->order > (int)(pow(2.0, layer) - 1)) {
			printLayer(data, layer, depth, length);
			length = 0;
			layer++;
			continue;
		}
		//结点出队列
		bitNode* node = deleteElem(&bitQueue);
		data[length] = node;
		// 将左右孩子入队
		// 并初始化左右孩子的序号
		if (node->LChild) {
			insertElem(&bitQueue, node->LChild);
			node->LChild->order = 2 * node->order;
		}
		if (node->RChild) {
			insertElem(&bitQueue, node->RChild);
			node->RChild->order = 2 * node->order + 1;
		}
		//有效结点数+1
		length++;
		//判断当前行是否已经结束
	}
}
//主函数
int main() {
	//构造二叉树
	printf("请以先序序列输入要构造的二叉树\n");
	printf("用#表示NULL指针域\n");
	bitTree* tree = preOrderCreateTree();
	//获取二叉树深度
	int depth = getDepth(tree, 1);
	//打印二叉树的字符图形
	printf("该二叉树图形为:\n");
	printTree(tree, depth);
}
