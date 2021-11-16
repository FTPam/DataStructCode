//给一个左右孩子已经填充好的二叉树填上父母
//parent应传入NULL
void getParent(bitTree bt, bitTree parent) {
	if (bt == NULL) {
		return;
	}	//如果传入的结点为空，则直接返回
	if (parent) {
		bt->parent = parent;
	}	//如果是从父母来的，就给结点填上父母
	//递归
	getParent(bt->LChild, bt);
	getParent(bt->RChild, bt);
}
