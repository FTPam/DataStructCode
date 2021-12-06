#pragma warning(disable:4996)
#include <stdio.h>
#define MAX_VERTEX_NUM 26
// 邻接表结构体
typedef char elemType;	//用字母代表事件
// 顶点表
typedef struct VNode {
	elemType data;
	ArcNode* firstArc;
}VNode, AdjList[MAX_VERTEX_NUM];
// 邻接表结点
typedef struct ArcNode {
	int adjvex;	//在顶点表中的下标
	double weight;	//权重
	ArcNode* nextArc;	//下一个邻接边
}ArcNode;
// 图结构体
typedef struct ALGraph {
	AdjList vex;	//顶点表
	int vexNum, arcNum;	//顶点数量、边数量
};
// 主函数
int main() {
	char fileName[] = "source.txt";
	printf("正在读入文件……");

}
