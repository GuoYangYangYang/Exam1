// Exam1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <fstream> 
#include <string>
#include <iostream>
#include <streambuf> 
using namespace std;

int main()
{
	//�����ļ������ 
	ofstream oFile;

	oFile.open("Hello.txt", ios::in | ios::out);

	/*
	//��Ҫ������ļ� 
	oFile.open("E:\\scoresheet1.txt", ios::out | ios::trunc);    // �����ͺ����׵����һ����Ҫ��excel �ļ�
	oFile << "����" << "," << "����" << "," << "�༶" << "," << "������" << endl;
	oFile << "����" << "," << "22" << "," << "1" << "," << "JIM" << endl;
	oFile << "����" << "," << "23" << "," << "3" << "," << "TOM" << endl;

	oFile.close();
	*/

	/*
	//��Ҫ������ļ� 
	ifstream iFile("E:\\scoresheet.csv");
	string   readStr((std::istreambuf_iterator<char>(iFile)), std::istreambuf_iterator<char>());
	cout << readStr.c_str();
	*/

	system("pause");
	return 0;
}
