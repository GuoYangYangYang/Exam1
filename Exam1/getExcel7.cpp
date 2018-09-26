#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-26
Description: ���ߣ�XXXX��X�꼶��Ƹ��൥��һ����������������������
********************************************************************************/

void setScoreBatch7(vector<vector<int>> &Class)
{
	int flag = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	if (Class.size() < 1)
	{
		vector<int> batch(15, 0);
		Class.push_back(batch);
	}
	while (Class.size() > 0)
	{
		vector<string> name = { "����","����","Ӣ��","����","��ѧ","����","����" };
		cout << "+--------------------------------------" << endl;
		cout << "|ѡ���������ö�Ӧ��Ŀ��һ���ߺͱ�����" << endl;
		cout << "+--------------------------------------" << endl;
		for (int i = 1; i <= name.size(); i++)
		{
			cout << "|";
			printf("%2d", i);
			cout << "|" << name[i - 1];
			cout << "|һ���ߣ�";
			printf("%3d", Class[i - 1][1]);
			cout << "|�����ߣ�";
			printf("%3d", Class[i - 1][3]);
			cout << endl;
		}
		cout << "+--------------------------------------" << endl;
		cin >> flag;
		if (flag < 1) break;
		cout << "������" << name[flag - 1] << "��һ���ߣ�" << endl;
		cin >> firstBatch;
		cout << "������" << name[flag - 1] << "�ı����ߣ�" << endl;
		cin >> secondBatch;
		Class[0][flag] = firstBatch;
		Class[0][flag] = secondBatch;
	}
}

int initClass7(vector<vector<int>> &Class, string classS)
{
	classS = classS.substr(2, 2);
	if (isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN >= Class.size()) // ���༶���볬���������ݱ������������г�ʼ����ֱ���༶����������ݱ��������
		{
			int ClassN = Class.size();
			while (classN >= ClassN)
			{
				vector<int> classData(15, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

void getData7(Csv csv, vector<vector<int>> &Class, string gradeS, string typeS)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�������������
	if ((csv.table[0][3].compare("����") == 0) && 
		(csv.table[0][4].compare("�༶") == 0) && 
		(csv.table[0][6].compare("�ܷ�") == 0) &&
		(csv.table[0][7].compare("����") == 0) &&
		(csv.table[0][8].compare("��ѧ") == 0) &&
		(csv.table[0][9].compare("Ӣ��") == 0) &&
		(csv.table[0][10].compare("����") == 0) &&
		(csv.table[0][11].compare("��ѧ") == 0) &&
		(csv.table[0][12].compare("����") == 0)
		)
	{
		int i = 1; // ����
		int classN = -1; // ��ǰѧ���İ༶
		int score[8] = { 0 };

		if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass7(Class, csv.table[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					for (int j = 0; j < 7; j++)
					{
						score[j] = atof(csv.table[i][j + 6].c_str()); // ��ȡ��ǰѧ������
					}
					if (score[0] >= 0) Class[classN][0]++; // ѧ��������Ч����ο�������һ
					for (int j = 1; j < 7; j++)
					{
						if (score[j] > Class[0][2 * j - 1]) Class[j][2 * j - 1]++;
						if (score[j] > Class[0][2 * j]) Class[j][2 * j]++;
					}
				}
			}
		}
	}
}

bool getExcel7(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName7 = folderOutput + "\\" + name + "��" + gradeS + "�꼶��Ƹ��൥��һ����������������������.csv";
	const char * excelNamec7 = excelName7.c_str();

	// ԭʼ���������ļ��ľ���·�������������ֱ������ƣ�����
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();

	// �༶��Ϣ
	vector<vector<int>> Class;

	setScoreBatch7(Class);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);

	// ������������
	string typeS = " ";
	typeS = "���";
	//getData7(csv1, Class, typeS); // ��������ܳɼ�
	typeS = "����";
	//getData7(csv3, Class, typeS); // ���������ܳɼ�

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec7);
	ofstream excel7;
	excel7.open(excelNamec7, std::ios::out | std::ios::app);

	if (!excel7.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel7 << ",,��,��,��,��,Ӣ,��,��,��,��,ѧ,��,��,��,��," << endl;
	excel7 << ",�ο�����,һ������,��������,һ������,��������,һ������,��������,һ������,��������,һ������,��������,һ������,��������,һ������,��������," << endl;




	excel7.close();
	return true;
	return true;
}
