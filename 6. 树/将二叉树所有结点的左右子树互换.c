//将二叉树中所有结点的左右子树相互交换
void change(bitTree bt) {
	if (!bt)
		return;	//若bt为空，则直接返回
	//否则，开始交换
	bitTree* t = bt->LChild;
	bt->LChild = bt->RChild;
	bt->RChild = t;
	change(bt->LChild);
	change(bt->RChild);
}
