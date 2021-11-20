#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define List_Init_Size 5

typedef int ElemType;
typedef struct twoStack {
	ElemType* base;	//数组的基地址
	ElemType* aHead;	//A的栈顶指针
	ElemType* bHead;	//B的栈顶指针
}twoStack;

void inistack(twoStack* tws) {
	tws->base = (ElemType*)malloc(List_Init_Size * sizeof(ElemType));
	if (tws->aHead == NULL) {
		printf("Failed to malloc memory.");
		exit(0);
	}
	tws->aHead = tws->base;
	tws->bHead = tws->base + List_Init_Size - 1;
}

void appendElem(ElemType* loc, ElemType data) {
	
}

//i为0时接A，i为1时接B
void push(twoStack* tws, int i, ElemType x) {
	if (tws->aHead > tws->bHead) {
		printf("STACK OVERFLOW");
	}
	else {
		if (i == 0) {
			*(tws->aHead) = x;
			tws->aHead++;
		}
		else if (i == 1) {
			*(tws->bHead) = x;
			tws->bHead--;
		}
		else
			printf("i输入错误");
	}
}

void pop(twoStack* tws, int i, ElemType* x) {
	if (i == 0) {
		if (tws->base == tws->aHead)
			printf("栈空");
		else {
			*x = *(tws->aHead - 1);
			tws->aHead--;
		}
	}
	else if (i == 1) {
		if (tws->base + List_Init_Size - 1 == tws->bHead)
			printf("栈空");
		else {
			*x = *(tws->bHead + 1);
			tws->bHead++;
		}
	}
	else
		printf("i输入错误");

}

void main() {
  //以下均为测试代码
	int x;
	twoStack stack;
	inistack(&stack);
	push(&stack, 0, 101);
	push(&stack, 0, 102);
	push(&stack, 1, 21);
	push(&stack, 1, 31);
	push(&stack, 1, 40);
	push(&stack, 0, 150);
	push(&stack, 0, 170);
	pop(&stack, 1, &x);
	pop(&stack, 1, &x);
	pop(&stack, 1, &x);
	pop(&stack, 1, &x);
	pop(&stack, 1, &x);
	pop(&stack, 0, &x);
	pop(&stack, 0, &x);
	pop(&stack, 0, &x);
	push(&stack, 1, 21);
	push(&stack, 0, 131);
	push(&stack, 0, 140);
	push(&stack, 0, 150);
	push(&stack, 0, 170);
}
