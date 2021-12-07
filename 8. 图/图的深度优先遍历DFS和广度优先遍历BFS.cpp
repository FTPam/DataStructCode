#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#define MAX_VERTEX_NUM 26
// 邻接表结构体
typedef char elemType;	//图所储存的数据类型
// 邻接表结点
typedef struct ArcNode {
	int adjvex;	//在顶点表中的下标
	ArcNode* nextArc;	//下一个邻接边
}ArcNode;
// 顶点表
typedef struct VNode {
	elemType data;
	bool isTed;	//是否被访问过
	ArcNode* firstArc;
}VNode, AdjList[MAX_VERTEX_NUM];
// 图结构体
typedef struct Graph { 
	AdjList vex;	//顶点表
	int vexNum, arcNum;	//顶点数量、边数量
}Graph;
// 给图添加边
// g为要添加的图，vex为顶点在顶点表中的下标
// des为相邻顶点在顶点表中的下标
void addEdge(Graph& g, int vex, int des) {
	ArcNode* p = g.vex[vex].firstArc;
	ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
	node->adjvex = des;
	node->nextArc = NULL;
	// 如果还没有第一条边，则加上
	if (!p) {
		g.vex[vex].firstArc = node;
	}
	else {
		// 移动到最后一个结点
		while (p->nextArc!=NULL) {
			p = p->nextArc;
		}
		p->nextArc = node;
	}
}
// 深度优先遍历
// g为要遍历的图，v为顶点序号
// 调用时，v一般应该传入0
void dfs(Graph& g, int v) {
	//如果没有结点，直接返回
	if (g.vexNum == 0) {
		return;
	}
	//输出当前结点
	cout << g.vex[v].data;
	g.vex[v].isTed = true;
	//递归深入
	ArcNode* p = g.vex[v].firstArc;
	while (p != NULL) {
		if (!g.vex[p->adjvex].isTed) {
			dfs(g, p->adjvex);
		}
		p = p->nextArc;
	}
}
// 广度优先遍历
// g为要遍历的图
void bfs(Graph& g) {
	//如果没有结点，直接返回
	if (g.vexNum == 0) {
		return;
	}
	//创建辅助队列并让第一个结点入队列
	queue <int> q;
	q.push(0);
	g.vex[0].isTed = true;
	while (!q.empty()) {
		//输出当前结点并标记为已访问过
		cout << g.vex[q.front()].data;
		//将与该节点相邻的所有结点入队列
		ArcNode* p = g.vex[q.front()].firstArc;
		while (p != NULL) {
			if (!g.vex[p->adjvex].isTed) {
				q.push(p->adjvex);
				g.vex[p->adjvex].isTed = true;
			}
			p = p->nextArc;
		}
		//删除当前结点
		q.pop();
	}
}
// 重新初始化图，将所有结点都设置为未访问过
void initalG(Graph& g) {
	for (int i = 0; i < g.vexNum; i++) {
		g.vex[i].isTed = false;
	}
}
// 主函数
int main() {
	char fileName[] = "source.txt";
	cout << "正在从" << fileName << "读入数据..." << endl;
	ifstream  file;
	file.open(fileName, ios::in);
	
	Graph g;
	int vNum;
	// 读入结点
	for (vNum = 0; file.peek() != '\n'; vNum++) {
		file >> g.vex[vNum].data;
		g.vex[vNum].isTed = false;
		g.vex[vNum].firstArc = NULL;
	}
	g.vexNum = vNum;
	// 读入边
	file.ignore(1);	//清除掉上一行的换行符
	for (int i = 0; !file.eof() && i < g.vexNum; i++) {
		while (1) {
			if (file.peek() == '\n' || file.eof()) {
				file.ignore(1);
				break;	//换行
			}
			else {
				int adj;
				file >> adj;
				addEdge(g, i, adj);
			}
		}
	}
	cout << "数据读入完毕..." << endl;
	cout << "深度优先遍历结果: ";
	dfs(g, 0);
	initalG(g);
	cout << endl << "广度优先遍历结果: ";
	bfs(g);
}
