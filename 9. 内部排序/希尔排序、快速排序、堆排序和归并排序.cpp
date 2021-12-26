#include <iostream>
#include <math.h>
using namespace std;

#define ARRAY_LENGTH 20+1

typedef struct {
	int arr[ARRAY_LENGTH];	// 数组
	int length;				//数组长度
}sortArr;
// 希尔排序
void shellSort(sortArr& s) {
	for (int k = log2(s.length + 1); k >= 1; k--) {	// d为增量，采用Hibbard增量序列
		int d = pow(2, k) - 1;
		for (int i = 1 + d; i <= s.length; i++) {	// 将此增量依次应用于每个元素
			int* a = &s.arr[0];
			if (a[i] < a[i - d]) {	// 若当前元素小于上一个元素，则需要将该元素插入到前面的序列中
				int j;
				a[0] = a[i];	// 将要插入的值记录到0号位
				for (j = i - d; j >= 1 && a[j] > a[0]; j -= d) {	// 按照增量进行插入
					a[j + d] = a[j];
				}
				a[j + d] = a[0];
			}
		}
	}
}
// 交换两个指针储存的数字
void mySawp(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}
// 快速排序
void qSort(sortArr& a, int low, int high) {
	if (low >= high) {
		return;
	}
	int rLow = low, rHigh = high;	// 记录原始的low和high
	// 按照三者取中算法计算枢轴
	int max, min, mid;
	max = a.arr[high] >= a.arr[low] ? high : low;
	min = a.arr[high] >= a.arr[low] ? low : high;
	mid = (high + low) / 2;
	if (a.arr[(high + low) / 2] > a.arr[max]) {
		mid = max;	// 若中间位置大于最大值，则当前最大值为mid
	}
	else if (a.arr[(high + low) / 2] < a.arr[min]) {
		mid = min;	// 若中间位置小于最小值，则当前最小值为mid
	}
	mySawp(a.arr[low], a.arr[high]);
	int pivo = low;
	// 开始进行此趟快速排序
	a.arr[0] = a.arr[pivo];	// 在零位记录枢轴值
	while (low < high) {
		while (low < high && a.arr[high] >= a.arr[0]) {
			high--;
		}
		a.arr[low] = a.arr[high];
		while (low < high && a.arr[low] <= a.arr[0]) {
			low++;
		}
		a.arr[high] = a.arr[low];
	}
	a.arr[low] = a.arr[0];
	pivo = low;
	if (rLow < rHigh) {
		qSort(a, rLow, pivo - 1);	// 递归处理左侧
		qSort(a, pivo + 1, rHigh);	// 递归处理右侧
	}
}
// 快速排序
void quickSort(sortArr& a) {
	qSort(a, 1, a.length);
}
// 调整堆
void heapAdj(int* s, int i, int length) {
	int j = i;
	while (s[j] > s[2 * j] || s[j] > s[2 * j + 1]) {
		// 让根节点与最小的子树交换
		int nextj;
		if (2 * j > length) {
			break;
		}
		else if (2 * j + 1 > length) {
			nextj = 2 * j;
		}
		else {
			nextj = s[2 * j] > s[2 * j + 1] ? 2 * j + 1 : 2 * j;
		}
		int t = s[nextj];
		s[nextj] = s[j];
		s[j] = t;
		j = nextj;	// 开始检查子树
	}
}
// 堆排序
void heapSort(sortArr& a) {
	sortArr sort = a;
	// 建成初始堆
	for (int i = sort.length / 2; i >= 1; i--) {
		heapAdj(sort.arr, i, sort.length);
	}
	// 开始排序
	for (int i = 1; sort.length > 0; i++, sort.length--) {
		a.arr[i] = sort.arr[1];
		sort.arr[1] = sort.arr[sort.length];
		heapAdj(sort.arr, 1, sort.length);
	}
}
// 归并排序
void mergeSort(sortArr& a) {
	sortArr s = a;
	for (int d = 1; d < a.length; d *= 2) {	// 控制归并的子数组大小
		int* sort = s.arr;	// 临时存放归并数组
		for (int k = 1, m = 1 + d; m <= a.length; k = m + d, m = k + d) {
			int i, j;
			// 开始归并
			for (i = 0, j = 0; i < d && j < d && m + j <= a.length;) {
				if (a.arr[k + i] <= a.arr[m + j]) {
					sort[k + i + j] = a.arr[k + i];
					i++;
				}
				else {
					sort[k + i + j] = a.arr[m + j];
					j++;
				}
			}
			// 合并剩余部分
			while (i < d) {
				sort[k + i++ + j] = a.arr[k + i];
			}
			while (j < d && m + j <= a.length) {
				sort[k + i + j++] = a.arr[m + j];
			}
		}
		a = s;
	}
}
// 输出数组中的每一个元素到屏幕上
void printArray(sortArr a) {
	for (int i = 1; i <= a.length; i++) {
		cout << a.arr[i] << " ";
	}
	cout << endl;
}
// 主函数
int main() {
	sortArr input, output;
	for (int length = 10; length <= 20; length += 5) {
		input.length = length;
		cout << "请输入" << length << "个数字来进行排序:" << endl;
		for (int i = 1; i <= length; i++) {	// 空出0位便于排序
			cin >> input.arr[i];
		}
		cout << "数据读入完毕，开始排序..." << endl;
		cout << endl << "希尔排序结果: ";
		output = input;
		shellSort(output);
		printArray(output);
		cout << endl << "快速排序结果: ";
		output = input;
		quickSort(output);
		printArray(output);
		cout << endl << "堆排序的结果: ";
		output = input;
		heapSort(output);
		printArray(output);
		cout << endl << "归并排序结果: ";
		output = input;
		mergeSort(output);
		printArray(output);
		cout << endl;
	}
}
