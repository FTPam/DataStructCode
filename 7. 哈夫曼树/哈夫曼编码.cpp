#pragma warning(disable:4996)
#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 100

typedef char elemType;
//哈夫曼树结点结构
typedef struct {
	int parent, LChild, RChild;	//父母左右孩子
	double weight;	//结点权重
}HF_BTNode;
//哈夫曼树结构
typedef struct {
	int n;	//符号数量
	elemType s[MAX_SIZE];	//符号表
	double weight[MAX_SIZE];	//权重
	char code[MAX_SIZE][MAX_SIZE + 1];	//编码表
	HF_BTNode hf[2 * MAX_SIZE - 1];	//码树
}HFT;
// 找到某一个字符的编码，并返回其编码长度
// i是目标字符在HFT的s中的下标，h是HFT，char[]用于返回编码
// mode是模式，传入1则在字符串末尾加\0，否则不加
int codeChar(char i,  HFT h, char* re, int mode) {
	int j, p = i;
	char code[MAX_SIZE];
	//从叶子往上找根
	for (j = 0; h.hf[p].parent != -1; j++) {
		if (h.hf[h.hf[p].parent].LChild == p) {
			code[j] = 48;	//左叶子则为0
		}
		else {
			code[j] = 49;	//右叶子则为1
		}
		p = h.hf[p].parent;
	}
	//逆序
	int k;
	for (k = 0; j >= 0; j--, k++) {
		re[k] = code[j - 1];
	}
	if (mode == 1) {
		re[k - 1] = '\0';
	}
	return k - 1;
}
//创建哈夫曼树
void createHFT(HFT& h) {
	int length = h.n * 2 - 1;
	//初始化，关系部分置为0，权重初始化
	for (int i = 0; i < length; i++) {
		if (i < h.n) {
			h.hf[i].weight = h.weight[i];
		}
		h.hf[i].parent = -1;
		h.hf[i].LChild = -1;
		h.hf[i].RChild = -1;
	}
	//从n到length，作为空的结点，填入左右孩子
	for (int i = h.n; i < length; i++) {
		//找到从0到n第一个没有父母的结点
		int j;
		for (j = 0; j < i; j++) {
			if (h.hf[j].parent == -1) {
				break;
			}
		}
		//找到从j+1到n权值最小的结点
		for (int k = j + 1; k < i; k++) {
			if (h.hf[k].weight < h.hf[j].weight && h.hf[k].parent == -1) {
				j = k;
			}
		}
		//将它作为左孩子接入
		h.hf[i].LChild = j;
		h.hf[j].parent = i;
		//找到从0到n第一个没有父母的结点
		for (j = 0; j < i; j++) {
			if (h.hf[j].parent == -1) {
				break;
			}
		}
		//找到从j+1到n权值最小的结点
		for (int k = j + 1; k < i; k++) {
			if (h.hf[k].weight < h.hf[j].weight && h.hf[k].parent == -1) {
				j = k;
			}
		}
		//将它作为右孩子接入
		h.hf[i].RChild = j;
		h.hf[j].parent = i;
		//将该结点的左右孩子权值相加
		h.hf[i].weight = h.hf[h.hf[i].LChild].weight + h.hf[h.hf[i].RChild].weight;
	}
	//创建编码表
	for (int i = 0; i < h.n; i++) {
		codeChar(i, h, h.code[i], 1);
	}
}
// 字符串转哈夫曼编码并返回编码字符串
// 成功返回1，失败返回0
// h是HFT，ch是要翻译的字符串，code用于返回翻译结果
int codeString(HFT h, char* ch, char* code) {
	int length = 0;
	for (int i = 0; ch[i] != '\0'; i++) {
		//找到它在字符表里的下标
		int j;
		char tempcode[MAX_SIZE];
		for (j = 0; j < h.n; j++) {
			if (h.s[j] == ch[i]) {
				break;
			}
		}
		if (j == h.n) {
			return 0;
		}
		int len = codeChar(j, h, tempcode, 0);
		for (int k = 0; k < len; k++) {
			code[length] = tempcode[k];
			length++;
		}
	}
	code[length] = '\0';
	return 1;
}
// 译码并输出
// hf是HFT，s是要翻译的字符串, re是返回的字符数组
void translate(HFT hf, char s[], char* re) {
	int p = hf.n * 2 - 2;
	int length = 0;	//记录当前翻译到了第几个字符
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == '0') {
			p = hf.hf[p].LChild;
		}
		else {
			p = hf.hf[p].RChild;
		}
		if (hf.hf[p].LChild == -1 && hf.hf[p].RChild == -1){
			re[length++] = hf.s[p];
			p = hf.n * 2 - 2;
			continue;
		}
	}
	re[length] = '\0';
}
//主函数
int main() {
	HFT hf;
	HF_BTNode test;
	printf("*****欢迎使用哈弗曼编码系统*****\n");
	printf("请输入要编码的字符数量: ");
	scanf("%d", &hf.n);
	getchar();
	printf("请依次输入字符及其对应的权重，格式如：A-0.5; B-0.3;\n");
	//输入字符的权重对应表
	for (int i = 0; i < hf.n; i++) {
		float a;
		scanf("%c-%f;", hf.s + i, &a);
		hf.weight[i] = a;
	}
	
	createHFT(hf);
	printf("哈夫曼编码已经生成，对应表如下：\n");
	for (int i = 0; i < hf.n; i++) {
		printf("- %c: %s\n", hf.s[i], hf.code[i]);
	}

	char code[MAX_SIZE], result[MAX_SIZE];
	while (1) {
		int ope;
		//人机交互部分
		printf("============菜单============\n");
		printf("[1] 字符串转哈夫曼编码\n");
		printf("[2] 退出系统\n请输入操作代码: ");
		cin >> ope;
		switch (ope) {
		case 1:
			printf("[*] 请输入要翻译的字符串: ");
			char ch[MAX_SIZE];
			cin >> ch;
			if (codeString(hf, ch, code)) {
				printf("[+] 哈夫曼编码: %s\n", code);
				translate(hf, code, result);
				printf("[+] 翻译得到串: %s\n", result);
				if (!strcmp(ch, result)) {
					printf("[+] 经比对，输出等于输入\n");
				}
				else {
					printf("[-] 经比对，输出不等于输入\n");
				}
			}
			else {
				printf("[+] 字符串中包含无法识别的字符\n");
			}
			if(code)
			break;
		case 2:
			printf("感谢使用，再见！");
			exit(0);
		default:
			printf("输入错误，请重新输入！");
		}
	}
}
