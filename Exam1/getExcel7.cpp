#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-27
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
			printf("%3d", Class[0][2 * i - 1]);
			cout << "|�����ߣ�";
			printf("%3d", Class[0][2 * i]);
			cout << endl;
		}
		cout << "+--------------------------------------" << endl;
		cin >> flag;
		if (flag < 1) break;
		cout << "������" << name[flag - 1] << "��һ���ߣ�" << endl;
		cin >> firstBatch;
		cout << "������" << name[flag - 1] << "�ı����ߣ�" << endl;
		cin >> secondBatch;
		Class[0][2 * flag - 1] = firstBatch;
		Class[0][2 * flag] = secondBatch;
	}
}

int initClass7(vector<vector<int>> &Class, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // ���༶�����Ƿ�Ϸ�
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

void getData7(Csv csv, vector<vector<int>> &Class)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�������������
	if ((csv.getTable()[0][3].compare("����") == 0) &&
		(csv.getTable()[0][4].compare("�༶") == 0) &&
		(csv.getTable()[0][6].compare("�ܷ�") == 0) &&
		(csv.getTable()[0][7].compare("����") == 0) &&
		(csv.getTable()[0][8].compare("����") == 0) &&
		(csv.getTable()[0][9].compare("Ӣ��") == 0) &&
		(csv.getTable()[0][10].compare("����") == 0) &&
		(csv.getTable()[0][11].compare("��ѧ") == 0) &&
		(csv.getTable()[0][12].compare("����") == 0)
		)
	{
		int i = 1; // ����
		int classN = -1; // ��ǰѧ���İ༶
		float score[8] = { 0 };

		if (!csv.getTable().empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass7(Class, csv.getTable()[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					for (int j = 0; j < 7; j++)
					{
						score[j] = atof(csv.getTable()[i][j + 6].c_str()); // ��ȡ��ǰѧ������
					}
					score[7] = score[4] + score[5] + score[6]; // ����ѧ�����۳ɼ�
					if (score[0] >= 0) Class[classN][0]++; // ѧ��������Ч����ο�������һ
					for (int j = 1; j < 8; j++)
					{
						if (score[j] >= Class[0][2 * j - 1]) Class[classN][2 * j - 1]++;
						if (score[j] >= Class[0][2 * j]) Class[classN][2 * j]++;
					}
					for (int j = 0; j < 8; j++) score[j] = 0;
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
	getData7(csv1, Class); // ��������ܳɼ�
	typeS = "����";
	getData7(csv2, Class); // ���������ܳɼ�

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
	excel7 << ",,����,,����,,Ӣ��,,����,,��ѧ,,����,,����,," << endl;
	excel7 << ",�ο�����,һ������,��������,һ������,��������,һ������,��������,һ������,��������,һ������,��������,һ������,��������,һ������,��������," << endl;

	for (int i = 1; i < Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel7 << "��" << gradeS << "��" << i << "��";
			for (int j = 0; j < Class[i].size(); j++) excel7 << "," << Class[i][j];
			excel7 << endl;
			excel7 << ",,";
			for (int j = 1; j < Class[i].size(); j++) 
				excel7 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%,";
			excel7 << endl;
		}
	}

	excel7 << endl << "ע,һ����,������" << endl;
	excel7 << "����," << Class[0][1] << "," << Class[0][2] << endl;
	excel7 << "����," << Class[0][3] << "," << Class[0][4] << endl;
	excel7 << "Ӣ��," << Class[0][5] << "," << Class[0][6] << endl;
	excel7 << "����," << Class[0][7] << "," << Class[0][8] << endl;
	excel7 << "��ѧ," << Class[0][9] << "," << Class[0][10] << endl;
	excel7 << "����," << Class[0][11] << "," << Class[0][12] << endl;
	excel7 << "����," << Class[0][13] << "," << Class[0][14] << endl;

	excel7.close();
	return true;
	return true;
}
