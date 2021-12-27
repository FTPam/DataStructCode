#pragma warning(disable:4996)
#include <iostream>
using namespace std;

#define NUM_OF_KEYS 8
#define RADIX_RANGE 16

typedef unsigned keyType;
typedef struct list {
	keyType data;
	keyType keys[NUM_OF_KEYS];
	list* next;
}sList, *sL;

void radixSort(sL head) {
	for (int i = NUM_OF_KEYS - 1; i >= 0; i--) {	// 对每一个关键字进行遍历
		sL listf[RADIX_RANGE] = { NULL }, liste[RADIX_RANGE] = { NULL };
		// 分配
		sL p = head->next;
		while (p != NULL) {	// 遍历链表
			int n = p->keys[i];	// 获取关键字
			sL fp = listf[n];	// 关键字工作指针
			if (fp == NULL) {
				listf[n] = p;
				liste[n] = p;
			}
			else {
				while (fp->next != NULL) {
					fp = fp->next;
				}
				fp->next = p;
				liste[n] = p;
			}
			sL pre = p;
			p = p->next;
			pre->next = NULL;
		}
		// 收集
		p = head;
		for (int j = 0; j < RADIX_RANGE; j++) {
			sL fp = listf[j];
			if (listf[j] != NULL) {
				p->next = listf[j];
				p = liste[j];
			}
		}
	}
	
}

void displayList(sL head) {
	head = head->next;
	cout << endl;
	while (head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void main() {
	keyType input;
	cout << "请输入一堆数组，以空格分割，以数字0结束" << endl;
	cin >> input;
	sL head = (sList*)malloc(sizeof(sList));	// 创建头节点
	if (head == NULL) {
		exit(0);
	}
	head->next = NULL;
	sL p = head;
	while (input) {
		sL node = (sList*)malloc(sizeof(sList));
		if (head == NULL) {
			exit(0);
		}
		for (int i = 1; i <= NUM_OF_KEYS; i++) {
			keyType temp;
			temp = input >> (32 - 4 * i);
			//与 1 进行与运算
			node->keys[i- 1] = temp & 15;
		}
		node->data = input;
		node->next = NULL;
		p->next = node;
		p = p->next;
		cin >> input;
	}
	cout << "数据读入完毕，开始排序..." << endl << endl;
	radixSort(head);
	cout << "排序结果如下:" << endl;
	displayList(head);
}
