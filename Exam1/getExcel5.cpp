#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-25
Description: ���壺XXXX��X�꼶����ɼ�ƽ���ֺͱ�׼��
********************************************************************************/

Excel5::Excel5(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel5::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel5::getExcel()
{
	Exam().clear();

	// ���ݷ�������ļ��ľ���·��
	string excelName5 = folderOutput + "\\" + name + "��" + gradeS + "�꼶����ɼ�ƽ���ֺͱ�׼��.csv";
	const char * excelNamec5 = excelName5.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Input = folderInput + "\\����ܳɼ�.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Input.c_str();

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	vector<vector<int>> Class1;
	vector<vector<double>> Class2;

	string type = " ";
	type = "���";
	getData1(csv1, Class1, Class2, gradeS, type);
	type = "�Ŀ�";
	getData1(csv2, Class1, Class2, gradeS, type);
	type = "����";
	getData1(csv3, Class1, Class2, gradeS, type);
	type = "����";
	getData1(csv4, Class1, Class2, gradeS, type);

	for (int i = 0; i < (int)Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			Class2[i][0] = (1.0 * Class1[i][2]) / (1.0 * Class1[i][1]);
		}
	}

	type = "���";
	getData2(csv1, Class1, Class2, gradeS, type);
	type = "�Ŀ�";
	getData2(csv2, Class1, Class2, gradeS, type);
	type = "����";
	getData2(csv3, Class1, Class2, gradeS, type);
	type = "����";
	getData2(csv4, Class1, Class2, gradeS, type);

	for (int i = 0; i < (int)Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			Class2[i][2] = sqrt((1.0 * Class2[i][1]) / (1.0 * Class1[i][1]));
		}
	}

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec5);
	ofstream excel5;
	excel5.open(excelNamec5, std::ios::out | std::ios::app);

	if (!excel5.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel5 << "����,�ο�����,ƽ����,��׼��" << endl;

	for (int i = 0; i < (int)Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			if (i < 4)
			{
				if (i == 0) excel5 << "���";
				if (i == 1) excel5 << "�Ŀ�";
				if (i == 2) excel5 << "����";
				if (i == 3) excel5 << "����";
			}
			else
			{
				excel5 << "��" << gradeS << "��" << (i - 3) << "��";
			}
			excel5 << "," << Class1[i][1] << ",";
			excel5 << fixed << setprecision(2) << Class2[i][0] << ",";
			excel5 << fixed << setprecision(2) << Class2[i][2] << endl;
		}
	}

	excel5.close();

	Exam().clear();
	cout << "�������ļ�����ַ���£������ҵĵ����д��ļ�����1������" << endl;
	cout << excelNamec5 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

int Excel5::initClass(vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN + 4 > (int)Class1.size()) // ���༶���볬���������ݱ������������г�ʼ����ֱ���༶����������ݱ��������
		{
			int ClassN = (int)Class1.size();
			while (classN + 4 > ClassN)
			{
				vector<int> classData1(3, 0);
				vector<double> classData2(3, 0.0);
				Class1.push_back(classData1);
				Class2.push_back(classData2);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

void Excel5::getData1(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS)
{
	auto table = csv.getTable();
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((table[0][3].compare("����") == 0) && (table[0][4].compare("�༶") == 0) && (table[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶
		int type = 0; // ��ǰѧ������

		if (!table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass(Class1, Class2, gradeS, table[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					classN += 3;
					if (!typeS.compare("���")) type = 0;
					if (!typeS.compare("�Ŀ�")) type = 1;
					if (!typeS.compare("����")) type = 2;
					if (!typeS.compare("����")) type = 3;
					if (!table[i][3].compare("���")) Class1[classN][0] = 1; // �����Ϊ1
					else Class1[classN][0] = 0; // �Ŀ���Ϊfalse
					score = atoi(table[i][6].c_str()); // ��ȡ��ǰѧ������
					if (score >= 0) // ѧ��������Ч����ο�������һ
					{
						Class1[type][1]++;
						Class1[type][2] += score;
						Class1[classN][1]++;
						Class1[classN][2] += score;
					}
				}
			}
		}
	}
}

void Excel5::getData2(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS)
{
	auto table = csv.getTable();
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((table[0][3].compare("����") == 0) && (table[0][4].compare("�༶") == 0) && (table[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶
		int type = 0; // ��ǰѧ������

		if (!table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass(Class1, Class2, gradeS, table[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					classN += 3;
					if (!typeS.compare("���")) type = 0;
					if (!typeS.compare("�Ŀ�")) type = 1;
					if (!typeS.compare("����")) type = 2;
					if (!typeS.compare("����")) type = 3;
					score = atoi(table[i][6].c_str()); // ��ȡ��ǰѧ������
					if (score >= 0) // ѧ��������Ч����ο�������һ
					{
						Class2[type][1] += (1.0 * score - Class2[type][0]) * (1.0 * score - Class2[type][0]);
						Class2[classN][1] += (1.0 * score - Class2[classN][0]) * (1.0 * score - Class2[classN][0]);
					}
				}
			}
		}
	}
}
