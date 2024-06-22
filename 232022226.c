#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <stdio.h>
#include <conio.h>		
#include <stdlib.h>		
#include <string.h>		
#include <stdbool.h>
enum Option
{
	EXIT,
	INPUT,
	SHOW,
	COUNT,
	FIND,
	CHANGE,
	DELETE,
	AVERAGE,
	GETPI,
	GETMAXANDMIN,
};

typedef struct tagStudent {
	char szName[20];
	char szSex[4];
	int  nAge;
	int  nStuNo;
	int  nScore;
}Student;


typedef struct tagNode
{
	Student stu;			//学生信息
	struct tagNode* pNext;	//指向下一个节点
}Node;

//创建头节点
Node* g_pHead = NULL;		//指向头节点


//菜单
void Menu();
//保存学生信息
void SaveStudent();
//从文件读取学生信息
void ReadStudent();
//1.录入学生信息
void InputStudent();
//2.显示学生信息
void ShowStudent();
//3.统计所有学生人数
void CountStudent();
//4.查找学生信息
void FindStudent();
//5.修改学生信息
void ChangeStudent();
//6.删除学生信息
void DeleteStudent();
//7.求平均分
void GetAverage();
//8.查看及格信息
void GetPassInformation();
//9.查看最值
void GetMaxAndMin();




int main() {
	while (1)
	{
		Menu();
		int n = 0;
		printf("请输入指令:> ");
		//先从文件读取学生信息，再进行操作
		ReadStudent();

		scanf("%d", &n);
		switch (n)
		{
		case INPUT://1.录入学生信息
			InputStudent();
			break;
		case SHOW://2.显示学生信息
			ShowStudent();
			break;
		case COUNT://3.统计所有学生人数
			CountStudent();
			break;
		case FIND://4.查找学生信息
			FindStudent();
			break;
		case CHANGE://5.修改学生信息
			ChangeStudent();
			break;
		case DELETE://6.删除学生信息
			DeleteStudent();
			break;
		case AVERAGE://7.求平均分
			GetAverage();
			break;
		case GETPI://8.查看及格信息
			GetPassInformation();
			break;
		case GETMAXANDMIN://9.查看最值
			GetMaxAndMin();
			break;
		case EXIT://0.退出系统
			return 0;
			break;
		default:
			printf("输入有误，没有该功能\n\n");
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}

//菜单
void Menu() {
	printf("*************************************************\n");
	printf("*\t欢迎使用高校学生成绩管理系统V3.0\t*\n");
	printf("*\t\t  请选择功能\t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.录入学生信息\t\t\t*\n");
	printf("*\t\t2.显示学生信息\t\t\t*\n");
	printf("*\t\t3.统计所有学生人数\t\t*\n");
	printf("*\t\t4.查找学生信息\t\t\t*\n");
	printf("*\t\t5.修改学生信息\t\t\t*\n");
	printf("*\t\t6.删除学生信息\t\t\t*\n");
	printf("*\t\t7.求平均分    \t\t\t*\n");
	printf("*\t\t8.查看及格信息\t\t\t*\n");
	printf("*\t\t9.查看最值\t\t\t*\n");
	printf("*\t\t0.退出系统\t\t\t*\n");
	printf("*************************************************\n");
}

//保存学生信息
void SaveStudent() {
	//打开文件
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "w+");

	if (pFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}

	//写入数据
	Node* p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
			p->stu.nStuNo,
			p->stu.szName,
			p->stu.szSex,
			p->stu.nAge,
			p->stu.nScore);
		p = p->pNext;
	}
	//关闭文件
	fclose(pFile);
}

