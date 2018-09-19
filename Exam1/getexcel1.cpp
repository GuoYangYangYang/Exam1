#include "stdafx.h"
#include "exam.h"
/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-19
Description: ��һ��XXXX��X�꼶���ģ���һ�������뱾������������
********************************************************************************/

/********************************************************************************
********************************************************************************/

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

/********************************************************************************
Function: getData
Description: ͳ��һ��csv���С��ܷ֡���һ�е�һ�����ͱ�����
Calls: getExcel1
Table Accessed: XXXX��X�꼶���ģ���һ�������뱾������������
Table Updated: XXXX��X�꼶���ģ���һ�������뱾������������
Input:
		1. const char * excelName: ���ݷ�����ľ��Ե�ַ
		2. Csv csv: �Ѿ�����õ�Csv�����ں�ԭʼ���ݱ�table
		3. string type: �˴η������ݵ����ͣ���Ҫ�У���ƣ��Ŀƣ��������� 
		4. double fristBatch: һ���߷���
		5. double secondBatch: �����߷���
Output: ��ָ��csv�ļ�����һ�з�������
Return: null
Others: null
********************************************************************************/
void getData(const char * excelName, Csv csv, string type, double fristBatch, double secondBatch)
{
	if (csv.table[0][6].compare("�ܷ�") == 0)
	{
		ofstream excel1;
		excel1.open(excelName, std::ios::out | std::ios::app);
		int i = 1;
		int score = -1;
		int student = 0;
		int fristStudent = 0;
		int secondStudent = 0;
		double fristBatchDouble = 0;
		double secondBatchDouble = 0;
		if (!csv.table.empty())
		{
			cout << isNum(csv.table[i][6]) << csv.table[i][6].compare("") << endl;
			for (i = 1; (isNum(csv.table[i][6])); i++)
			{
				score = atoi(csv.table[i][6].c_str());
				if (score >= fristBatch) fristStudent++;
				if (score >= secondBatch) secondStudent++;
				if (score >= 0) student++;
				score = -1;
			}
			if (student != 0)
			{
				fristBatchDouble = 100.0 * (fristStudent * 1.0) / (student * 1.0);
				secondBatchDouble = 100.0 * (secondStudent * 1.0) / (student * 1.0);
			}
			else
			{
				fristBatchDouble = secondBatchDouble = 0;
			}
		}
		
		excel1 << type << "," << student << "," << fristStudent << ",";
		excel1 << fixed << setprecision(2) << fristBatchDouble << "%,";
		excel1 << secondStudent << ",";
		excel1 << fixed << setprecision(2) << secondBatchDouble << "%" << endl;

		excel1.close();
	}
}

/********************************************************************************
Function: getExcel1
Description: ����ָ����ԭʼ���ݱ����ɷ�����XXXX��X�꼶���ģ���һ�������뱾������������
Calls: chooseExcel
Table Accessed: 
		1. ����ܳɼ�.csv
		2. �Ŀ��ܳɼ�.csv
		3. �����ܳɼ�.csv
		4. �����ܳɼ�.csv
Table Updated: XXXX��X�꼶���ģ���һ�������뱾������������
Input: 
		1. string folderIntput: ԭ���������ڵ��ļ��еľ��Ե�ַ
		2. string folderOutput�������������ڵ��ļ��еľ��Ե�ַ
		3. string name: �˴ο��Ե����ֻ��߳ƺ�
		4. string gradeS: �ο�ѧ�����꼶
Output: XXXX��X�꼶���ģ���һ�������뱾������������
Return: true�������ݷ����ɹ���false�����ʧ��
Others: null
********************************************************************************/
bool getExcel1(string folderIntput, string folderOutput, string name, string gradeS)
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

	int scienceFristBatch = 512;
	int scienceSecondBatch = 375;
	int artsFristBatch = 561;
	int artsSecondBatch = 441;

	/*
	cout << "������һ���ߣ���ƣ�:";
	cin >> scienceFristBatch;
	cout << "�����뱾���ߣ���ƣ�:";
	cin >> scienceSecondBatch;
	cout << "������һ���ߣ��Ŀƣ�:";
	cin >> artsFristBatch;
	cout << "�����뱾���ߣ��Ŀƣ�:";
	cin >> artsSecondBatch;

	cout << "һ���ߣ���ƣ���" << scienceFristBatch << endl;
	cout << "�����ߣ���ƣ���" << scienceSecondBatch << endl;
	cout << "һ���ߣ��Ŀƣ���" << artsFristBatch << endl;
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
	getData(excelNamec1, csv1, type, scienceFristBatch, scienceSecondBatch);
	type = "�Ŀ�";
	getData(excelNamec1, csv2, type, artsFristBatch, artsSecondBatch);
	type = "����";
	getData(excelNamec1, csv3, type, scienceFristBatch, scienceSecondBatch);
	type = "����";
	getData(excelNamec1, csv4, type, artsFristBatch, artsSecondBatch);

	excel1.open(excelNamec1, std::ios::out | std::ios::app);
	excel1 << endl;
	excel1 << "ע,һ����,������" << endl;
	excel1 << "���," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel1 << "�Ŀ�," << artsFristBatch << "," << artsSecondBatch << endl;
	excel1.close();

	return true;
}