#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-25
Description: ���ģ�XXXX��X�꼶����ɼ�����������������
********************************************************************************/

int initClass4(vector<vector<int>> &Class, string gradeS, string classS, int scoreSectionNumber)
{
	classS = classS.substr(2, 2);
	if (isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN > Class.size()) // ���༶���볬���������ݱ������������г�ʼ����ֱ���༶����������ݱ��������
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				vector<int> classData(scoreSectionNumber + 3, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

int findScoreSection(vector<int> scoreSection, int score)
{
	int i = scoreSection.size() - 1;
	if (score < scoreSection[i]) return i + 1;
	if (score >= scoreSection[0]) return 0;
	while (i > 0)
	{
		if (score >= scoreSection[i] && score < scoreSection[i - 1]) return i;
		i--;
	}
	return -1;
}

void getData4(Csv csv, vector<vector<int>> &Class, string gradeS, vector<int> scoreSection)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.table[0][3].compare("����") == 0) && (csv.table[0][4].compare("�༶") == 0) && (csv.table[0][6].compare("�ܷ�") == 0))
	{
		if (scoreSection.size() != 0)
		{
			int i = 1; // ����
			int score = -1; // ��ǰѧ���ķ���
			int classN = -1; // ��ǰѧ���İ༶

			if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
			{
				for (i = 1; (isNum(csv.table[i][6])); i++) // ���е����е�����Ϊ����ʱ
				{
					classN = initClass4(Class, gradeS, csv.table[i][4], scoreSection.size()); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
					if (classN != -1)
					{
						if (!csv.table[i][3].compare("���")) Class[classN - 1][0] = 1; // �����Ϊ1
						else Class[classN - 1][0] = 0; // �Ŀ���Ϊfalse
						score = atoi(csv.table[i][6].c_str()); // ��ȡ��ǰѧ������
						if (score >= 0) Class[classN - 1][1]++; // ѧ��������Ч����ο�������һ
						int section = findScoreSection(scoreSection, score);
						if (section != -1) Class[classN - 1][section + 2]++;
					}
				}
			}
		}
	}
}

bool getExcel4(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName4 = folderOutput + "\\" + name + "��" + gradeS + "�꼶����ɼ�����������������.csv";
	const char * excelNamec4 = excelName4.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	// ���������
	vector<int> scoreSection;

	double score = -1;
	double lscore = -1;
	while (true)
	{
		do {
			if (lscore != -1) cout << "��һ����������" << lscore;
			cout << "���������,��������ֱ����ǵ����ݼ���:" << endl;
			cin >> score;
			if (lscore == -1) lscore = score + 1;
		} while (lscore <= score);
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
	}

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	vector<vector<int>> Class;
	
	getData4(csv1, Class, gradeS, scoreSection);
	getData4(csv2, Class, gradeS, scoreSection);
	getData4(csv3, Class, gradeS, scoreSection);
	getData4(csv4, Class, gradeS, scoreSection);

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec4);
	ofstream excel4;
	excel4.open(excelNamec4, std::ios::out | std::ios::app);

	if (!excel4.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel4 << "�༶,�ο�����";
	for (auto ss : scoreSection) excel4 << ",>=" << ss;
	excel4 << ",<=" << scoreSection[scoreSection.size() - 1];

	excel4 << endl;

	for (int i = 0; i < Class.size(); i++)
	{
		if (Class[i][1] != 0)
		{
			excel4 << "��" << gradeS << "��" << (i + 1) << "��";
			for (int j = 1; j < Class[i].size(); j++)
			{
				excel4 << "," << Class[i][j];
			}
			excel4 << endl;
			excel4 << ",";
			for (int j = 2; j < Class[i].size(); j++)
			{
				excel4 << ",";
				excel4 << fixed << setprecision(2) << (100 * (Class[i][j] * 1.0) / (Class[i][1] * 1.0)) << "%";
			}
			excel4 << endl;
		}
	}

	excel4.close();
	return true;
}