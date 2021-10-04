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
	case '(':
	case ')':
	case '#':
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
	case '(':
		return 1;
	case '#':
		return 0;
	default:
		return -1;
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
	case '#':
		return 0;
	default:
		return -1;
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
//主函数
int main() {
	stack* numStack = NULL, * opeStack = NULL;
	char ch;
	elemType result = 0;

	printf("Please input your infix expression\n");
	printf("Your expressin must start and end with #\n");
	ch = getchar();
	int sign = 1;//用于判断即将读入的'+'、'-'是加减号还是正负号
	/*判断'+'、'-'是加减号还是正负号的方法是：
	先默认它是加减号
	之后每次往运算符栈加入一个符号后，就将sign设为0
	sign为0时，'+'、'-'它被认为是正负号
	之后每次往运算数栈加入一个数字后，就将sign设为1
	sign为1时，'+'、'-'它被认为是加减号*
	而特殊情况是，小括号前后是可以跟正负号的
	因此，加入了(sign || ch == '(' || ch == ')')条件*/
	while (1) {
		if (isOperator(ch) && (sign || ch == '(' || ch == ')')) {
			int icp = getIcp(ch);
			int isp = getIsp(getTop(opeStack));

			if (icp > isp) {
				push(&opeStack, ch);
			}
			else {
				do {
					push(&numStack, calculate(pop(&numStack), pop(&numStack), pop(&opeStack)));
					if (ch == '#' && getTop(opeStack) == '#') {
						result = pop(&numStack);
						goto end;
					}
					if (ch == ')' && getTop(opeStack) == '(') {
						pop(&opeStack);
						ch = getchar();
						icp = getIcp(ch);
					}
					isp = getIsp(getTop(opeStack));
				} while (icp < isp);
				if (ch != ')')
					push(&opeStack, ch);
			}
			ch = getchar();
			if (ch != '(')
				sign = 0;
		}
		else {	//数字则无条件入栈
			int num = 0;
			int numSign = 1;
			if (isOperator(ch) && !sign) {
				if (ch == '+')
					numSign = 1;
				else
					numSign = -1;
				ch = getchar();
			}
			while (!isOperator(ch)) {
				num = num * 10 + (ch - 48);
				ch = getchar();
			}
			push(&numStack, num * numSign);
			sign = 1;
		}
	}
end:
	printf("= %d", result);
}