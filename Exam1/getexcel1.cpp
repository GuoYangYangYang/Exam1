#include "stdafx.h"
#include "exam.h"

bool isNum(string str)
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

void getData(const char * excelName, Csv csv, string type, double fristBatch, double secondBatch)
{
	if (csv.table[0][6].compare("�ܷ�") == 0)
	{
		ofstream excel1;
		excel1.open(excelName, std::ios::out | std::ios::app);
		int i = 0;
		int student = 0;
		int fristStudent = 0;
		int secondStudent = 0;
		double fristBatchDouble = 0;
		double secondBatchDouble = 0;
		for (i = 1; ((isNum(csv.table[i][6]) && (csv.table[i][6].compare(""))); i++)
		{
			if (atoi(csv.table[student][6].c_str()) >= fristBatch) fristStudent++;
			if (atoi(csv.table[student][6].c_str()) >= secondBatch) secondStudent++;
		}

		fristBatchDouble = 100.0 * (fristStudent * 1.0) / (student * 1.0);
		secondBatchDouble = 100.0 * (secondStudent * 1.0) / (student * 1.0);

		excel1 << type << "," << student << "," << fristStudent << ",";
		excel1 << fixed << setprecision(2) << fristBatchDouble << "%,";
		excel1 << secondStudent << ",";
		excel1 << fixed << setprecision(2) << secondBatchDouble << "%" << endl;
		excel1.close();

	}
}

string getExcel1(string folderIntput, string folderOutput, string name, string gradeS)
{
	string excelName1 = folderOutput + "\\" + name + "���ģ���" + "��" + gradeS + "�꼶һ�������뱾������������.csv";
	const char * excelNamec1 = excelName1.c_str();
	
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	int scienceFirstBatch = 512;
	int scienceSecondBatch = 375;
	int artsFirstBatch = 561;
	int artsSecondBatch = 441;

	/*
	cout << "������һ���ߣ���ƣ�:";
	cin >> scienceFirstBatch;
	cout << "�����뱾���ߣ���ƣ�:";
	cin >> scienceSecondBatch;
	cout << "������һ���ߣ��Ŀƣ�:";
	cin >> artsFirstBatch;
	cout << "�����뱾���ߣ��Ŀƣ�:";
	cin >> artsSecondBatch;

	cout << "һ���ߣ���ƣ���" << scienceFirstBatch << endl;
	cout << "�����ߣ���ƣ���" << scienceSecondBatch << endl;
	cout << "һ���ߣ��Ŀƣ���" << artsFirstBatch << endl;
	cout << "�����ߣ��Ŀƣ���" << artsSecondBatch << endl;
*/

	remove(excelNamec1);
	ofstream excel1;
	excel1.open(excelNamec1, std::ios::out | std::ios::app);

	if (!excel1.is_open())
	{
		cout << "�����ļ�����" << endl;
		return "ERROR";
	}
	excel1 << "����,�ο�����,һ������,����,��������,����" << endl;

	excel1.close();
	cout << file1 << endl;

	
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	string type = "";
	type = "���";
	getData(excelNamec1, csv1, type, scienceFirstBatch, scienceSecondBatch);
	type = "�Ŀ�";
	getData(excelNamec1, csv2, type, artsFirstBatch, artsSecondBatch);
	type = "����";
	getData(excelNamec1, csv3, type, scienceFirstBatch, scienceSecondBatch);
	type = "����";
	getData(excelNamec1, csv4, type, artsFirstBatch, artsSecondBatch);

	return " ";
}