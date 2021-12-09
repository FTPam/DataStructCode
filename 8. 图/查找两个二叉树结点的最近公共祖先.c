// 查找两个二叉树结点的最近公共祖先
// p和q为两个节点的值，back用于返回其公共祖先的值
// 查找成功返回-1，部分值查找不到则返回0或1，其中一个查找值为根节点则返回2
int preOrder(bitTree bt, bitTree p, bitTree q, elemType* back) {
	// 若为叶子，则直接返回0
	if (bt == NULL) {
		return 0;
	}
	// 因为是求公共祖先，所以立即往深处递归
	int num = preOrder(bt->LChild, p, q, back) + preOrder(bt->RChild, p, q, back);
	// 递归完成后再判断自身是否是目标结点
	if (num == 2) {
		*back = bt->data;
		return -1;
	}
	if (bt == p || bt == q) {
		num++;
	}
	return num;
}
