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
	Student stu;			//ѧ����Ϣ
	struct tagNode* pNext;	//ָ����һ���ڵ�
}Node;

//����ͷ�ڵ�
Node* g_pHead = NULL;		//ָ��ͷ�ڵ�


//�˵�
void Menu();
//����ѧ����Ϣ
void SaveStudent();
//���ļ���ȡѧ����Ϣ
void ReadStudent();
//1.¼��ѧ����Ϣ
void InputStudent();
//2.��ʾѧ����Ϣ
void ShowStudent();
//3.ͳ������ѧ������
void CountStudent();
//4.����ѧ����Ϣ
void FindStudent();
//5.�޸�ѧ����Ϣ
void ChangeStudent();
//6.ɾ��ѧ����Ϣ
void DeleteStudent();
//7.��ƽ����
void GetAverage();
//8.�鿴������Ϣ
void GetPassInformation();
//9.�鿴��ֵ
void GetMaxAndMin();




int main() {
	while (1)
	{
		Menu();
		int n = 0;
		printf("������ָ��:> ");
		//�ȴ��ļ���ȡѧ����Ϣ���ٽ��в���
		ReadStudent();

		scanf("%d", &n);
		switch (n)
		{
		case INPUT://1.¼��ѧ����Ϣ
			InputStudent();
			break;
		case SHOW://2.��ʾѧ����Ϣ
			ShowStudent();
			break;
		case COUNT://3.ͳ������ѧ������
			CountStudent();
			break;
		case FIND://4.����ѧ����Ϣ
			FindStudent();
			break;
		case CHANGE://5.�޸�ѧ����Ϣ
			ChangeStudent();
			break;
		case DELETE://6.ɾ��ѧ����Ϣ
			DeleteStudent();
			break;
		case AVERAGE://7.��ƽ����
			GetAverage();
			break;
		case GETPI://8.�鿴������Ϣ
			GetPassInformation();
			break;
		case GETMAXANDMIN://9.�鿴��ֵ
			GetMaxAndMin();
			break;
		case EXIT://0.�˳�ϵͳ
			return 0;
			break;
		default:
			printf("��������û�иù���\n\n");
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}

//�˵�
void Menu() {
	printf("*************************************************\n");
	printf("*\t��ӭʹ�ø�Уѧ���ɼ�����ϵͳV3.0\t*\n");
	printf("*\t\t  ��ѡ����\t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.¼��ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t2.��ʾѧ����Ϣ\t\t\t*\n");
	printf("*\t\t3.ͳ������ѧ������\t\t*\n");
	printf("*\t\t4.����ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t5.�޸�ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t6.ɾ��ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t7.��ƽ����    \t\t\t*\n");
	printf("*\t\t8.�鿴������Ϣ\t\t\t*\n");
	printf("*\t\t9.�鿴��ֵ\t\t\t*\n");
	printf("*\t\t0.�˳�ϵͳ\t\t\t*\n");
	printf("*************************************************\n");
}

//����ѧ����Ϣ
void SaveStudent() {
	//���ļ�
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "w+");

	if (pFile == NULL) {
		printf("���ļ�ʧ�ܡ�\n");
		return;
	}

	//д������
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
	//�ر��ļ�
	fclose(pFile);
}

//���ļ���ȡѧ����Ϣ
void ReadStudent() {
	//���ļ�
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "r");

	if (pFile == NULL) {
		//�ļ���ʧ�ܣ��ļ������ڣ��½��ļ�
		pFile = fopen(".\\stuinfo.dat", "w");
		fclose(pFile);
		pFile = fopen(".\\stuinfo.dat", "r");
	}

	//����һ���ˣ��ڶ��з����ڴ�
	Node* p = (Node*)malloc(sizeof(Node));
	p->pNext = NULL;
	//���½�������
	g_pHead = p;

	//������ʶ����ı�����
	char str[200];
	int i = 0;
	while (fscanf(pFile, "%s", str) != EOF) {  //���ļ������������뵽char����str 
		//���ʲ���*���߿�ʱ�����и�ֵ
		if (strcmp(str, "*") && str != NULL) {
			switch (i)
			{
			case 0:
				p->stu.nStuNo = atoi(str);//atoi���ַ���ת��Ϊ����
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

//1.¼��ѧ����Ϣ
void InputStudent() {
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	//ָ����һ��ָ���
	pNewNode->pNext = NULL;

	//���������β���
	Node* p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//�ѽڵ�嵽�����β�ڵ�
	if (g_pHead == NULL) {
		g_pHead = pNewNode;
	}
	//����Ϊ��
	else {
		p->pNext = pNewNode;
	}

	//¼��ѧ����Ϣ
	printf("������ѧ��������\n");
	scanf_s("%s", pNewNode->stu.szName, sizeof(pNewNode->stu.szName));
	printf("�������Ա�\n");
	scanf_s("%s", pNewNode->stu.szSex, sizeof(pNewNode->stu.szSex));
	printf("������ѧ�����䣺\n");
	scanf_s("%d", &pNewNode->stu.nAge);
	printf("������ѧ�ţ�\n");
	scanf_s("%d", &pNewNode->stu.nStuNo);
	printf("������ɼ���\n");
	scanf_s("%d", &pNewNode->stu.nScore);

	printf("ѧ����Ϣ¼��ɹ���\n\n");
	SaveStudent();
	system("pause");
	system("cls");
}

//2.��ʾѧ����Ϣ
void ShowStudent() {

	system("cls");
	//��������
	Node* p = g_pHead;
	if (p == NULL) {
		printf("ϵͳ������ѧ����Ϣ����¼���������ӡ�鿴��\n\n");
	}
	else {
		printf("*****************************************************************************************\n");
		printf("*\t\t\t\t��ӭʹ�ø�Уѧ���ɼ�����ϵͳV3.0\t\t\t*\n");
		printf("*****************************************************************************************\n");
		printf("*\tѧ��\t\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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

			//��һ���ڵ�
			p = p->pNext;
			printf("*****************************************************************************************\n");
		}
	}

	system("pause");
	system("cls");
}



//3.ͳ������ѧ������
void CountStudent() {
	int countStu = 0;

	//��������
	Node* p = g_pHead;
	while (p != NULL)
	{
		countStu++;
		p = p->pNext;
	}
	printf("ѧ����������%d\n\n", countStu);

	system("pause");
	system("cls");
}

//4.����ѧ����Ϣ
void FindStudent() {
	system("cls");
	int stuNum;
	printf("���������ѧ��ѧ�ţ�");
	scanf("%d", &stuNum);
	Node* p = g_pHead;
	//��ͷ����չʾһ��
	bool isShowHead = false;
	//��¼�Ƿ����ҵ���ѧ�ŵ�ѧ����Ϣ
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*****************************************************************************************\n");
				printf("*\tѧ��\t\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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
		printf("ѧ����������ϵͳ�����޸�ѧ����Ϣ��\n\n");
	}

	system("pause");
	system("cls");
}

//5.�޸�ѧ����Ϣ
void ChangeStudent() {
	//��ѧ��Ϊ����ʾ����������Ϣ�������̻�������
	int stuNum;
	printf("���������޸�ѧ����ѧ�ţ�");
	scanf("%d", &stuNum);
	//����������ң����ҵ��������Ϣ��ʾ
	Node* p = g_pHead;
	//�Ա�ͷ����չʾһ��
	bool isShowHead = false;
	//��¼�Ƿ����ҵ���ѧ�ŵ�ѧ����Ϣ
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*****************************************************************************************\n");
				printf("*\tѧ��\t\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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
			//�޸�ѧ����Ϣ
			printf("������ѧ��������\n");
			scanf_s("%s", p->stu.szName, sizeof(p->stu.szName));   
			printf("�������Ա�\n");
			scanf_s("%s", p->stu.szSex, sizeof(p->stu.szSex));
			printf("������ѧ�����䣺\n");
			scanf_s("%d", &p->stu.nAge);
			printf("������ѧ�ţ�\n");
			scanf_s("%d", &p->stu.nStuNo);
			printf("������ɼ���\n");
			scanf_s("%d", &p->stu.nScore);
			isFindStu = true;
			printf("\n�޸ĳɹ���\n");
			//����
			SaveStudent();
			//���¶��ļ���������������
			ReadStudent();
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("ѧ����������ϵͳ�����޸�ѧ����Ϣ���޷������޸ġ�\n\n");
	}
	system("pause");
	system("cls");
}

//6.ɾ��ѧ����Ϣ
void DeleteStudent() {
	system("cls");
	int stuNum;
	printf("������ɾ��ѧ����ѧ�ţ�");
	scanf("%d", &stuNum);
	//����������ң����ҵ��������Ϣ��ʾ
	Node* p = g_pHead;
	//��¼ǰһ���ڵ㣬ɾ��ʱ�������
	Node* beforeNode = g_pHead;
	//Node* tmp = NULL;
	
	//��¼�Ƿ����ҵ���ѧ�ŵ�ѧ����Ϣ
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
			
			//ɾ���ڵ�Ϊͷ�ڵ�
			if (p == g_pHead) {
				g_pHead = p->pNext;
			}
			//ɾ���ڵ�Ϊβ�ڵ�
			else if (p->pNext == NULL) {
				Node* tmp = p;
				p = beforeNode;
				beforeNode->pNext = NULL;
				free(tmp);
			}
			//ɾ���ڵ�Ϊ�м�ڵ�
			else {
				beforeNode->pNext = p->pNext;
			}
		}
		beforeNode = p;
		p = p->pNext;
		//����
		SaveStudent();
	}
	if (!isFindStu) {
		printf("ѧ����������ϵͳ�����޸�ѧ����Ϣ���޷�����ɾ��������\n\n");
	}
	

	//д���ļ�
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "w+");

	if (pFile == NULL) {
		printf("���ļ�ʧ�ܡ�\n");
		return;
	}

	//д������
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
	//�ر��ļ�
	fclose(pFile);
	printf("\nɾ���ɹ�!!!\n");
	system("pause");
	system("cls");
}

//7.��ƽ����

void GetAverage()
{
	int sum = 0;
	int countStu = 0;
	//��������
	Node* p = g_pHead;
	while (p != NULL)
	{
		sum += p->stu.nScore;
		countStu++;
		p = p->pNext;
	}
	printf("ƽ���֣�%.2lf\n\n", (sum*1.0) / countStu);

	system("pause");
	system("cls");
}

//8.�鿴������Ϣ
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
	printf("��������%d\n����������%d\n�����ʣ�%0.2lf%%\n\n", countStu, passStu, (passStu * 1.0) / countStu * 100);

	system("pause");
	system("cls");

}

//9.�鿴��ֵ
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
	printf("��߷֣�%d\n", max);
	printf("��ͷ֣�%d\n", min);
	system("pause");
	system("cls");
}