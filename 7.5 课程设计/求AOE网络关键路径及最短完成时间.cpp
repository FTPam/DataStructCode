#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

#define MAX_VERTEX_NUM 26

typedef char elemType;	// 储存char型数据
// 邻接表结点
typedef struct ArcNode {
	int adjvex;	// 下一个顶点在顶点表中的下标
	int weight;	// 该边的权重
	ArcNode* nextArc;	// 下一个邻接边
}ArcNode;
// 顶点表
typedef struct VNode {
	elemType data;
	bool isTed;	// 该节点是否已被访问过
	ArcNode* firstArc;
}VNode, AdjList[MAX_VERTEX_NUM];
// AOE网络结构体
typedef struct Graph {
	AdjList vex;	//顶点表
	int vexNum, arcNum;	//顶点数量、边数量
}Graph;
// 给图添加边
// g为要添加的图，vex为顶点在顶点表中的下标
// des为相邻顶点在顶点表中的下标
void addEdge(Graph& g, int vex, int des, int weight) {
	ArcNode* p = g.vex[vex].firstArc;
	ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
	node->adjvex = des;
	node->weight = weight;
	node->nextArc = NULL;
	// 如果还没有第一条边，则加上
	if (!p) {
		g.vex[vex].firstArc = node;
	}
	else {
		// 移动到最后一个结点
		while (p->nextArc != NULL) {
			p = p->nextArc;
		}
		p->nextArc = node;
	}
}
// 获取Ve和Vi数组，并返回拓扑序列数组
int* getVEI(Graph& g, int VE[], int VL[]) {
	// 如果没有结点，直接返回
	if (g.vexNum == 0) {
		return NULL;
	}
	int in[MAX_VERTEX_NUM] = { 0 };	// 记录各顶点入度
	// 拓扑序列存储数组
	int* topSort = (int*)malloc(sizeof(int) * MAX_VERTEX_NUM);
	if (topSort == NULL) {
		exit(0);
	}
	stack <int> stack;	// 辅助进行拓补排序
	// 遍历图，获取结点入度表，并初始化VE和辅助栈
	for (int i = 0; i < g.vexNum; i++) {
		// 遍历整个邻接表，并将入度为0的顶点入栈和队列
		ArcNode* p = g.vex[i].firstArc;
		while (p != NULL) {
			in[p->adjvex]++;
			p = p->nextArc;
		}
		// 初始化VE数组
		VE[i] = 0;
	}
	for (int i = 0; i < g.vexNum; i++) {
		// 压入入度为0的结点
		if (in[i] == 0) {
			stack.push(i);
		}
	}
	int topSorti = 0;	// 帮助建立拓扑排序结果数组
	// 遍历图，进行拓补排序
	while (!stack.empty()) {
		int i = stack.top();
		topSort[topSorti++] = i;
		stack.pop();
		ArcNode* p = g.vex[i].firstArc;
		while (p != NULL) {	// 遍历该节点的边，将新的入度为0的结点入栈
			in[p->adjvex]--;
			if (in[p->adjvex] == 0) {
				stack.push(p->adjvex);
			}
			p = p->nextArc;
		}
	}
	if (topSorti != g.vexNum) {
		exit(0);	// 拓补排序失败，图有环
	}
	// 开始计算VE数组，同时初始化VL数组
	for (int i = 0; i < g.vexNum; i++) {
		//遍历整个邻接表
		ArcNode* p = g.vex[i].firstArc;
		while (p != NULL) {
			//如果当前路径获得的权重大于原权重，则更新
			if (VE[i] + p->weight > VE[p->adjvex]) {
				VE[p->adjvex] = VE[i] + p->weight;
			}
			VL[p->adjvex] = VE[p->adjvex];	// 初始VL=VE
			p = p->nextArc;
		}
	}
	// 计算VL数组，从拓扑序列最后一个结点，逆序向前计算
	for (int i = g.vexNum - 1; i > 0; i--) {

		//遍历整个邻接表
		ArcNode* p = g.vex[topSort[i]].firstArc;
		while (p != NULL) {
			if (VL[p->adjvex] - p->weight > VL[topSort[i]]) {
				VL[topSort[i]] = VL[p->adjvex] - p->weight;
			}
			p = p->nextArc;
		}
	}
	return topSort;
}
// 输出关键路径
// g为图，VE和VL为VE VL数组，top为拓扑序列数组
void printCP(Graph g, int VE[], int VL[], int* top) {
	ArcNode* p = g.vex[top[0]].firstArc;
	printf("%c ", g.vex[top[0]].data);
	while (p != NULL) {
		if (VL[p->adjvex] == VE[p->adjvex]) {
			printf("%c ", g.vex[p->adjvex].data);
			p = g.vex[p->adjvex].firstArc;
			continue;
		}
		p = p->nextArc;
	}
}
// 从文件读入数据
// 格式：顶点为第一行，以空格分割
// 邻接表以 下一节点编号-权重, 的格式输入，每一行以分号结束
void readFile(Graph& g, char fileName[]) {
	ifstream  file;
	file.open(fileName, ios::in);
	int vNum;
	// 读入结点
	for (vNum = 0; file.peek() != '\n'; vNum++) {
		file >> g.vex[vNum].data;
		g.vex[vNum].isTed = false;
		g.vex[vNum].firstArc = NULL;
	}
	g.vexNum = vNum;
	g.arcNum = 0;
	// 读入边
	for (int i = 0; i < g.vexNum; i++) {
		while (1) {
			char temp = file.peek();
			if (file.peek() == '\n') {
				file.ignore(1);
			}
			if (file.peek() == ';' || file.eof()) {
				file.ignore(1);	//跳过分号
				break;	//开始记录邻接表的下一行
			}
			else if (file.peek() == ',') {
				file.ignore(1);	//跳过该符号
			}
			int adj;
			int weight;
			file >> adj >> weight;
			addEdge(g, i, adj, -weight);
			g.arcNum++;
		}
	}

}
// 主函数
int main() {
	char fileName[] = "source.txt";
	Graph g;
	cout << "正在从" << fileName << "读入数据..." << endl;
	readFile(g, fileName);
	cout << "数据读入完毕..." << endl << endl;

	if (g.arcNum == 0) {
		printf("至少需要一条边");
		exit(0);
	}

	int VE[MAX_VERTEX_NUM] = { 0 }, VL[MAX_VERTEX_NUM] = { 0 };
	int* topSort = getVEI(g, VE, VL);

	cout << "关键路径: ";
	printCP(g, VE, VL, topSort);

	cout << endl << "最短完成时间: " << VE[topSort[g.vexNum - 1]] << endl;
}
