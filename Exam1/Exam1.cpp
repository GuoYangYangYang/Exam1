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

	/*
	//�����ļ������ 
	ofstream oFile;

	//��Ҫ������ļ�
	oFile.open("E:\\scoresheet1.csv", ios::out | ios::trunc);    // �����ͺ����׵����һ����Ҫ��excel �ļ�
	oFile << "����" << "," << "����" << "," << "�༶" << "," << "������" << endl;
	oFile << "����" << "," << "22" << "," << "1" << "," << "JIM" << endl;
	oFile << "����" << "," << "23" << "," << "3" << "," << "TOM" << endl;

	oFile.close();
	

	
	//��Ҫ������ļ�
	ifstream iFile("E:\\14��Ƴɼ������.csv");
	string   readStr((std::istreambuf_iterator<char>(iFile)), std::istreambuf_iterator<char>());
	cout << readStr.c_str() << endl;
	cout << readStr.length() << endl; 
	
	
	const char * filename = (folder + "\\����ܳɼ�.csv").c_str();
	
	//char filename[] = "E:\\14��Ƴɼ������.CSV"; //�ļ���
	Csv csv(filename);//Ԫ����ʾ����
		for (auto it1 = 0; it1 != csv.table.size(); ++it1)
		{
			for (auto it2 = 0; it2 != csv.table[it1].size(); ++it2)
			{
				cout << setw(9) << setfill(' ') << csv.table[it1][it2];
			}
			cout << endl;
		}
	*/

	system("pause");
	return 0;
}

