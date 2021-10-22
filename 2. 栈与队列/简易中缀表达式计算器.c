#include <stdio.h>
#include <stdlib.h>

typedef int elemType;	//定义链栈所要储存的数据类型
//链表的struct结构，供链式栈使用
typedef struct linkedList {
	elemType data;		//数据域
	struct stack* next;	//next域
}stack;
//创建一个结点并返回
stack* createNode(elemType data, stack* next) {
	stack* node = (stack*)malloc(sizeof(stack));
	if (node == NULL) {	//若内存分配失败，则直接退出程序
		printf("Failed to malloc memory for stack");
		exit(0);
	}
	node->data = data;
	node->next = next;
	return node;
}
//压栈
void push(stack** head, elemType data) {
	*(head) = createNode(data, *(head));
}
/*出栈，并返回弹出的值，若下溢则直接退出
  务必传入stackA指针的地址*/
elemType pop(stack** head) {
	elemType data;
	if (*head != NULL) {
		stack* p = *head;
		data = p->data;
		(*head) = (*(head))->next;
		free(p);
		return data;
	}
	//下溢证明算式输入错误，直接退出
	printf("SYNTAX ERROR!");
	exit(0);
}
//获取栈顶元素的值
elemType getTop(stack* head) {
	if (head != NULL) {
		return head->data;
	}
	return -1;
}
//判断某个字符是否为运算符
int isOperator(char ope) {
	switch (ope)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		return 1;
	default:
		return 0;
	}
}
//获取栈内运算符优先级
int getIsp(char ope) {
	switch (ope) {
	case ')':
		return 4;
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	default:
		return 0;
	}
}
//获取栈外运算符优先级
int getIcp(char ope) {
	switch (ope) {
	case ')':
		return 1;
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	case '(':
		return 4;
	default:
		return 0;
	}
}
//进行计算，并返回结果
elemType calculate(elemType a, elemType b, char ch) {
	switch (ch) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0;
	}
}
//处理缓冲区中的字符
//ch是初始字符，startSign是开始标志，endSign是结束标志
elemType process(char ch, char startSign, char endSign) {
	//创建操作符和运算符栈
	stack* numStack = NULL, * opeStack = NULL;
	//如果没有传入初始ch值，则从缓存区读一个
	if (ch == ' ')
		ch = getchar();	
	//默认将+ -理解为操作符，1为操作符，0为正负号
	int sign = 1;	
	
	while (1) {
		if (ch == '\n')	//读到换行符则无条件结束程序，避免因为没有输入开始结束符导致的无限循环
			exit(0);
		if (ch == ')')	//一律将右括号处理为结束符，以便实现递归
			ch = endSign;
		//此分支处理开始符、结束符、运算符
		if ((isOperator(ch) && sign) || ch == startSign || ch == endSign) {
			int icp = getIcp(ch);
			//获取栈内运算符优先级，若为空则将isp设为-1
			int isp = getTop(opeStack) == -1 ? -1 : getIsp(getTop(opeStack));

			//如果icp>isp则直接入栈
			if (icp > isp) {
				push(&opeStack, ch);
			}
			else {
				//先判断一次是否结束运算，用于应对开始符和结束符中间没有运算符的情况(#5#)
				if (ch == endSign && getTop(opeStack) == startSign) {
					pop(&opeStack);	//清空运算符栈
					return pop(&numStack);	//返回运算结果
				}
				//一直运算，直到直到栈外运算符优先级大于站内运算符后，让运算符入栈
				do {
					push(&numStack, calculate(pop(&numStack), pop(&numStack), pop(&opeStack)));
					if (ch == endSign && getTop(opeStack) == startSign) {
						pop(&opeStack);	//清空运算符栈
						return pop(&numStack);	//返回运算结果
					}
					isp = getIsp(getTop(opeStack));	//重新获取当前栈内运算符优先级
				} while (icp < isp);
				//将操作符压入操作符栈
				push(&opeStack, ch);
			}
			//从缓存区读入下一个字符
			ch = getchar();
			//接下来+ -会被认为是正负号
			sign = 0;
		}
		else {	//此分支用于处理数字、正负号
			int num = 0;	//要入栈的数字
			int numSign = 1;//要入栈的数字的符号
			//此循环用于处理数字前面的修饰符号
			while ((isOperator(ch) && !sign) || ch == '(') {
				switch (ch) {
				case '+':
					break;	//正号则不作处理
				case '-':
					numSign = -numSign;	//负号则取将numSign反号，以支持一连串的负号
					break;
				case '(':
					//若遇到左括号，则递归调用此函数，将括号内的值压入运算数栈
					num = process(startSign, startSign, endSign);
					//()括号结构后面的第一个+或-应被理解为加减号
					sign = 1;
					break;
				}
				//从缓存区读入下一个字符
				ch = getchar();
			}
			//此循环用于支持任意整型数字的输入（不大于int上限）
			while (!isOperator(ch) && ch != startSign && ch != endSign && ch != ')') {
				num = num * 10 + (ch - 48);
				ch = getchar();
			}
			//最终综合修饰符号和数字两条路获得的结果，将最终结果入栈
			push(&numStack, num * numSign);
			//接下来的+ -会被认为是运算符
			sign = 1;
		}
	}
}
//主函数
int main() {
	//支持以除了运算符、数字、小括号以外的任何字符作为开始和结束符
	char startSign = '#';
	char endSign = '#';

	//人机交互信息
	printf("Infix Calculater by TPam\n-------------------------\n");
	printf("Your expressin must start with %c and end with %c.\n", startSign, endSign);
	printf("Please input your infix expression:\n");
	
	//之所以要将运算函数封装起来，是因为需要递归调用此函数
	printf("The result is: %d\n", process(' ', startSign, endSign));
}
