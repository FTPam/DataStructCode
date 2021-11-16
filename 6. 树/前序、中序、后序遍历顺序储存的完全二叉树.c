#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100

//储存整数
typedef int elemType;
//二叉树的顺序储存
typedef struct sqBitTree {
	elemType data[MAX_TREE_SIZE];
	int length;
}sqBitTree;

//先序遍历顺序结构二叉树
//bt为要遍历的顺序二叉树，num为遍历起始点（根节点为1）
void preOrder(sqBitTree bt, int num) {
	if (bt.length < 0 || num < 1 || num > bt.length) {
		return;
	}
	printf("%d ", bt.data[num - 1]);
	if (2 * num <= bt.length) {
		preOrder(bt, 2 * num);
	}
	if (2 * num + 1 <= bt.length) {
		preOrder(bt, 2 * num + 1);
	}
}

//中序遍历顺序结构二叉树
//bt为要遍历的顺序二叉树，num为遍历起始点（根节点为1）
void inOrder(sqBitTree bt, int num) {
	if (bt.length < 0 || num < 1 || num > bt.length) {
		return;
	}
	if (2 * num <= bt.length) {
		inOrder(bt, 2 * num);
	}
	printf("%d ", bt.data[num - 1]);
	if (2 * num + 1 <= bt.length) {
		inOrder(bt, 2 * num + 1);
	}
}

//后遍历顺序结构二叉树
//bt为要遍历的顺序二叉树，num为遍历起始点（根节点为1）
void postOrder(sqBitTree bt, int num) {
	if (bt.length < 0 || num < 1 || num > bt.length) {
		return;
	}
	if (2 * num <= bt.length) {
		postOrder(bt, 2 * num);
	}
	if (2 * num + 1 <= bt.length) {
		postOrder(bt, 2 * num + 1);
	}
	printf("%d ", bt.data[num - 1]);
}

//主函数
int main() {
	sqBitTree bt;

	//此段代码建立顺序结构存储完全二叉树
	printf("请输入完全二叉树的元素个数: ");
	scanf("%d", &bt.length);
	printf("请依次输入要存入完全二叉树的元素:\n");
	for (int i = 0; i < bt.length; i++) {
		int ch;
		scanf("%d", &ch);
		bt.data[i] = ch;
	}
	printf("\n先序遍历结果：");
	preOrder(bt, 1);
	printf("\n中序遍历结果：");
	inOrder(bt, 1);
	printf("\n后序遍历结果：");
	postOrder(bt, 1);
}
