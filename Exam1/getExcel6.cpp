#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-25
Description: ������XXXX��X�꼶�������ģ��Ƶ���һ����������������������
********************************************************************************/

void setScoreBatch(int Class[][5])
{
	int flag = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	while (true)
	{
		vector<string> name = { "����","����","����","Ӣ��","����","��ѧ","����","����","����","����","��ʷ","����" };
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
		Class[flag - 1][1] = firstBatch;
		Class[flag - 1][3] = secondBatch;
	}
}

void getData6(Csv csv, int Class[][5])
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.table[0][3].compare("����") == 0) && (csv.table[0][4].compare("�༶") == 0) && (csv.table[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶

		if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			int type = -1;

			for (int i = 7; i <= 12; i++)
			{
				if (csv.table[0][i].compare("����") == 0) type = 0;
				if (csv.table[0][i].compare("����") == 0) type = 1;
				if (csv.table[0][i].compare("����") == 0) type = 2;
				if (csv.table[0][i].compare("Ӣ��") == 0) type = 3;
				if (csv.table[0][i].compare("����") == 0) type = 4;
				if (csv.table[0][i].compare("��ѧ") == 0) type = 5;
				if (csv.table[0][i].compare("����") == 0) type = 6;
				if (csv.table[0][i].compare("����") == 0) type = 7;
				if (csv.table[0][i].compare("����") == 0) type = 8;
				if (csv.table[0][i].compare("����") == 0) type = 9;
				if (csv.table[0][i].compare("��ʷ") == 0) type = 10;
				if (csv.table[0][i].compare("����") == 0) type = 11;
				if (type != -1)
				{
					for (int j = 1; (isNum(csv.table[j][i])); j++) // ���е����е�����Ϊ����ʱ
					{
						float score = atof(csv.table[j][i].c_str());
						if (score >= 0.0) Class[type][0]++;
						if (score >= (1.0 * Class[type][1])) Class[type][2]++;
						if (score >= (1.0 * Class[type][3])) Class[type][4]++;
					}
				}
				type = -1;
			}
		}
	}
}


bool getExcel6(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName6 = folderOutput + "\\" + name + "��" + gradeS + "�꼶����һ�������뱾������������.csv";
	const char * excelNamec6 = excelName6.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	// �༶��Ϣ
	int Class[13][5] = {0};

	setScoreBatch(Class);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	getData6(csv1, Class); // ��������ܳɼ�
	getData6(csv2, Class); // �����Ŀ��ܳɼ�
	getData6(csv3, Class); // ���������ܳɼ�
	getData6(csv4, Class); // ���������ܳɼ�

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << Class[i][j] << " ";
		}
		cout << endl;
	}

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec6);
	ofstream excel6;
	excel6.open(excelNamec6, std::ios::out | std::ios::app);

	if (!excel6.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel6 << "��Ŀ,�ο�����,һ������,����,��������,����" << endl;


	// ������һ������Ŀ��ߺͱ�������Ŀ���
	excel6 << endl;

	excel6.close();
	return true;
}