//从文件读取学生信息
void ReadStudent() {
	//打开文件
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "r");

	if (pFile == NULL) {
		//文件打开失败，文件不存在，新建文件
		pFile = fopen(".\\stuinfo.dat", "w");
		fclose(pFile);
		pFile = fopen(".\\stuinfo.dat", "r");
	}

	//创建一个人，在堆中分配内存
	Node* p = (Node*)malloc(sizeof(Node));
	p->pNext = NULL;
	//重新建立链表
	g_pHead = p;

	//逐个单词读入文本内容
	char str[200];
	int i = 0;
	while (fscanf(pFile, "%s", str) != EOF) {  //读文件，将内容输入到char数组str 
		//单词不是*或者空时，进行赋值
		if (strcmp(str, "*") && str != NULL) {
			switch (i)
			{
			case 0:
				p->stu.nStuNo = atoi(str);//atoi将字符串转换为整数
				break;
			case 1:
				strcpy(p->stu.szName, str);
				break;
			case 2:
				strcpy(p->stu.szSex, str);
				break;
			case 3:
				p->stu.nAge = atoi(str);
				break;
			case 4:
				p->stu.nScore = atoi(str);
				break;
			default:
				Node* pNewNode = (Node*)malloc(sizeof(Node));
				pNewNode->pNext = NULL;
				p->pNext = pNewNode;
				p = pNewNode;
				p->stu.nStuNo = atoi(str);
				i = 0;
				break;
			}
			i++;
		}
	}
}

//1.录入学生信息
void InputStudent() {
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	//指针下一个指向空
	pNewNode->pNext = NULL;

	//查找链表的尾结点
	Node* p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//把节点插到链表的尾节点
	if (g_pHead == NULL) {
		g_pHead = pNewNode;
	}
	//链表不为空
	else {
		p->pNext = pNewNode;
	}

	//录入学生信息
	printf("请输入学生姓名：\n");
	scanf_s("%s", pNewNode->stu.szName, sizeof(pNewNode->stu.szName));
	printf("请输入性别：\n");
	scanf_s("%s", pNewNode->stu.szSex, sizeof(pNewNode->stu.szSex));
	printf("请输入学生年龄：\n");
	scanf_s("%d", &pNewNode->stu.nAge);
	printf("请输入学号：\n");
	scanf_s("%d", &pNewNode->stu.nStuNo);
	printf("请输入成绩：\n");
	scanf_s("%d", &pNewNode->stu.nScore);

	printf("学生信息录入成功。\n\n");
	SaveStudent();
	system("pause");
	system("cls");
}

//2.显示学生信息
void ShowStudent() {

	system("cls");
	//遍历链表
	Node* p = g_pHead;
	if (p == NULL) {
		printf("系统中暂无学生信息，请录入后再来打印查看。\n\n");
	}
	else {
		printf("*****************************************************************************************\n");
		printf("*\t\t\t\t欢迎使用高校学生成绩管理系统V3.0\t\t\t*\n");
		printf("*****************************************************************************************\n");
		printf("*\t学号\t\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
		printf("*****************************************************************************************\n");

		while (p != NULL)
		{
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);

			//下一个节点
			p = p->pNext;
			printf("*****************************************************************************************\n");
		}
	}

	system("pause");
	system("cls");
}



//3.统计所有学生人数
void CountStudent() {
	int countStu = 0;

	//遍历链表
	Node* p = g_pHead;
	while (p != NULL)
	{
		countStu++;
		p = p->pNext;
	}
	printf("学生总人数：%d\n\n", countStu);

	system("pause");
	system("cls");
}

//4.查找学生信息
void FindStudent() {
	system("cls");
	int stuNum;
	printf("请输入查找学生学号：");
	scanf("%d", &stuNum);
	Node* p = g_pHead;
	//表头进行展示一次
	bool isShowHead = false;
	//记录是否有找到该学号的学生信息
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*****************************************************************************************\n");
				printf("*\t学号\t\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*****************************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);
			isFindStu = true;
			printf("*****************************************************************************************\n");
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息。\n\n");
	}

	system("pause");
	system("cls");
}

