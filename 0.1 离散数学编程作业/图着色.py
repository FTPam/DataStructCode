import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()  # 创建图

# 读入结点
nodes = input("请输入图的结点，以空格分割: ")
nodes = nodes.split()
for n in nodes:
    G.add_node(n)

# 读入边
print("请依次输入每个点的邻接点，每个点一行，以空格分割: ")
for n in nodes:
    edge = input()
    edge = edge.split()
    for e in edge:
        G.add_edge(n, e)

# 按度数排序
d = G.degree()
d = sorted(d, key=lambda x: (x[1]), reverse=True)

# 开始着色
colors = {}
i = 0
for j in range(len(d)):
    for (v, degree) in d:           # 遍历结点度数排序表
        if v in colors:             # 如果已经着色，则跳过
            continue
        flag = 0                    # 记录邻接点中是否有相同颜色
        for vn in G[v]:             # 遍历v的邻接点
            if vn not in colors:
                continue
            if colors[vn] == i:     # 表示邻接点中有该颜色了
                flag = 1
                break
        if flag == 0:
            colors[v] = i           # 着色
    i = i + 1                       # 加入新颜色

print(colors)                       # 输出结果

# 使用matplot画图
plt.figure(figsize=(7, 7))
pos = nx.spring_layout(G, seed=2020114936)                    # 生成一个位置，种子是我的学号。这是为了保证用有颜色的点覆盖的时候能够重叠到之前的图上
mat_colors = {0: 'lightcoral', 1: 'lightgreen', 2: 'lightblue', 3: 'lightyellow'}   # 根据四色定律，只会有四种颜色，所以可以枚举（平面图）
nx.draw(G, pos)     # 画图
for c in colors:    # 然后用有颜色的点覆盖原来的点
    nx.draw_networkx_nodes(G, pos, nodelist=c, node_color=mat_colors[colors[c]])

plt.show()
