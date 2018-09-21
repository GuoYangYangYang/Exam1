#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-20
Description: �����XXXX��X�꼶���ģ����ַܷ���������������
********************************************************************************/

typedef struct classData
{
	string className;
	int allNumber;
	int fristNumber;
	int secondNumber;
	bool SorA;
} classData;

int initClass(vector<classData> &Class, string gradeS, string typeS, string classS)
{
	bool type = false;
	classS = classS.substr(2, 2);
	if (!typeS.compare("���")) type = true;
	else type = false;
	//cout << type << classS << endl;
	if (isNum(classS))
	{
		int classN = atoi(classS.c_str());
		if (classN > Class.size())
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				string className = "��" + gradeS + "��";
				className += to_string(ClassN + 1);
				className += "��";
				classData classNew = {className, 0, 0, 0, true};
				Class.push_back(classNew);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

void getData3(const char * excelName, Csv csv, vector<classData> &Class, string gradeS, double fristBatch, double secondBatch)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.table[0][3].compare("����") == 0) && (csv.table[0][4].compare("�༶") == 0) && (csv.table[0][6].compare("�ܷ�") == 0))
	{
		ofstream excel3;
		excel3.open(excelName, std::ios::out | std::ios::app); // �򿪷����ļ�������

		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶

		if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass(Class, gradeS, csv.table[i][3], csv.table[i][4]);
				if (classN != -1)
				{
					if (!csv.table[i][3].compare("���")) Class[classN - 1].SorA = true;
					else Class[classN - 1].SorA = false;
					score = atoi(csv.table[i][6].c_str());
					if (score >= 0) Class[classN - 1].allNumber++;
					if (score >= secondBatch) Class[classN - 1].secondNumber++;
					if (score >= fristBatch) Class[classN - 1].fristNumber++;
				}
			}
		}

		excel3.close();
	}
}

bool getExcel3(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName3 = folderOutput + "\\" + name + "��" + gradeS + "�꼶����һ�������뱾������������.csv";
	const char * excelNamec3 = excelName3.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	int scienceFristBatch = 512; // ���һ��������
	int scienceSecondBatch = 375; // ��Ʊ��Ʒ�����
	int artsFristBatch = 561; // �Ŀ�һ��������
	int artsSecondBatch = 441; // �ĿƱ��Ʒ�����

	/*
	// ���������
	cout << "������һ���ߣ���ƣ�:";
	cin >> scienceFristBatch;
	cout << "�����뱾���ߣ���ƣ�:";
	cin >> scienceSecondBatch;
	cout << "������һ���ߣ��Ŀƣ�:";
	cin >> artsFristBatch;
	cout << "�����뱾���ߣ��Ŀƣ�:";
	cin >> artsSecondBatch;

	// ��ʾ������
	cout << "һ���ߣ���ƣ���" << scienceFristBatch << endl;
	cout << "�����ߣ���ƣ���" << scienceSecondBatch << endl;
	cout << "һ���ߣ��Ŀƣ���" << artsFristBatch << endl;
	cout << "�����ߣ��Ŀƣ���" << artsSecondBatch << endl;
	*/

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// �༶��Ϣ
	vector<classData> Class;

	// ������������
	string type = "";
	type = "���";
	getData3(excelNamec3, csv1, Class, gradeS, scienceFristBatch, scienceSecondBatch); // ��������ܳɼ�
	type = "�Ŀ�";
	getData3(excelNamec3, csv2, Class, gradeS, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�
	type = "����";
	getData3(excelNamec3, csv3, Class, gradeS, scienceFristBatch, scienceSecondBatch); // ��������ܳɼ�
	type = "����";
	getData3(excelNamec3, csv4, Class, gradeS, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�


	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec3);
	ofstream excel3;
	excel3.open(excelNamec3, std::ios::out | std::ios::app);

	if (!excel3.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel3 << "�༶,�ο�����,һ������,����,��������,����,��/��" << endl;

	for (auto c : Class)
	{
		if (c.allNumber != 0)
		{
			excel3 << c.className << "," << c.allNumber << "," << c.fristNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.fristNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			excel3 << "," << c.secondNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.secondNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			if (c.SorA) excel3 << ",���" << endl;
			else excel3 << ",�Ŀ�" << endl;
		}
	}

	excel3 << endl;
	excel3 << "ע,һ����,������" << endl;
	excel3 << "���," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel3 << "�Ŀ�," << artsFristBatch << "," << artsSecondBatch << endl;

	excel3.close();
	return true;
}