#include "stdafx.h" 
#include "exam.h"

Exam::Exam()
{

}

void Exam::getExam()
{
	string file = "";
	while (1)
	{
		if (init() == false) exit(0);
		clear();
		cout << "��ӭʹ��ѧ���ɼ�����ϵͳ:-)" << endl;
		cout << "����������1��ʼ�ɣ�������1����������" << endl;
		while(inputInteger(1) != 1);
		file = chooseExam();
		chooseExcel(file);
	}
}

bool Exam::init()
{
	if (createDirectory("D://�ɼ�¼��"))
	{
		//std::cout << "�ɼ�¼���ʼ���ɹ�, ���ļ���ΪD���µġ��ɼ�¼�롱��" << std::endl;
	}
	else
	{
		//std::cout << "�ɼ�¼���ʼ��ʧ��" << std::endl;
		return false;
	}
	if (createDirectory("D://�ɼ�����"))
	{
		//std::cout << "�ɼ�������ʼ���ɹ������ļ���ΪD���µġ��ɼ���������" << std::endl;
	}
	else
	{
		//std::cout << "�ɼ�������ʼ��ʧ��" << std::endl;
		return false;
	}
	return true;
}

void Exam::clear()
{
	system("cls");
}

/********************************************************************************
Function: isNum
Description: �ж�һ���ַ����Ƿ���Ա�ת��Ϊ����
Calls: getExcel1
Table Accessed: null
Table Updated: null
Input: �򵥵��ַ���
Output: null
Return: true�����ַ�������ת��Ϊ���֣�false����
Others: null
********************************************************************************/
bool Exam::isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
}