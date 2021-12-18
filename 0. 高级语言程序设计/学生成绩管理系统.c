#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>

#define MAX_STUDENT_NUM 30
#define MAX_SUBJECT_NUM 6
#define MAX_INFO_LENGTH 10
// 学生结构体
typedef struct student {
	char name[MAX_INFO_LENGTH], id[MAX_INFO_LENGTH];	// 姓名及学号
	int score[MAX_SUBJECT_NUM];	// 各科成绩
	int sum;	// 总分
}student, * stuNode;
// 代表一次测验的结构体
typedef struct test {
	int stuNum, subNum;	// 参加此次考试的学生人数和此次考试的科目数量
	char subName[MAX_SUBJECT_NUM][MAX_INFO_LENGTH];	// 课程名称表
	student stu[MAX_STUDENT_NUM];	// 学生表
}test, * te;
// 记录学生总分
void getSum(test* a) {
	for (int i = 0; i < a->stuNum; i++) {
		int sum = 0;
		for (int j = 0; j < a->subNum; j++) {
			sum += a->stu[i].score[j];
		}
		a->stu[i].sum = sum;
	}
}
// 学生总分降序排序规则
int downScore(student a, student b) {
	return a.sum - b.sum;
}
// 学生总分升序排序规则
int upScore(student a, student b) {
	return b.sum - a.sum;
}
// 学号从小到大排序规则
int upID(student a, student b) {
	return strcmp(b.id, a.id);
}
// 姓名字典顺序排序规则
int upName(student a, student b) {
	return strcmp(b.name, a.name);
}
// 对一次测验中的学生进行排序
// 传入cmp函数指针，按照cmp返回值大于0的在前
void sortStu(test* a, int(*cmp)(student, student)) {
	for (int i = 0; i < a->stuNum - 1; i++) {
		int maxi = i;
		for (int j = i + 1; j < a->stuNum; j++) {
			if (cmp(a->stu[j], a->stu[maxi]) > 0) {
				maxi = j;
			}
		}
		student t = a->stu[maxi];
		a->stu[maxi] = a->stu[i];
		a->stu[i] = t;
	}
}
// 输出某个学生的全部成绩 i是学生在数组中的编号
void printStuSco(test a, int i) {
	for (int j = 0; j < a.subNum; j++) {
		printf(" %4d", a.stu[i].score[j]);
	}
}
// 排序并输出学生成绩表
// mode为1表示输出总分，mode为0表示输出各科成绩
void printSorted(test sort, int(*cmp)(student, student)) {
	sortStu(&sort, cmp);
	for (int i = 0; i < sort.stuNum; i++) {
		printf("%s %s", sort.stu[i].id, sort.stu[i].name);	// 输出姓名学号
		printStuSco(sort, i);	// 输出各科成绩
		printf(" %5d\n", sort.stu[i].sum);	// 输出总分
	}
}
// 读入数据，成功则返回1
int readData(test* a) {
	printf("请输入学生数量: ");
	scanf("%d", &a->stuNum);
	printf("请输入科目数量: ");
	scanf("%d", &a->subNum);
	printf("请依次输入科目名称: ");
	for (int i = 0; i < a->subNum; i++) {
		printf("科目%d: ", i + 1);
		scanf("%s", &a->subName[i]);
		getchar();	// 去掉换行符
	}
	printf("请按照如下格式输入信息:\n");
	printf("学号-姓名-科目1成绩-科目2成绩...\n");
	for (int i = 0; i < a->stuNum; i++) {
		scanf("%s %s", &a->stu[i].id, &a->stu[i].name);
		for (int j = 0; j < a->subNum; j++) {
			scanf(" %d", &a->stu[i].score[j]);
		}
		getchar();	// 去掉换行符
	}
	printf("[+] 数据读入完毕\n");
	return 1;
}

