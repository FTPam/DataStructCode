#include <stdio.h>

typedef int ElemType;

typedef struct List {	//链表结构体
	ElemType data;		//数据域
	struct List* next;	//下一个结点的地址
}list;

list* CreateList() {	//创建一个头结点
	list* a = (list*)malloc(sizeof(list));
	if (!a) {
		printf("Failed to malloc memory!\n");
		exit(0);
	}	//成功创建一个结点
	a->data = NULL;
	a->next = NULL;	//将结点链接到头指针上
	return a;
}

void AppendNode(list* head, ElemType data) {
	list* p = (list*)malloc(sizeof(list));
	if (p == NULL) {
		printf("Failed to malloc memory!\n");
		exit(0);
	}
	p->data = NULL;
	p->next = NULL;		//成功创建一个标准尾结点
	while (head->next != NULL) {	//将head指针移动到链表尾部
		head = head->next;
	}
	p->data = data;		//将数据存入结点数据域
	head->next = p;		//将结点接到链表尾部
}

void DisplayList(list* head) {
	head = head->next;	//先将指针移动到头结点的下一个结点
	while (head != NULL) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

void MergeList(list* La, list* Lb) {
	list* p = La;
	list* headB = Lb;
	La = La->next;	//将指针移动到数据域
	Lb = Lb->next;
	while (La && Lb) {
		if (La->data <= Lb->data) {
			p->next = La;
			La = La->next;
		}
		else {
			p->next = Lb;
			Lb = Lb->next;
		}
		p = p->next;
	}
	p->next = La ? La : Lb;	//合并剩下的部分
	free(headB);	//释放链表B头指针空间
}

void TypeDataIntoList(list* La, char listName) {	//从键盘获取数据并存入链表，完成后依次输出链表中所有结点的数据
	int length = 6;
	scanf_s("%d", &length);
	for (int i = 0; i < length; i++) {
		ElemType data;
		scanf_s("%d", &data);
		AppendNode(La, data);
	}
	DisplayList(La);
}

void deleteElemByData(list* La, ElemType data) {
	list* work = La;
	La = La->next;
	while (work->next != NULL) {
		if (La->data == data) {
			work->next = La->next;
			free(La);
			La = work->next;
		}
		else {
			La = La->next;
			work = work->next;
		}
	}
}

void main() {
	list* headA = CreateList();	//创建头指针并指向头节点

	printf("输入数组6个元素的值。\n");
	TypeDataIntoList(headA, 'A');	//从键盘获取数据并存入链表

	printf("此链表各个结点的数据域为：\n");
	DisplayList(headA);
	printf("输入要删除的数据x: \n");
	int data;
	scanf_s("%d", &data);
	deleteElemByData(headA, data);
	printf("删除后链表各个结点的数据域为： \n");
	DisplayList(headA);
}