//5.修改学生信息
void ChangeStudent() {
	//以学号为查找示例，其他信息查找流程基本相似
	int stuNum;
	printf("请输入欲修改学生的学号：");
	scanf("%d", &stuNum);
	//遍历链表查找，查找到后进行信息显示
	Node* p = g_pHead;
	//对表头进行展示一次
	bool isShowHead = false;
	//记录是否有找到该学号的学生信息
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*****************************************************************************************\n");
				printf("*\t学号\t\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*****************************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);
			printf("*****************************************************************************************\n");
			//修改学生信息
			printf("请输入学生姓名：\n");
			scanf_s("%s", p->stu.szName, sizeof(p->stu.szName));   
			printf("请输入性别：\n");
			scanf_s("%s", p->stu.szSex, sizeof(p->stu.szSex));
			printf("请输入学生年龄：\n");
			scanf_s("%d", &p->stu.nAge);
			printf("请输入学号：\n");
			scanf_s("%d", &p->stu.nStuNo);
			printf("请输入成绩：\n");
			scanf_s("%d", &p->stu.nScore);
			isFindStu = true;
			printf("\n修改成功！\n");
			//保存
			SaveStudent();
			//重新读文件，加载最新内容
			ReadStudent();
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息，无法进行修改。\n\n");
	}
	system("pause");
	system("cls");
}

//6.删除学生信息
void DeleteStudent() {
	system("cls");
	int stuNum;
	printf("请输入删除学生的学号：");
	scanf("%d", &stuNum);
	//遍历链表查找，查找到后进行信息显示
	Node* p = g_pHead;
	//记录前一个节点，删除时方便操作
	Node* beforeNode = g_pHead;
	//Node* tmp = NULL;
	
	//记录是否有找到该学号的学生信息
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);
			isFindStu = true;
			
			//删除节点为头节点
			if (p == g_pHead) {
				g_pHead = p->pNext;
			}
			//删除节点为尾节点
			else if (p->pNext == NULL) {
				Node* tmp = p;
				p = beforeNode;
				beforeNode->pNext = NULL;
				free(tmp);
			}
			//删除节点为中间节点
			else {
				beforeNode->pNext = p->pNext;
			}
		}
		beforeNode = p;
		p = p->pNext;
		//保存
		SaveStudent();
	}
	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息，无法进行删除操作。\n\n");
	}
	

	//写入文件
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "w+");

	if (pFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}

	//写入数据
	p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
			p->stu.nStuNo,
			p->stu.szName,
			p->stu.szSex,
			p->stu.nAge,
			p->stu.nScore);
		p = p->pNext;
	}
	//关闭文件
	fclose(pFile);
	printf("\n删除成功!!!\n");
	system("pause");
	system("cls");
}

//7.求平均分

void GetAverage()
{
	int sum = 0;
	int countStu = 0;
	//遍历链表
	Node* p = g_pHead;
	while (p != NULL)
	{
		sum += p->stu.nScore;
		countStu++;
		p = p->pNext;
	}
	printf("平均分：%.2lf\n\n", (sum*1.0) / countStu);

	system("pause");
	system("cls");
}

//8.查看及格信息
void GetPassInformation()
{
	int passStu = 0;
	int countStu = 0;
	Node* p = g_pHead;
	while (p != NULL)
	{
		countStu++;
		if (p->stu.nScore >= 60)
		{
			passStu++;
		}
		p = p->pNext;
	}
	printf("总人数：%d\n及格人数：%d\n及格率：%0.2lf%%\n\n", countStu, passStu, (passStu * 1.0) / countStu * 100);

	system("pause");
	system("cls");

}

//9.查看最值
void GetMaxAndMin()
{
	int max = 0;
	int min = 100;
	Node* p = g_pHead;
	while (p != NULL)
	{
		if (p->stu.nScore > max)
		{
			max = p->stu.nScore;
		}
		if (p->stu.nScore < min)
		{
			min = p->stu.nScore;
		}
		p = p->pNext;
	}
	printf("最高分：%d\n", max);
	printf("最低分：%d\n", min);
	system("pause");
	system("cls");
}