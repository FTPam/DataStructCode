//将顺序存储的二叉树存入二叉链表中存储
//bt为源顺序存储的二叉树，num应传入1
bitTree ConvertTree(sqBitTree bt, int num) {
	if (bt.length < 0 || num < 1 || num > bt.length) {
		return NULL;
	}//检查数据合法性
	//创建结点
	bitNode* node = createNode();
	node->data = bt.data[num - 1];
	//递归为其接上左右孩子
	if (2 * num <= bt.length) {
		node->LChild = ConvertTree(bt, 2 * num);
	}
	if (2 * num + 1 <= bt.length) {
		node->RChild = ConvertTree(bt, 2 * num + 1);
	}
	return node;
}
