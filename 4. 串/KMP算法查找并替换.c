#include <stdio.h>
#include <string.h>

void getNext(char* ch, int* next);
void replace(char* s, char* t2, int loc, int length);

int main() {
	//s为主串，t1为模式串，t2为要替换进去的内容
	char s[100], t1[100], t2[100];
	//i为主串游标，j为模式串游标, count为总计匹配到的次数
	//next为t1的next数组，用于指导模式串在失配时的回溯
	int i = 0, j = 0, count = 0, next[100];

	//人机交互部分，获取s、t1、t2
	printf("Please type in s: ");
	gets(s);
	printf("String s is: %s\n", s);
	printf("Please type in t1: ");
	gets(t1);
	printf("Please type in t2: ");
	gets(t2);

	getNext(t1, next);	//获取next数组

	while (i < strlen(s)) {
		//当s[i]与t1[j]匹配，或j为-1（模式串该后移一位）时
		if (s[i] == t1[j] || j == -1) {
			//若匹配，则先判断是否已经比到末尾
			if (j == strlen(t1) - 1) {
				//若已完全匹配，则执行替换
				replace(s, t2, i - strlen(t1) + 1, strlen(t1));
				//匹配次数+1
				count++;
				//移动比较位置
				i += strlen(t2);
				j = 0;
			}
			//如果还没比完，则模式串和主串的游标都往后一位
			//若j=-1，则表示游标回到模式串的首位，并和主串的下一位对齐
			else {
				i++;
				j++;
			}
		}
		else {
			//如果不等，则j回到next[j]
			j = next[j];
		}
	}

	//输出总共的匹配次数，以及查找替换后的s
	printf("Totoal match: %d\nNow, s is %s\n", count, s);
}

//获取模式串的优化next函数
void getNext(char* ch, int* next) {
	//先将next[0]定义为-1
	next[0] = -1;
	int i = 0, j = -1;
	while (i < strlen(ch) - 1) {
		if (ch[i] == ch[j] || j == -1) {
			//写入下一位的next值
			next[i + 1] = ++j;
			//优化next数组
			if (ch[i + 1] == ch[next[i + 1]]) {
				next[i + 1] = next[next[i + 1]];
			}
			i++;
		}
		else {
			//回到next[j]重新比较
			j = next[j];
		}
	}
}

//将*s字符串中，从loc开始，长度为length的范围，替换为t2
void replace(char* s, char* t2, int loc, int length) {
	//先处理s，为t2腾出刚好够的位置

	//获取t2与要替换的部分的长度差
	int n = strlen(t2) - length;
	//如果t2比要替换的部分长
	if (n > 0) {
		for (int i = strlen(s) + n; i >= loc + length; i--)
			s[i] = s[i - n];
	}
	//如果t2比要替换的部分短
	else if (n < 0) {
		int i = loc + length;
		for (; i < strlen(s); i++)
			s[i + n] = s[i];
		s[i + n] = '\0';	//截断多出来的部分
	}

	//将t2写入中间
	for (int j = 0; j < strlen(t2); j++) {
		s[loc + j] = t2[j];
	}
}
