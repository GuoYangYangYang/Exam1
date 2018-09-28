#include "stdafx.h"
#include "exam.h"

int Exam::inputInteger(int start)
{
	string s = "";
	int i = 0;
	cin >> s;
	i = atoi(s.c_str());
	return i;
}

int Exam::inputInteger(int begin, int end)
{
	string s = "";
	int i = 0;
	while (begin <= end)
	{
		cout << "请输入" << begin << "到" << end << "的整数，包括" << begin << "和" << end << endl;
		cin >> s;
		i = atoi(s.c_str());
		if (i == 0)
		{
			cout << i << "不是整数！请重新输入！" << endl;
		}
		else if (i < begin || i > end)
		{
			cout << i << "不在" << begin << "到" << end << "之间！请重新输入！" << endl;
		}
		else break;
	}
	return i;
}

float Exam::inputFloat(float begin, float end)
{
	string s = "";
	float i = 0;
	while (begin <= end)
	{
		cout << "请输入" << begin << "到" << end << "的整数或者小数，包括" << begin << "和" << end << endl;
		cin >> s;
		i = atof(s.c_str());
		if (i == 0)
		{
			cout << i << "不是整数！请重新输入！" << endl;
		}
		else if (i < begin || i > end)
		{
			cout << i << "不在" << begin << "到" << end << "之间！请重新输入！" << endl;
		}
		else break;
	}
	return i;
}

string Exam::inputString()
{
	string s = "";
	while (true)
	{
		cin >> s;
		if (s.compare(""))
			break;
	}
	return s;
}