// Exam1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "exam.h"

#define APP_VERSION 1.1

int main()
{
	cout << "���Գɼ�����ϵͳ��" << APP_VERSION << endl;
	
	Exam* exam = new Exam();
	exam->getExam();

	system("pause");
	return 0;
}

