#pragma warning(disable:4996)
#include <stdio.h>

//二叉树储存int型数据
typedef int elemType;
//二叉树的三叉链表结构
typedef struct bitNode {
	elemType data;						//结点数据值
	struct bitNode* LChild, * RChild;	//左右孩子和父母
}bitNode, * bitTree;
//循环队列结构体
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
bitNode* preOrderCreateTree() {
	bitNode* node;
	elemType ch;
	scanf("%d", &ch);
	//如果遇到数字0则置NULL
	if (ch == 0) {
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
//获取二叉树结点数据最大值
//max必须传入bt->data
//即调用时，必须是getMax(bt, bt->data)
int getMax(bitTree bt, int max) {
	if (bt == NULL) {
		return max;
	}
	if (bt->data > max) {
		max = bt->data;
	}
	max = getMax(bt->LChild, max);
	max = getMax(bt->RChild, max);
	return max;
}
//获取二叉树结点数据之和
//sum应传入0
int getSum(bitTree bt, int sum) {
	if (bt == NULL) {
		return sum;
	}
	sum += bt->data;
	sum = getSum(bt->LChild, sum);
	sum = getSum(bt->RChild, sum);
	return sum;
}
//获取二叉树负值结点总数
//sum应传入0
int getNegNum(bitTree bt, int sum) {
	if (bt == NULL) {
		return sum;
	}
	if (bt->data < 0) {
		sum += 1;
	}
	sum = getNegNum(bt->LChild, sum);
	sum = getNegNum(bt->RChild, sum);
	return sum;
}

//主函数
int main() {
	bitTree bt = preOrderCreateTree();
	printf("二叉树中最大数据值为: %d\n", getMax(bt, bt->data));
	printf("二叉树节点数据之和为: %d\n", getSum(bt, 0));
	printf("二叉树负值结点总数为: %d\n", getNegNum(bt, 0));
}
