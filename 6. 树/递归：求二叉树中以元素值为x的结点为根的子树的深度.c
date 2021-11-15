//求二叉树中以元素值为x的结点为根的子树的深度
//bt为要查找的二叉树，x为目标位置的值， tag必须为0
//depth为深度的起始值，必须为0
//若二叉树中不存在值为x的结点，则会返回0
int getDepthX(bitTree bt, elemType x, int tag, int depth) {
	if (!bt) {
		return depth - 1;
	}	//如果传入的二叉树为空，则返回depth - 1，表示深度并未增加
	if (bt->data == x && !tag) {
		return getDepthX(bt, x, 1, 0) + 1;
	}	//此时将递归函数从“寻找模式”切换到“求深度模式”
	if (!tag) {
		int LNum = 0, RNum = 0;
		if (bt->LChild)
			LNum = getDepthX(bt->LChild, x, 0, 0);
		if (bt->RChild)
			RNum = getDepthX(bt->RChild, x, 0, 0);
		return LNum ? LNum : RNum;
	}	//若未找到，则继续在“寻找模式”下寻找根节点
	//这部分代码是递归求深度
	int LDepth, RDepth;
	LDepth = getDepthX(bt->LChild, x, tag, depth + 1);
	RDepth = getDepthX(bt->RChild, x, tag, depth + 1);
	return LDepth >= RDepth ? LDepth : RDepth;
}
