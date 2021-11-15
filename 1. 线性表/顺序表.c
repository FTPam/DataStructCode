#include <stdio.h>
#define List_Init_Size 5
#define List_Increment 5

typedef int ElemType;

typedef struct list {	//顺序表结构体
	ElemType* head;	//基地址
	int length;		//当前数据个数
	int size;	//总容量
}list;

list CreateList() {		//创建一个顺序表并返回
	struct list list;
	list.head = (ElemType*)malloc(List_Init_Size * sizeof(ElemType));
	if (!list.head)
		exit(0);	//成功为顺序表的基地址分配内存
	list.length = 0;
	list.size = List_Init_Size;	//初始化顺序表
	return list;
}

list IncreaseList(list list) {	//增长顺序表
	ElemType* newBase = (ElemType*)realloc(list.head, (list.size + List_Increment) * sizeof(ElemType));
	if (!newBase)
		exit(0);	//成功重新分配内存
	list.head = newBase;
	list.size += List_Increment;
	return list;	//重新初始化新的顺序表
}

list InsertList(list list, int i, int data) {		//插入的表的基地址、插入的位置(以0开始)、插入的数值
	if (list.length >= list.size)
		list = IncreaseList(list);
	ElemType* q, * p; //定义2个指针变量，一个用于插入数据，一个用于移动数据
	q = list.head + i; //将q指针移动到要插入的地方
	for (p = list.head + list.size - 1; p > q; p--) {
		*p = *(p - 1);
	}
	*q = data;
	list.length++;
	return list;
}

void DisplayList(list list) {	//输出某个顺序表中的所有元素
	for (int i = 0; i < list.length; i++) {
		printf("%d ", *(list.head + i));
	}
	printf("\n");
}

list MergeList(list La, list Lb) {
	int i = 0, j = 0;	//游标置零
	list Lc = CreateList();
	//按顺序将La和Lb中的元素接入Lc
	while (i < La.length && j < Lb.length) {
		if (*(La.head + i) <= *(Lb.head + j)) {
			Lc = InsertList(Lc, i + j, *(La.head + i));
			i++;
		}
		else {
			Lc = InsertList(Lc, i + j, *(Lb.head + j));
			j++;
		}
	}
	//将剩下的接入Lc
	while (i < La.length) {
		Lc = InsertList(Lc, i + j, *(La.head + i));
		i++;
	}
	while (j < Lb.length) {
		Lc = InsertList(Lc, i + j, *(Lb.head + j));
		j++;
	}
	return Lc;
}

list TypeDataIntoList(list La, char listName) {	//输入数据到数组中，并输出其中每个元素到屏幕
	printf("How long is list %c: ", listName);
	int length;
	scanf_s("%d", &length);
	printf("Please type in %d numbers in ascending order: ", length);
	for (int i = 0; i < length; i++) {
		int data;
		scanf_s("%d", &data);
		La = InsertList(La, i, data);
	}
	printf("List %c is: ", listName);
	DisplayList(La);
	return La;
}

int main() {
	list headA = CreateList();
	list headB = CreateList();

	headA = TypeDataIntoList(headA, 'A');
	headB = TypeDataIntoList(headB, 'B');

	printf("The list after merged is:\n");
	list headC = MergeList(headA, headB);
	DisplayList(headC);
}
