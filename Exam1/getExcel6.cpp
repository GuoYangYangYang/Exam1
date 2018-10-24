#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-25
Description: ������XXXX��X�꼶�������ģ��Ƶ���һ����������������������
********************************************************************************/

Excel6::Excel6(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel6::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel6::getExcel()
{
	Exam().clear();

	// ���ݷ�������ļ��ľ���·��
	string excelName6 = folderOutput + "\\" + "������" + name + "��" + gradeS + "�꼶�������ģ��Ƶ���һ����������������������.csv";
	const char * excelNamec6 = excelName6.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Input = folderInput + "\\����ܳɼ�.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Input.c_str();

	// �༶��Ϣ
	int Class[20][5] = { 0 };

	setScoreBatch(Class);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	string typeS = " ";
	typeS = "���";
	getData(csv1, Class, typeS); // ��������ܳɼ�
	typeS = "�Ŀ�";
	getData(csv2, Class, typeS); // �����Ŀ��ܳɼ�
	typeS = "����";
	getData(csv3, Class, typeS); // ���������ܳɼ�
	typeS = "����";
	getData(csv4, Class, typeS); // ���������ܳɼ�

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
	excel6 << "���,�ο�����,һ������,����,��������,����" << endl;

	vector<string> type = { "����","����","��Ӣ","����","��ѧ","����","����",
							"����","����","��Ӣ","����","��ʷ","����","����" };

	for (int i = 0; i < 7; i++) // ������
	{
		excel6 << type[i] << "," << Class[i + 1][0] << "," << Class[i + 1][2] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][2]) / (1.0 *Class[i + 1][0]) << "%,";
		excel6 << Class[i + 1][4] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][4]) / (1.0 *Class[i + 1][0]) << "%";
		excel6 << endl;
	}

	excel6 << endl;
	excel6 << "�Ŀ�,�ο�����,һ������,����,��������,����" << endl;

	for (int i = 7; i < 14; i++) // ����Ŀ�
	{
		excel6 << type[i] << "," << Class[i + 1][0] << "," << Class[i + 1][2] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][2]) / (1.0 *Class[i + 1][0]) << "%,";
		excel6 << Class[i + 1][4] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][4]) / (1.0 *Class[i + 1][0]) << "%";
		excel6 << endl;
	}

	excel6.close();

	Exam().clear();
	cout << "�������ļ�����ַ���£������ҵĵ����д��ļ�����1������" << endl;
	cout << excelNamec6 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

void Excel6::setScoreBatch(int Class[][5])
{
	int flag = -1;
	int maxScore = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	while (true)
	{
		Exam().clear();
		vector<string> name = { "����","����","��Ӣ","����","��ѧ","����","����",
			"����","����","��Ӣ","����","��ʷ","����","����" };
		cout << "+--------------------------------------" << endl;
		cout << "|ѡ���������ö�Ӧ��Ŀ��һ���ߺͱ�����" << endl;
		cout << "+--------------------------------------" << endl;
		for (int i = 1; i <= (int)name.size(); i++)
		{
			cout << "|";
			printf("%2d", i);
			cout << "|" << name[i - 1];
			cout << "|һ���ߣ�";
			printf("%3d", Class[i][1]);
			cout << "|�����ߣ�";
			printf("%3d", Class[i][3]);
			cout << endl;
		}
		cout << "+--------------------------------------" << endl;
		flag = Exam().inputInteger(0, name.size());
		switch (flag)
		{
		case(1): // ����
			maxScore = MaxChineseScore;
			break;
		case(2): // ����
			maxScore = MaxMathScore;
			break;
		case(3): // ��Ӣ
			maxScore = MaxEnglishScore;
			break;
		case(4): // ����
			maxScore = MaxPhysicsScore;
			break;
		case(5): // ��ѧ
			maxScore = MaxChemistryScore;
			break;
		case(6): // ����
			maxScore = MaxBiologyScore;
			break;
		case(7): // ����
			maxScore = MaxScienceComprehensiveScore;
			break;
		case(8): // ����
			maxScore = MaxChineseScore;
			break;
		case(9): // ����
			maxScore = MaxMathScore;
			break;
		case(10): // ��Ӣ
			maxScore = MaxEnglishScore;
			break;
		case(11): // ����
			maxScore = MaxPoliticsScore;
			break;
		case(12): // ��ʷ
			maxScore = MaxHistoryScore;
			break;
		case(13): // ����
			maxScore = MaxGeographyScore;
			break;
		case(14): // ����
			maxScore = MaxArtsComprehensiveScore;
			break;
		default:
			break;
		}
		if (flag == 0) break;
		cout << "������" << name[flag - 1] << "��һ���ߣ�" << endl;
		firstBatch = Exam().inputInteger(0, maxScore);
		cout << "������" << name[flag - 1] << "�ı����ߣ�" << endl;
		secondBatch = Exam().inputInteger(0, firstBatch - 1);
		Class[flag][1] = firstBatch;
		Class[flag][3] = secondBatch;
	}
}

