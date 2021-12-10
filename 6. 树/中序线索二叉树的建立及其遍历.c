#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

// 二叉树储存char型数据
typedef char elemType;
// 二叉线索链表储存结构
typedef struct bitNode {
	elemType data;
	struct bitNode* LChild, * RChild;
	int LTag, RTag;	//0为孩子，L1为前驱，R1为后继
}bitNode, * bitTree;

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

// 中序线索化二叉树，返回根节点
// bt是二叉链表
// pre和bt都传入二叉链表
bitTree inThreading(bitTree* pre, bitTree bt) {
	if (bt == NULL) {
		return *pre;
	}
	bitTree back = NULL;
	// 先走到最左
	back = inThreading(pre, bt->LChild);
	bt->LTag = 0;
	bt->RTag = 0;
	// 对空的左孩子域进行处理
	if (bt->LChild == NULL) {
		bt->LTag = 1;
		bt->LChild = *pre;
	}
	// 对空的右孩子域进行处理
	bitTree rpre = *pre;
	if (rpre != NULL && rpre->RTag == 1) {
		rpre->RChild = bt;
	}
	if (bt->RChild == NULL) {
		bt->RTag = 1;
	}
	*pre = bt;
	back = inThreading(pre, bt->RChild);
	return back;
}

void inTraverse(bitTree bt) {
	// 若为空，则直接返回
	if (bt == NULL) {
		return;
	}
	// 先走到根节点并记录下来
	bitTree head = bt;
	bt = bt->LChild;
	// 找到中序序列第一节点
	while (bt->LTag == 0) {
		bt = bt->LChild;
	}
	// 开始遍历输出
	while (bt != head) {
		printf("%c ", bt->data);
		// 如果LTag是孩子，则走到最左
		if (bt->RTag == 1) {
			bt = bt->RChild;
		}
		else {
			// 走到中序遍历的下一个结点
			bt = bt->RChild;
			while (bt->LTag == 0) {
				bt = bt->LChild;
			}
		}	
	}
}

//主函数
int main() {
	printf("请输入要构造的二叉树\n");
	printf("程序依次读入单个字符，遇到*则置空\n");
	bitTree tree = preOrderCreateTree();

	// 创建头结点
	bitNode head;
	// 创建头指针
	bitTree pre = &head;
	pre->LChild = tree;
	pre->LTag = 0;
	bitTree last = inThreading(&pre, tree);
	// 处理头节点与最后一个中序结点的关系
	last->RTag = 1;
	last->RChild = &head;
	head.RTag = 1;
	head.RChild = last;

	inTraverse(&head);
}
