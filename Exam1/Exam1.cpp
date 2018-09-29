// Exam1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "exam.h"

#define APP_VERSION 1.1

int main()
{
	cout << "考试成绩分析系统：" << APP_VERSION << endl;
	
	Exam* exam = new Exam();
	exam->getExam();

	system("pause");
	return 0;
}

