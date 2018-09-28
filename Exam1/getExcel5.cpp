#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-25
Description: ���壺XXXX��X�꼶����ɼ�ƽ���ֺͱ�׼��
********************************************************************************/

int initClass5(vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN + 4 > Class1.size()) // ���༶���볬���������ݱ������������г�ʼ����ֱ���༶����������ݱ��������
		{
			int ClassN = Class1.size();
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

void getData5_1(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.getTable()[0][3].compare("����") == 0) && (csv.getTable()[0][4].compare("�༶") == 0) && (csv.getTable()[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶
		int type = 0; // ��ǰѧ������

		if (!csv.getTable().empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass5(Class1, Class2, gradeS, csv.getTable()[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					classN += 3;
					if (!typeS.compare("���")) type = 0;
					if (!typeS.compare("�Ŀ�")) type = 1;
					if (!typeS.compare("����")) type = 2;
					if (!typeS.compare("����")) type = 3;
					if (!csv.getTable()[i][3].compare("���")) Class1[classN][0] = 1; // �����Ϊ1
					else Class1[classN][0] = 0; // �Ŀ���Ϊfalse
					score = atoi(csv.getTable()[i][6].c_str()); // ��ȡ��ǰѧ������
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

void getData5_2(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.getTable()[0][3].compare("����") == 0) && (csv.getTable()[0][4].compare("�༶") == 0) && (csv.getTable()[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶
		int type = 0; // ��ǰѧ������

		if (!csv.getTable().empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass5(Class1, Class2, gradeS, csv.getTable()[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					classN += 3;
					if (!typeS.compare("���")) type = 0;
					if (!typeS.compare("�Ŀ�")) type = 1;
					if (!typeS.compare("����")) type = 2;
					if (!typeS.compare("����")) type = 3;
					score = atoi(csv.getTable()[i][6].c_str()); // ��ȡ��ǰѧ������
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

bool getExcel5(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName5 = folderOutput + "\\" + name + "��" + gradeS + "�꼶����ɼ�ƽ���ֺͱ�׼��.csv";
	const char * excelNamec5 = excelName5.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	vector<vector<int>> Class1;
	vector<vector<double>> Class2;

	string type = " ";
	type = "���";
	getData5_1(csv1, Class1, Class2, gradeS, type);
	type = "�Ŀ�";
	getData5_1(csv2, Class1, Class2, gradeS, type);
	type = "����";
	getData5_1(csv3, Class1, Class2, gradeS, type);
	type = "����";
	getData5_1(csv4, Class1, Class2, gradeS, type);

	for (int i = 0; i < Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			Class2[i][0] = (1.0 * Class1[i][2]) / (1.0 * Class1[i][1]);
		}
	}

	type = "���";
	getData5_2(csv1, Class1, Class2, gradeS, type);
	type = "�Ŀ�";
	getData5_2(csv2, Class1, Class2, gradeS, type);
	type = "����";
	getData5_2(csv3, Class1, Class2, gradeS, type);
	type = "����";
	getData5_2(csv4, Class1, Class2, gradeS, type);

	for (int i = 0; i < Class1.size(); i++)
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

	for (int i = 0; i < Class1.size(); i++)
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
	return true;
}