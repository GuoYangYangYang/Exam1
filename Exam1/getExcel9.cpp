#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-27
Description: ��ţ�XXXX��X�꼶XX���Ʒ���������������
********************************************************************************/

void setScoreBatch9(vector<float> &scoreSection)
{
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
}

int initClass9(vector<vector<int>> &Class, string classS, int scoreSectionSize)
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
				vector<int> classData(scoreSectionSize + 2, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

int findScoreSection9(vector<float> scoreSection, float score)
{
	int i = scoreSection.size() - 1;
	if (score < scoreSection[i]) return i + 1;
	if (score >= scoreSection[0]) return 0;
	while (i > 0)
	{
		if (score >= scoreSection[i] && score < scoreSection[i - 1]) return i;
		i--;
	}
	return 0;
}

void getData9(Csv csv, vector<vector<int>> &Class, vector<float> scoreSection, string typeS)
{
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.getTable()[0][3].compare("����") == 0) &&
		(csv.getTable()[0][4].compare("�༶") == 0) &&
		(csv.getTable()[0][6].compare("�ܷ�") == 0)
		)
	{

		int typeN = 0;
		for (int l = 7; l <= 12; l++)
			if (csv.getTable()[0][l].compare(typeS) == 0)
				typeN = l;

		int i = 1; // ����
		int classN = -1; // ��ǰѧ���İ༶
		float score =  0; // ��ǰѧ���ķ���
		int section = -1; // ��ǰѧ���������ڷ�����

		if (!csv.getTable().empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // ���е�����Ϊ����ʱ
			{
				classN = initClass9(Class, csv.getTable()[i][4], scoreSection.size()); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					score = atof(csv.getTable()[i][typeN].c_str()); // ��ȡ��ǰѧ������
					if (score > 0.0)
					{
						Class[classN][0]++; // ѧ��������Ч����ο�������һ
						section = findScoreSection9(scoreSection, score);
						if (section != -1) Class[classN][section + 1]++;
					}
				}
				classN = -1;
				score = 0;
				section = -1;
			}
		}
	}
}

bool getExcel9(string folderIntput, string folderOutput, string name, string gradeS)
{
	string typeS = " ";

	int typeN = 0;

	vector<string> name9 = { "����","����","����","Ӣ��","����","��ѧ","����","����","����","��ʷ","����","����" };
	cout << "+--------------------------------------" << endl;
	cout << "|ѡ���Ŀ��" << endl;
	cout << "+--------------------------------------" << endl;
	for (int i = 1; i <= name9.size(); i++)
	{
		cout << "|";
		printf("%2d", i);
		cout << "|" << name9[i - 1];
		cout << endl;
	}
	cout << "+--------------------------------------" << endl;
	cin >> typeN;

	if (typeN > 0 && typeN <= name9.size()) typeS = name9[typeN - 1];
	else return false;

	// ���ݷ�������ļ��ľ���·��
	string excelName9 = folderOutput + "\\" + name + "��" + gradeS + "�꼶"+ typeS +"���Ʒ���������������.csv";
	const char * excelNamec9 = excelName9.c_str();

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
	vector<vector<int>> Class;

	vector<float> scoreSection;

	setScoreBatch9(scoreSection);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	getData9(csv1, Class, scoreSection, typeS); // ��������ܳɼ�
	getData9(csv2, Class, scoreSection, typeS); // ���������ܳɼ�
	getData9(csv3, Class, scoreSection, typeS); // ��������ܳɼ�
	getData9(csv4, Class, scoreSection, typeS); // ���������ܳɼ�

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec9);
	ofstream excel9;
	excel9.open(excelNamec9, std::ios::out | std::ios::app);

	if (!excel9.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	// ��ʼ�����ݷ�����
	excel9 << "��Ŀ:" << typeS << ",�ο�����";
	for (auto ss : scoreSection) excel9 << ",>=" << ss;
	excel9 << ",<" << scoreSection[scoreSection.size() - 1] << endl;;

	for (int i = 1; i < Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel9 << "��" << gradeS << "��" << i << "��";
			for (int j = 0; j < Class[i].size(); j++) excel9 << "," << Class[i][j];
			excel9 << endl;
			excel9 << ",";
			for (int j = 1; j < Class[i].size(); j++)
			{
				excel9 << ",";
				excel9 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%";
			}
			excel9 << endl;
		}
	}


	excel9.close();
	return true;
}