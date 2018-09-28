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
		cout << "欢迎使用学生成绩分析系统:-)" << endl;
		cout << "让我们输入1开始吧！请输入1继续。。。" << endl;
		while(inputInteger(1) != 1);
		file = chooseExam();
		chooseExcel(file);
	}
}

bool Exam::init()
{
	if (createDirectory("D://成绩录入"))
	{
		//std::cout << "成绩录入初始化成功, 此文件夹为D盘下的“成绩录入”。" << std::endl;
	}
	else
	{
		//std::cout << "成绩录入初始化失败" << std::endl;
		return false;
	}
	if (createDirectory("D://成绩分析"))
	{
		//std::cout << "成绩分析初始化成功，此文件夹为D盘下的“成绩分析”。" << std::endl;
	}
	else
	{
		//std::cout << "成绩分析初始化失败" << std::endl;
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
Description: 判断一个字符串是否可以被转化为数字
Calls: getExcel1
Table Accessed: null
Table Updated: null
Input: 简单的字符串
Output: null
Return: true代表字符串可以转化为数字，false则不能
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