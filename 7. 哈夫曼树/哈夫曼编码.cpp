#pragma warning(disable:4996)
#include <iostream>
#include <list>
using namespace std;
#define MAX_SIZE 30

typedef char elemType;
//哈夫曼树结点结构
typedef struct {
	int parent,	LChild, RChild;	//父母左右孩子
	double w;	//结点权重
}HF_BTNode;
//哈夫曼树结构
typedef struct {
	int n;	//符号数量
	elemType s[MAX_SIZE];	//符号表
	double weight[MAX_SIZE];	//权重
	char code[MAX_SIZE][MAX_SIZE + 1];	//编码表
	HF_BTNode hf[2 * MAX_SIZE - 1];	//码树
}HFT;

int main() {
	int n;
	HFT tree;
	HF_BTNode test;
	printf("哈弗曼编码系统");
	printf("请输入字符数量: ");
	scanf("%d", n);
	printf("请依次输入字符: ");

	// 建立哈夫曼编码系统

	while (1) {
		int ope;
		printf("============菜单============");
		printf("1. 字符串转哈夫曼编码");
		printf("2. 退出系统");
		scanf("%d", &ope);
		if (ope == 1) {

		}
		else if (ope == 2) {

		}
		else {
			printf("输入错误，请重新输入！");
		}
	}
}
