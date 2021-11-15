//求先序序列中第k个位置节点的值
//d为目标位置，t为根节点编号
int getPreK(bitTree bt, int d, int t, elemType* data) {
	if (!bt)
		return t - 1;	//若传入的是空树，则返回t - 1，表示并未前进
	if (t == d + 1) {
		return t;	//若已经找到，则返回t
	}
	if (t == d) {
		*data = bt->data;
		return t + 1;	//若找到了，则将值传给data，并返回t+1，告诉后面的代码，data已经求得
	}
	t = getPreK(bt->LChild, d, t + 1, data);	//继续查找左子树
	if (t == d + 1) {
		return t;	//若已经在左子树找到，则返回t
	}
	t = getPreK(bt->RChild, d, t + 1, data);	//继续查找右子树
}

//使用方法
int main() {
	elemType data = NULL;
	bitTree bt = preOrderCreateTree();  //先序序列创建二叉树
	getPreK(bt, 7, 1, &data); //若根节点为“第一个元素”，查找该二叉树中第7个元素
	printf("%c", data);
}
