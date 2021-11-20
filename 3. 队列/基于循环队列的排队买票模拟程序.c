#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef char ElemType;
typedef struct queue {
	ElemType* base;	//基地址
	int front;		//头指针
	int rear;		//尾指针，指向即将要写入的单元
	int tag;		//1为满，-1为空，0为一般情况
}queue;

//创建并返回一个队列
queue createQueue() {
	queue a;
	a.base = (ElemType*)malloc(MAX_SIZE * sizeof(ElemType));
	if (!a.base) {
		printf("Failed to malloc memory for the software!");
		exit(0);
	}
	a.front = 0;
	a.rear = 0;
	a.tag = -1;
	return a;
}

//向队列添加元素，成功则返回1，队满失败则返回0
int insertElem(queue* a, char name) {
	if (a->tag == 1)		//如果队满，则返回0
		return 0;
	*(a->base + a->rear) = name;
	a->rear = (a->rear + 1) % MAX_SIZE;	//重新定位rear指针
	a->tag = 0;					//此时已经回到一般情况或队满
	if (a->front == a->rear)	//判断是否队满
		a->tag = 1;
	return 1;		//插入成功，返回1
}

//从队列删除元素，成功则返回用户姓名，队空失败返回0
char deleteElem(queue* a) {
	char name;	//用于储存用户姓名
	if (a->tag == -1)
		return 0;	//队空，返回0
	name = *(a->base+a->front);
	a->front = (a->front + 1) % MAX_SIZE;	//重新定位front指针
	a->tag = 0;					//此时已经回到一般情况或队空
	if (a->front == a->rear)	//判断是否队空
		a->tag = -1;
	return name;				//返回用户姓名
}

//展示整个队列中的所有元素
void displayElem(queue a) {
	int length;		//储存队列长度
	if (a.tag == -1) {
		printf("当前队列为空！\n");
		return 0;
	}
	length = (a.rear - a.front - 1 + MAX_SIZE) % MAX_SIZE + 1;
	printf("当前队列中有%d人，从前到后依次是：\n", length);
	for (int i = 0; i < length; i++) {
		printf("%d号是%c\n", i + 1, *(a.base + (a.front + i) % MAX_SIZE));
	}
}

//获取从键盘输入的字符并过滤掉换行符
char getOpe() {
	char ope;
	do {
		ope = getchar();
	} while (ope == '\n');
	return ope;
}

//主函数
int main() {
	queue a = createQueue();
	char ope;
	printf("欢迎访问售票系统！\n");
	printf("请通过输入菜单中的数字代码来进行操作！\n");
	printf("======================================\n");
	printf("1. 排队\n");
	printf("2. 售票\n");
	printf("3. 查看队列\n");
	printf("4. 结束\n");
	printf("======================================\n");
	printf("请输入操作代码：");

	while (1) {
		ope = getOpe();
		switch (ope) {
		case 49: {
			printf("请输入姓名：");
			char name;
			name = getOpe();
			if (insertElem(&a, name))
				printf("排队成功！\n");
			else
				printf("排队失败，队列已满，请您再稍等一会！\n");
			
			break;
		}
		case 50: {
			char name = deleteElem(&a);
			if (name)
				printf("售票成功，买到票的是：%c\n", name);
			else
				printf("售票失败，因为没有人在排队！\n");
			break;
		}
		case 51: {
			displayElem(a);
			break;
		}
		case 52: {
			goto end;
			break;
		}
		default: {
			printf("\n输入有误，请重新输入1-4的数字代码：");
		}
		}
		printf("\n请输入操作代码：");
	}

end:
	printf("感谢使用本系统，再见！\n");
}
