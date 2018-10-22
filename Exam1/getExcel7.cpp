#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-27
Description: ���ߣ�XXXX��X�꼶��Ƹ��൥��һ����������������������
********************************************************************************/

Excel7::Excel7(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel7::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel7::getExcel()
{
	Exam().clear();
	// ���ݷ�������ļ��ľ���·��
	string excelName7 = folderOutput + "\\" + "���ߣ�" + name + "��" + gradeS + "�꼶��Ƹ��൥��һ����������������������.csv";
	const char * excelNamec7 = excelName7.c_str();

	// ԭʼ���������ļ��ľ���·�������������ֱ������ƣ�����
	string file1Input = folderInput + "\\����ܳɼ�.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file2 = file2Input.c_str();

	// �༶��Ϣ
	vector<vector<int>> Class;

	setScoreBatch(Class);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);

	// ������������
	string typeS = " ";
	typeS = "���";
	getData(csv1, Class); // ��������ܳɼ�
	typeS = "����";
	getData(csv2, Class); // ���������ܳɼ�

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

	for (int i = 1; i < (int)Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel7 << "��" << gradeS << "��" << i << "��";
			for (int j = 0; j < (int)Class[i].size(); j++) excel7 << "," << Class[i][j];
			excel7 << endl;
			excel7 << ",,";
			for (int j = 1; j < (int)Class[i].size(); j++)
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

	Exam().clear();
	cout << "�������ļ�����ַ���£������ҵĵ����д��ļ�����1������" << endl;
	cout << excelNamec7 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}


void Excel7::setScoreBatch(vector<vector<int>> &Class)
{
	int flag = -1;
	int maxScore = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	if (Class.size() < 1)
	{
		vector<int> batch(15, 0);
		Class.push_back(batch);
	}
	while (Class.size() > 0)
	{
		Exam().clear();
		vector<string> name = { "����","����","Ӣ��","����","��ѧ","����","����" };
		cout << "+--------------------------------------------------------" << endl;
		cout << "|ѡ���������ö�Ӧ��Ŀ��һ���ߺͱ����ߣ�����0���ɷ�������" << endl;
		cout << "+--------------------------------------------------------" << endl;
		for (int i = 1; i <= (int)name.size(); i++)
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
		cout << "+--------------------------------------------------------" << endl;
		flag = Exam().inputInteger(0, 7);
		switch (flag)
		{
		case(1):
			maxScore = MaxChineseScore;
			break;
		case(2):
			maxScore = MaxMathScore;
			break;
		case(3):
			maxScore = MaxEnglishScore;
			break;
		case(4):
			maxScore = MaxPhysicsScore;
			break;
		case(5):
			maxScore = MaxChemistryScore;
			break;
		case(6):
			maxScore = MaxBiologyScore;
			break;
		case(7):
			maxScore = MaxScienceComprehensiveScore;
			break;
		default:
			break;
		}
		if (flag == 0) break;
		cout << "������" << name[flag - 1] << "��һ���ߣ�" << endl;
		firstBatch = Exam().inputInteger(0, maxScore);
		cout << "������" << name[flag - 1] << "�ı����ߣ�" << endl;
		secondBatch = Exam().inputInteger(0, firstBatch - 1);
		Class[0][2 * flag - 1] = firstBatch;
		Class[0][2 * flag] = secondBatch;
	}
}

int Excel7::initClass(vector<vector<int>> &Class, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN >= (int)Class.size()) // ���༶���볬���������ݱ������������г�ʼ����ֱ���༶����������ݱ��������
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

void Excel7::getData(Csv csv, vector<vector<int>> &Class)
{
	auto table = csv.getTable();
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�������������
	if ((table[0][3].compare("����") == 0) &&
		(table[0][4].compare("�༶") == 0) &&
		(table[0][6].compare("�ܷ�") == 0) &&
		(table[0][7].compare("����") == 0) &&
		(table[0][8].compare("����") == 0) &&
		(table[0][9].compare("Ӣ��") == 0) &&
		(table[0][10].compare("����") == 0) &&
		(table[0][11].compare("��ѧ") == 0) &&
		(table[0][12].compare("����") == 0)
		)
	{
		int i = 1; // ����
		int classN = -1; // ��ǰѧ���İ༶
		double score[8] = { 0 };

		if (!table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass(Class, table[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					for (int j = 0; j < 7; j++)
					{
						score[j] = atof(table[i][j + 6].c_str()); // ��ȡ��ǰѧ������
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