//判断两棵二叉树是否相似
//返回1表示相似，返回0表示不相似
int isLike(bitTree B1, bitTree B2) {
	if (!B1 ^ !B2) {
		return 0;   //若B1和B2一个存在，一个不存在，则返回0
	}
	if (!B1 && !B2) {
		return 1;   //若B1和B2都不存在，则直接返回1
	}
	//若B1和B2都存在，则递归遍历其左右子树
	int left, right;
	left = isLike(B1->LChild, B2->LChild);
	right = isLike(B1->RChild, B2->RChild);
	return left && right;
}
