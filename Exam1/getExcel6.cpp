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

void getData6(Csv csv, int Class[][5], string typeS)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.table[0][3].compare("����") == 0) && (csv.table[0][4].compare("�༶") == 0) && (csv.table[0][6].compare("�ܷ�") == 0))
	{
		if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			int type = -1;
			int flag = 0;

			if (!typeS.compare("���")) flag = 1;
			if (!typeS.compare("�Ŀ�")) flag = 2;
			if (!typeS.compare("����")) flag = 3;
			if (!typeS.compare("����")) flag = 4;

			for (int i = 6; i <= 12; i++)
			{
				if (csv.table[0][i].compare("�ܷ�") == 0) type = 0;
				if (csv.table[0][i].compare("����") == 0) type = 1;
				if (csv.table[0][i].compare("����") == 0) type = 2;
				if (csv.table[0][i].compare("����") == 0) type = 3;
				if (csv.table[0][i].compare("Ӣ��") == 0) type = 4;
				if (csv.table[0][i].compare("����") == 0) type = 5;
				if (csv.table[0][i].compare("��ѧ") == 0) type = 6;
				if (csv.table[0][i].compare("����") == 0) type = 7;
				if (csv.table[0][i].compare("����") == 0) type = 8;
				if (csv.table[0][i].compare("����") == 0) type = 9;
				if (csv.table[0][i].compare("����") == 0) type = 10;
				if (csv.table[0][i].compare("��ʷ") == 0) type = 11;
				if (csv.table[0][i].compare("����") == 0) type = 12;

				if (type == 0)
					for (int j = 1, score = 0.0; (score = atof(csv.table[j][i].c_str())) != 0.0; j++)
						Class[0][flag]++;

				if (type != -1 && type != 0)
				{
					float score = 0.0;
					for (int j = 1; j <= Class[0][flag]; j++)
					{
						score = atof(csv.table[j][i].c_str());
						if (score != 0.0)
						{
							if (score >= 0.0) Class[type][0]++;
							if (score >= (1.0 * Class[type][1])) Class[type][2]++;
							if (score >= (1.0 * Class[type][3])) Class[type][4]++;
						}
					}
				}

				if (type == 5 || type == 9) // ����⵽���������ʱ���������ۻ�����
				{
					float score = 0.0, score1 = 0.0, score2 = 0.0, score3 = 0.0;
					for (int j = 1; j <= Class[0][flag]; j++)
					{
						score1 = atof(csv.table[j][i].c_str()), // ��ȡ���������
						score2 = atof(csv.table[j][i + 1].c_str()), // ��ȡ��ѧ�����
						score3 = atof(csv.table[j][i + 2].c_str()), // ��ȡ�������ʷ
						score = score1 + score2 + score3; // �������ۻ�����
						if (score != 0.0)
						{
							if (score >= 0.0) Class[type + 3][0]++;
							if (score >= (1.0 * Class[type + 3][1])) Class[type + 3][2]++;
							if (score >= (1.0 * Class[type + 3][3])) Class[type + 3][4]++;
						}
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
	string excelName6 = folderOutput + "\\" + name + "��" + gradeS + "�꼶�������ģ��Ƶ���һ����������������������.csv";
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
	int Class[14][5] = {0};

	setScoreBatch(Class);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	string typeS = " ";
	typeS = "���";
	getData6(csv1, Class, typeS); // ��������ܳɼ�
	typeS = "�Ŀ�";
	getData6(csv2, Class, typeS); // �����Ŀ��ܳɼ�
	typeS = "����";
	getData6(csv3, Class, typeS); // ���������ܳɼ�
	typeS = "����";
	getData6(csv4, Class, typeS); // ���������ܳɼ�

	for (int i = 0; i < 13; i++)
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

	vector<string> type = { "����","����","����","Ӣ��","����","��ѧ","����","����","����","����","��ʷ","����" };

	for (int i = 0; i < type.size(); i++)
	{
		excel6 << type[i] << "," << Class[i + 1][0] << "," << Class[i + 1][2] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][2]) / (1.0 *Class[i + 1][0]) << "%,";
		excel6 << Class[i + 1][0] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][4]) / (1.0 *Class[i + 1][0]) << "%";
		excel6 << endl;
	}

	excel6.close();
	return true;
}