void Excel6::getData(Csv csv, int Class[][5], string typeS)
{
	auto table = csv.getTable();
	// ���ԭʼ���ݱ��������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((table[0][3].compare("����") == 0) && (table[0][4].compare("�༶") == 0) && (table[0][6].compare("�ܷ�") == 0))
	{
		if (!table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			int type = -1;
			int flag = 0;

			if (!typeS.compare("���")) flag = 1;
			if (!typeS.compare("�Ŀ�")) flag = 2;
			if (!typeS.compare("����")) flag = 3;
			if (!typeS.compare("����")) flag = 4;

			if (flag == 1 || flag == 3) // ���
			{
				for (int i = 0; i <= 12; i++)
				{
					if (table[0][i].compare("�ܷ�") == 0) type = 0;
					if (table[0][i].compare("����") == 0) type = 1;
					if (table[0][i].compare("����") == 0) type = 2;
					if (table[0][i].compare("Ӣ��") == 0) type = 3;
					if (table[0][i].compare("����") == 0) type = 4;
					if (table[0][i].compare("��ѧ") == 0) type = 5;
					if (table[0][i].compare("����") == 0) type = 6;

					if (type == 0)
					{
						double score = 0.0;
						for (int j = 1; (score = atof(table[j][i].c_str())) != 0.0; j++) // ���ܴ���bug
							Class[0][flag]++;
					}

					if (type != -1 && type != 0)
					{
						double score = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score = ceill(atof(table[i][6].c_str())); // ��ȡ��ǰѧ������
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type][0]++;
								if (score >= (1.0 * Class[type][1])) Class[type][2]++;
								if (score >= (1.0 * Class[type][3])) Class[type][4]++;
							}
						}
					}

					if (type == 4) // ����⵽����ʱ����������
					{
						double score = 0.0, score1 = 0.0, score2 = 0.0, score3 = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score1 = atof(table[j][i].c_str()), // ��ȡ����
							score2 = atof(table[j][i + 1].c_str()), // ��ȡ��ѧ
							score3 = atof(table[j][i + 2].c_str()), // ��ȡ����
							score = score1 + score2 + score3; // ��������
							score = ceill(score); // ��������
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type + 3][0]++;
								if (score >= (1.0 * Class[type + 3][1])) Class[type + 3][2]++;
								if (score >= (1.0 * Class[type + 3][3])) Class[type + 3][4]++;
							}
						}
					}

					type = -1; // ����type
				}
			} // if

			if (flag == 2 || flag == 4) // �Ŀ�
			{
				for (int i = 0; i <= 12; i++)
				{
					if (table[0][i].compare("�ܷ�") == 0) type = 0;
					if (table[0][i].compare("����") == 0) type = 8;
					if (table[0][i].compare("����") == 0) type = 9;
					if (table[0][i].compare("Ӣ��") == 0) type = 10;
					if (table[0][i].compare("����") == 0) type = 11;
					if (table[0][i].compare("��ʷ") == 0) type = 12;
					if (table[0][i].compare("����") == 0) type = 13;

					if (type == 0)
					{
						double score = 0.0;
						for (int j = 1; (score = atof(table[j][i].c_str())) != 0.0; j++) // ���ܴ���bug
							Class[0][flag]++;
					}

					if (type != -1 && type != 0)
					{
						double score = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score = ceill(atof(table[i][6].c_str())); // ��ȡ��ǰѧ������
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type][0]++;
								if (score >= (1.0 * Class[type][1])) Class[type][2]++;
								if (score >= (1.0 * Class[type][3])) Class[type][4]++;
							}
						}
					}

					if (type == 11) // ����⵽����ʱ����������
					{
						double score = 0.0, score1 = 0.0, score2 = 0.0, score3 = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score1 = atof(table[j][i].c_str()), // ��ȡ����
							score2 = atof(table[j][i + 1].c_str()), // ��ȡ����
							score3 = atof(table[j][i + 2].c_str()), // ��ȡ��ʷ
							score = score1 + score2 + score3; // ��������
							score = ceill(score); // ��������
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type + 3][0]++;
								if (score >= (1.0 * Class[type + 3][1])) Class[type + 3][2]++;
								if (score >= (1.0 * Class[type + 3][3])) Class[type + 3][4]++;
							}
						}
					}

					type = -1; // ����type
				}
			} // if

		}
	}
}
