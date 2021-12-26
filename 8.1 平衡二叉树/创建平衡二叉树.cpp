#pragma warning(disable:4996)
#include <iostream>
using namespace std;

enum {
	LL = 1, LR = 2, RR = 3, RL = 4
};
typedef int elemType;	// 二叉树储存整型数据
typedef struct bitNode {	// 二叉平衡树结构体
	elemType data;
	int bf;
	bitNode* LChild, * RChild;
}bsNode, * bsTree;
// 访问操作：输出平衡因子
void visitPrintBF(bsTree t) {
	cout << t->bf;
}
// 访问操作：输出结点数据
void visitPrintData(bsTree t) {
	cout << t->data;
}
// 返回一个初始化后的二叉树结点
bsTree getBSNode(elemType data) {
	bsTree node = (bsTree)malloc(sizeof(bitNode));
	if (node == NULL) {
		exit(1);
	}
	node->data = data;
	node->bf = 0;
	node->LChild = NULL;
	node->RChild = NULL;
}
// 先序遍历二叉树
void preOrderTra(bsTree t, void(*visit)(bsTree)) {
	if (t == NULL) {
		return;
	}
	visit(t);
	cout << " ";
	preOrderTra(t->LChild, visit);
	preOrderTra(t->RChild, visit);
}
// 中序遍历二叉树
void inOrderTra(bsTree t, void(*visit)(bsTree)) {
	if (t == NULL) {
		return;
	}
	inOrderTra(t->LChild, visit);
	visit(t);
	cout << " ";
	inOrderTra(t->RChild, visit);
}
// 对二叉排序树进行翻转
bsTree turnTree(bsTree bs, int type) {
    // 调整二叉树的代码逻辑参照严蔚敏的《数据结构》
	switch (type) {
	case LL: {
		bsTree back = bs->LChild;
		bs->LChild = back->RChild;
		back->RChild = bs;
		// 调整平衡因子
		bs->bf = 0;
		back->bf = 0;
		return back;
	}
	case LR: {
		bsTree back = bs->LChild->RChild;
		bs->LChild->RChild = back->LChild;
		back->LChild = bs->LChild;
		bs->LChild = back->RChild;
		back->RChild = bs;
		// 调整平衡因子
		back->LChild->bf = (1 - back->bf) / 2;	// 此式通过数学计算得到
		back->RChild->bf = (-1 - back->bf) / 2;	// 此式通过数学计算得到
		back -> bf = 0;
		return back;
	}
	case RR: {
		bsTree back = bs->RChild;
		bs->RChild = back->LChild;
		back->LChild = bs;
		// 调整平衡因子
		bs->bf = 0;
		back->bf = 0;
		return back;
	}
	case RL: {
		bsTree back = bs->RChild->LChild;
		bs->RChild->LChild = back->RChild;
		back->RChild = bs->RChild;
		bs->RChild = back->LChild;
		back->LChild = bs;
		// 调整平衡因子
		back->LChild->bf = (1 - back->bf) / 2;	// 此式通过数学计算得到
		back->RChild->bf = (-1 - back->bf) / 2;	// 此式通过数学计算得到
		back->bf = 0;
		return back;
	}
	}
}
// 向二叉排序树插入元素
// 若插入的元素在翻转前会增加二叉树深度，则返回true，否则返回false
bool insertTree(bsTree t, elemType data, bsTree* parent) {
	bsTree node = getBSNode(data);
	bool isDeeper = false;
	// 进行插入操作
	if (data < t->data) {
		if (t->LChild == NULL) {
			t->LChild = node;
			t->bf++;	// 在当前结点添加左子树，必定bf++
			return t->RChild == NULL ? true : false;	// 判断深度是否增加
		}
		else {
			if (insertTree(t->LChild, data, &(t->LChild))) {
				t->bf++;	// 左子树深度增加，bf++
				isDeeper = true;
			}
		}
	}
	else if (data > t->data) {
		if (t->RChild == NULL) {
			t->RChild = node;
			t->bf--;	// 在当前结点添加右子树，必定bf--
			return t->LChild == NULL ? true : false;	// 判断深度是否增加
		}
		else {
			if (insertTree(t->RChild, data, &(t->RChild))) {
				t->bf--;	// 右子树深度增加，bf--;
				isDeeper = true;
			}
		}
	}
	else {
		cout << "按照实验要求，不允许输入任意两个相同的数字，程序即将退出……" << endl;
		exit(1);
	}
	// 进行平衡判定
	if (t->bf == 2) {
		if (t->LChild->bf == 1) {
			*parent = turnTree(t, LL);
		}
		else if (t->LChild->bf == -1) {
			*parent = turnTree(t, LR);
		}
	}
	else if (t->bf == -2) {
		if (t->RChild->bf == -1) {
			*parent = turnTree(t, RR);
		}
		else if (t->RChild->bf == 1) {
			*parent = turnTree(t, RL);
		}
	}
	else {
		// 依然保持平衡，但深度增加
		return isDeeper ? true : false;
	}
	// 若经过了平衡调整，则深度不变
	return false;
}
// 主函数
int main() {
	int input;
	cout << "请输入若干两两互不相同的非零整数，以0结束：\n";
	// 创建并初始化二叉树
	bsTree tree;
	cin >> input;
	if (input == 0) {
		return 0;
	}
	else {
		tree = getBSNode(input);
		cin >> input;
	}
	// 开始循环读入数据
	while (input != 0) {
		insertTree(tree, input, &tree);
		cin >> input;
	}
	cout << "先序序列：" << endl;
	preOrderTra(tree, visitPrintData);
	cout << endl;

	cout << "中序序列：" << endl;
	inOrderTra(tree, visitPrintData);
	cout << endl;

	cout << "中序序列输出结点平衡因子：" << endl;
	inOrderTra(tree, visitPrintBF);
	cout << endl;
}
