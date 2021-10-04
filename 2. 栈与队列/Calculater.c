#include <stdio.h>
#include <stdlib.h>

typedef int status;		//用1表示成功，用0表示失败
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
//压栈，成功则返回1，否则返回0
status push(stack** head, elemType data) {
	*(head) = createNode(data, *(head));
	return 1;
}
/*出栈，并返回弹出的值，若为空返回NULL
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
	return -1;
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
void DisplayList(stack* head) {
	head = head->next;	//先将指针移动到头结点的下一个结点
	while (head != NULL) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}
//处理缓冲区中的字符
//支持以除了运算符、小括号、数字以外的任意字符作为开始和结束符
elemType process(char ch, char startSign, char endSign) {
	stack* numStack = NULL, * opeStack = NULL;

	if (ch == ' ')
		ch = getchar();	//如果没有传入初始ch值，则从缓存区读一个
	int sign = 1;	//默认将+ -理解为操作符

	while (1) {
		if (ch == ')')	//一律将右括号处理为结束符
			ch = endSign;
		if ((isOperator(ch) && sign) || ch == startSign || ch == endSign) {
			int icp = getIcp(ch);	//获取栈外运算符优先级
			//获取栈内运算符优先级，若为空则将isp设为-1
			int isp = getTop(opeStack) == -1 ? -1 : getIsp(getTop(opeStack));

			//如果icp>isp则直接入栈
			if (icp > isp) {
				push(&opeStack, ch);
			}
			else {
				if (ch == endSign && getTop(opeStack) == startSign) {
					pop(&opeStack);	//清空运算符栈
					return pop(&numStack);	//返回运算结果
				}
				do {
					push(&numStack, calculate(pop(&numStack), pop(&numStack), pop(&opeStack)));
					if (ch == endSign && getTop(opeStack) == startSign) {
						pop(&opeStack);	//清空运算符栈
						return pop(&numStack);	//返回运算结果
					}
					isp = getIsp(getTop(opeStack));	//重新获取当前栈内运算符优先级
				} while (icp < isp);	//一直运算，直到栈外运算符优先级大于栈内元素优先级
				push(&opeStack, ch);	//直到栈外运算符优先级大于站内运算符后，才让入栈
			}
			ch = getchar();
			sign = 0;
		}
		else {	//如果是数字、+、-、小括号
			int num = 0;	//后面一坨的值
			int numSign = 1;	//后面一坨运算符的符号，默认为正
			while ((isOperator(ch) && !sign) || ch == '(') {
				switch (ch) {
				case '+':
					numSign = 1;
					break;
				case '-':
					numSign = -1;
					break;
				case '(':
					num = process('#', '#', '#');
					sign = 1;
					break;
				}
				ch = getchar();
			}
			while (!isOperator(ch) && ch != startSign && ch != endSign && ch != ')') {	//终于读到数字之后，获取数字的值
				num = num * 10 + (ch - 48);	//目的是获取任意位数的数字（不超过int上限）
				ch = getchar();
			}
			push(&numStack, num * numSign);
			sign = 1;
		}
	}
}

//主函数
int main() {
	printf("Infix Calculater\n---------------\n");
	printf("Your expressin must start and end with #.\n");
	printf("Please input your infix expression:\n");
	
	//之所以将处理缓冲区的功能封装起来，是因为需要递归调用
	//传入空的头字符，以#作为开始和结束标志
	printf("The result is: %d\n", process(' ', '#', '#'));
}