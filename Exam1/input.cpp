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
		cout << "������" << begin << "��" << end << "������������" << begin << "��" << end << endl;
		cin >> s;
		i = atoi(s.c_str());
		if (i == 0)
		{
			cout << i << "�������������������룡" << endl;
		}
		else if (i < begin || i > end)
		{
			cout << i << "����" << begin << "��" << end << "֮�䣡���������룡" << endl;
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
		cout << "������" << begin << "��" << end << "����������С��������" << begin << "��" << end << endl;
		cin >> s;
		i = atof(s.c_str());
		if (i == 0)
		{
			cout << i << "�������������������룡" << endl;
		}
		else if (i < begin || i > end)
		{
			cout << i << "����" << begin << "��" << end << "֮�䣡���������룡" << endl;
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