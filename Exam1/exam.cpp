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
		clear();
		if (init() == false) exit(0);
		cout << "��ӭʹ��ѧ���ɼ�����ϵͳ:-)" << endl;
		cout << "ע�����" << endl;
		cout << "1. ѧ����Ϣ���ݵ����벻�ڱ�ϵͳ�������д򿪸��ļ�ͬĿ¼�µġ��������롱�ļ��У�" << endl << "1. �ҵ��ļ��򿪺���ӱ����ɺ��뱣�棬ÿ������һ�����ֲ�׼�ı䣡����" << endl;
		cout << "2. ѧ����Ϣ�������������ͬĿ¼�µġ����ݷ������ļ��У��ҵ���Ӧ���ļ���" << endl << "2. �����ٴ����ɣ�һ��Ҫ�ر��Ѵ򿪵�Excel����ļ�������" << endl;
		cout << "����������1��ʼ�ɣ�������1����������" << endl;
		while(inputInteger(1) != 1);
		file = chooseExam();
		chooseExcel(file);
	}
}

bool Exam::init()
{
	_getcwd(root, 1000);
	rootS = root;
	if (createDirectory(rootS + "\\�ɼ�¼��"))
	{
		//std::cout << "�ɼ�¼���ʼ���ɹ�, ���ļ���ΪD���µġ��ɼ�¼�롱��" << std::endl;
	}
	else
	{
		//std::cout << "�ɼ�¼���ʼ��ʧ��" << std::endl;
		return false;
	}
	if (createDirectory(rootS + "\\�ɼ�����"))
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