int getDepth(bitTree bt) {
	// 如果遇到叶子，则返回0，开始计数
	if (!bt) {
		return 0;
	}
	//这部分代码是递归求深度
	int LDepth, RDepth;
	LDepth = getDepth(bt->LChild);
	RDepth = getDepth(bt->RChild);
	return (LDepth >= RDepth ? LDepth : RDepth) + 1;
}
