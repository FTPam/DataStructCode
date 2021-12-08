#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#define MAX_VERTEX_NUM 26

// 邻接表结构体
typedef char elemType;	//图所储存的数据类型
// 邻接表结点
typedef struct ArcNode {
	int adjvex;	//指向的顶点在顶点表中的下标
	int weight;	//该边的权重
	ArcNode* nextArc;	//下一个邻接边
}ArcNode;
// 顶点表
typedef struct VNode {
	elemType data;
	bool isTed;	//是否被访问过
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
// 获取Ve和Vi数组
void bfs(Graph& g, int VE[], int VL[]) {
	//如果没有结点，直接返回
	if (g.vexNum == 0) {
		return;
	}
	//创建辅助队列并让第一个结点入队列
	queue <int> q;
	int re[MAX_VERTEX_NUM], i = 0;
	q.push(0);
	g.vex[0].isTed = true;
	//计算VE
	int last;	//记录网络终点
	while (!q.empty()) {
		//遍历整个邻接表
		ArcNode* p = g.vex[q.front()].firstArc;
		re[i++] = q.front();
		while (p != NULL) {
			//将还未访问过的进行处理
			if (!g.vex[p->adjvex].isTed) {
				q.push(p->adjvex);
				VE[p->adjvex] = VE[q.front()] + p->weight;
				g.vex[p->adjvex].isTed = true;
			}
			else {
				//如果当前路径获得的权重大于原权重，则更新
				if (VE[q.front()] + p->weight > VE[p->adjvex]) {
					VE[p->adjvex] = VE[q.front()] + p->weight;
				}
			}
			VL[p->adjvex] = VE[p->adjvex];	//初始化一遍VL
			p = p->nextArc;
		}
		//删除当前结点
		last = q.front();
		q.pop();
	}
	i = i - 2;
	while (i > 0) {
		//遍历整个邻接表
		ArcNode* p = g.vex[i].firstArc;
		while (p != NULL) {
			if (VL[p->adjvex] - p->weight > VL[i]) {
				VL[i] = VL[p->adjvex] - p->weight;
			}
			p = p->nextArc;
		}
		i--;
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
	file.ignore(1);	//清除掉上一行的换行符
	for (int i = 0; i < g.vexNum - 1; i++) {
		while (1) {
			char temp = file.peek();
			if (file.peek() == ';' || file.eof()) {
				file.ignore(1);	//跳过分号
				break;	//开始记录邻接表的下一行
			}
			else if (file.peek() == ',') {
				file.ignore(1);	//跳过逗号
				char temp = file.peek();
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

	int VE[MAX_VERTEX_NUM] = { 0 }, VL[MAX_VERTEX_NUM] = { 0 };
	bfs(g, VE, VL);

	cout << "VE[]: ";
	for (int i = 0; i < g.vexNum; i++) {
		printf("%3d", VE[i]);
	}
	cout << endl << "VL[]: ";
	for (int i = 0; i < g.vexNum; i++) {
		printf("%3d", VL[i]);
	}
	cout << endl;
}