// 主函数
int main() {
	char fileName[] = "source.txt";
	test a;	// 创建一次考试
	int tag = 1, isInitialed = 0;	// 控制菜单循环
	printf("1.Input record\n");
	printf("2.Calculate total and average score of every course\n");
	printf("3.Calculate total and average score of every student\n");
	printf("4.Sort in descending order by total score of every student\n");
	printf("5.Sort in ascending order by total score of every student\n");
	printf("6.Sort in ascending order by number\n");
	printf("7.Sort in dictionary order by name\n");
	printf("8.Search by number\n");
	printf("9.Search by name\n");
	printf("10.Statistic analysis for every course\n");
	printf("11.List record\n");
	printf("12.Write to a file\n");
	printf("13.Read from a file\n");
	printf("0.Exit\n");
	while (tag) {
		printf("Please enter your choice: ");
		int ope;
		scanf("%d", &ope);
		getchar();	// 去除换行符
		if (ope > 13 || ope < 0) {
			printf("菜单代码输入错误，请输入0-13的代码");
			continue;
		}
		else if (!isInitialed && ope > 1 && ope < 13) {
			printf("您需要先输入或者从文件读入数据才能进行此操作!\n");
			continue;
		}
		switch (ope) {
		case 0: {
			tag = 0;
			printf("感谢使用本系统，再见！");
			break;
		}
		case 1: {
			if (readData(&a)) {
				isInitialed = 1;
			}
			getSum(&a);
			break;
		}
		case 2: {	// 计算课程平均分和总分
			int sum = 0;
			for (int i = 0; i < a.subNum; i++) {
				for (int j = 0; j < a.stuNum; j++) {
					sum += a.stu[j].score[i];
				}
				printf("科目 %s 总分为: %1d, 平均分为: %4.2f\n", a.subName[i], sum, sum / (double)a.stuNum);
				sum = 0;
			}
			break;
		}
		case 3: {	// 计算学生总分和平均分
			int sum = 0;
			for (int i = 0; i < a.stuNum; i++) {
				for (int j = 0; j < a.subNum; j++) {
					sum += a.stu[i].score[j];
				}
				printf("%s %s总分为: %4d, 平均分为: %4.2f\n", a.stu[i].id, a.stu[i].name, sum, sum / (double)a.subNum);
				sum = 0;
			}
			break;
		}
		case 4: {	// 降序输出学生总分名次表
			printf("学生总分名次表（降序）\n");
			printSorted(a, downScore);
			break;
		}
		case 5: {	// 升序输出学生总分名次表
			printf("学生总分名次表（升序）\n");
			printSorted(a, upScore);
			break;
		}
		case 6: {	// 按学号由小到大
			printf("学生成绩表（按学号由小到大）\n");
			printSorted(a, upID);
			break;
		}
		case 7: {	// 按姓名字典顺序
			printf("学生成绩表（按姓名字典顺序）\n");
			printSorted(a, upName);
			break;
		}
		case 8: {	// 按学号查询学生排名及考试成绩
			char desID[MAX_INFO_LENGTH];
			int i;
			printf("请输入要查询的学生的学号: ");
			gets(desID);
			for (i = 0; i < a.stuNum; i++) {
				if (!strcmp(a.stu[i].id, desID)) {
					printf("%s %s", a.stu[i].id, a.stu[i].name);
					printStuSco(a, i);
					break;
				}
			}
			if (i == a.stuNum) {
				printf("未查询到该学生");
			}
			break;
		}
		case 9: {	// 按姓名查询学生排名及考试成绩
			char desName[MAX_INFO_LENGTH];
			int i;
			printf("请输入要查询的学生的姓名: ");
			gets(desName);
			for (i = 0; i < a.stuNum; i++) {
				if (!strcmp(a.stu[i].name, desName)) {
					printf("%s %s", a.stu[i].id, a.stu[i].name);
					printStuSco(a, i);
					break;
				}
			}
			if (i == a.stuNum) {
				printf("未查询到该学生");
			}
			break;
		}
		case 10: {	// 数据分析
			// 计算每门课程的不同等级百分比
			char name[MAX_SUBJECT_NUM][MAX_INFO_LENGTH] = { "优秀","良好","中等","及格","挂科" };	// 记录不同等级对应的下标
			for (int i = 0; i < a.subNum; i++) {
				printf("科目: %s\n", a.subName[i]);
				int result[5] = { 0 };	// 用于记录不同等级的人数
				for (int j = 0; j < a.stuNum; j++) {
					switch (a.stu[j].score[i] / 10) {
					case 10:
					case 9:
						result[0]++;	// 优秀
						break;
					case 8:
						result[1]++;	// 良好
						break;
					case 7:
						result[2]++;	// 中等
						break;
					case 6:
						result[3]++;	// 及格
						break;
					default:
						result[4]++;	// 不及格
						break;
					}
				}
				for (int k = 0; k < 5; k++) {
					printf("%s人数: %3d, 占比: %4.2f%%\n", name[k], result[k], result[k] / (double)a.stuNum * 100);
				}
				printf("\n");
			}
			break;
		}
		case 11: {	// 输出学生学号、姓名、各科成绩，每门课程的总分和平均分
			for (int i = 0; i < a.stuNum; i++) {
				printf("%s %s ", a.stu[i].id, a.stu[i].name);
				printStuSco(a, i);
				printf("\n");
			}
			// 计算课程总分和平均分
			printf("\n科目信息:\n");
			for (int i = 0; i < a.subNum; i++) {
				int sum = 0;
				for (int j = 0; j < a.stuNum; j++) {
					sum += a.stu[j].score[i];
				}
				printf("%8s 总分:%4d 平均分:%4.2f\n", a.subName[i], sum, sum / (double)a.stuNum);
			}
			break;
		}
		case 12: {	// 将学生的记录信息写入文件
			FILE* file = fopen(fileName, "r+");
			if (isInitialed == 0) {
				printf("[!] 需要先读入成绩信息才能进行后续操作，请先输入1\n");
				break;
			}
			fprintf(file, "student num: %d, subject num: %d;\n", a.stuNum, a.subNum);
			for (int i = 0; i < a.subNum; i++) {
				fprintf(file, "%s ", a.subName[i]);
			}
			fprintf(file, "\n");
			for (int i = 0; i < a.stuNum; i++) {
				fprintf(file, "%s %s", a.stu[i].id, a.stu[i].name);
				for (int j = 0; j < a.subNum; j++) {
					fprintf(file, " %d", a.stu[i].score[j]);
				}
				fprintf(file, "\n");
			}
			fclose(file);
			break;
		}
		case 13: {	// 从文件中读取学生的记录信息并显示
			FILE* file = fopen(fileName, "r");
			char p = 'y';	// 默认yes
			if (isInitialed == 1) {
				printf("该操作将会覆盖当前考试信息，是否继续？(y/n) ");
				p = getchar();
				getchar();	// 去掉换行符
			}
			if (p == 'y') {
				fscanf(file, "student num: %d, subject num: %d;", &a.stuNum, &a.subNum);
				if (a.stuNum > 0 && a.stuNum < MAX_STUDENT_NUM && a.subNum>0 && a.subNum < MAX_SUBJECT_NUM) {
					for (int i = 0; i < a.subNum; i++) {
						fscanf(file, "%s", &a.subName[i]);
					}
					for (int i = 0; i < a.stuNum; i++) {
						fscanf(file, "%s %s", &a.stu[i].id, &a.stu[i].name);
						for (int j = 0; j < a.subNum; j++) {
							fscanf(file, " %d", &a.stu[i].score[j]);
						}
					}
					isInitialed = 1;
					getSum(&a);
					printf("成功读入数据！\n");
				}
				else {
					printf("[!] 文件中不包含可用信息\n");
				}
			}
			fclose(file);
			break;
		}
		}
		printf("\n");
	}
	return 0;
}
