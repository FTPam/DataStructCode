//求二叉树叶子数量
//bt为要查找的二叉树，num一般应设置为0（从num开始计数）
int getLeaveNum(bitTree bt, int num) {
	if (!bt) {
		return num;	//若传入的是空节点，则返回num，表示num不变
	}
	if (!bt->LChild && !bt->RChild) {
		return num + 1;	//若找到一片叶子，则num+1
	}
	num = getLeaveNum(bt->LChild, num);
	num = getLeaveNum(bt->RChild, num);
	return num;
}
