#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-27
Description: ��ţ�XXXX��X�꼶XX���Ʒ���������������
********************************************************************************/

Excel9::Excel9(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel9::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel9::getExcel()
{
	Exam().clear();

	string typeS = " ";

	int typeN = 0;
	int maxScore = -1;

	vector<string> name9 = { "����","����","����","Ӣ��","����","��ѧ","����","����","����","��ʷ","����","����" };
	cout << "+--------------------------------------------------------" << endl;
	cout << "|ѡ���Ŀ������0�����ɷ������ݣ�" << endl;
	cout << "+--------------------------------------------------------" << endl;
	for (int i = 1; i <= (int)name9.size(); i++)
	{
		cout << "|";
		printf("%2d", i);
		cout << "|" << name9[i - 1];
		cout << endl;
	}
	cout << "+--------------------------------------------------------" << endl;
	typeN = Exam().inputInteger(0, 12);
	switch (typeN)
	{
	case(1):
		maxScore = MaxChineseScore;
		break;
	case(2):
		maxScore = MaxMathScore;
		break;
	case(3):
		maxScore = MaxMathScore;
		break;
	case(4):
		maxScore = MaxEnglishScore;
		break;
	case(5):
		maxScore = MaxPhysicsScore;
		break;
	case(6):
		maxScore = MaxChemistryScore;
		break;
	case(7):
		maxScore = MaxBiologyScore;
		break;
	case(8):
		maxScore = MaxScienceComprehensiveScore;
		break;
	case(9):
		maxScore = MaxPoliticsScore;
		break;
	case(10):
		maxScore = MaxHistoryScore;
		break;
	case(11):
		maxScore = MaxGeographyScore;
		break;
	case(12):
		maxScore = MaxArtsComprehensiveScore;
		break;
	default:
		break;
	}

	if (typeN > 0 && typeN <= (int)name9.size()) typeS = name9[typeN - 1];
	else return false;

	// ���ݷ�������ļ��ľ���·��
	string excelName9 = folderOutput + "\\" + "��ţ�" + name + "��" + gradeS + "�꼶" + typeS + "���Ʒ���������������.csv";
	const char * excelNamec9 = excelName9.c_str();

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
	vector<vector<int>> Class;

	vector<double> scoreSection;

	setScoreBatch(scoreSection, (double)maxScore);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	getData(csv1, Class, scoreSection, typeS); // ��������ܳɼ�
	getData(csv2, Class, scoreSection, typeS); // ���������ܳɼ�
	getData(csv3, Class, scoreSection, typeS); // ��������ܳɼ�
	getData(csv4, Class, scoreSection, typeS); // ���������ܳɼ�

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
	excel9 << "��Ŀ:" << typeS << ",�ο�����";
	for (auto ss : scoreSection) excel9 << ",>=" << ss;
	excel9 << ",<" << scoreSection[scoreSection.size() - 1] << endl;;

	for (int i = 1; i < (int)Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel9 << "��" << gradeS << "��" << i << "��";
			for (int j = 0; j < (int)Class[i].size(); j++) excel9 << "," << Class[i][j];
			excel9 << endl;
			excel9 << ",";
			for (int j = 1; j < (int)Class[i].size(); j++)
			{
				excel9 << ",";
				excel9 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%";
			}
			excel9 << endl;
		}
	}

	excel9.close();

	Exam().clear();
	cout << "�������ļ�����ַ���£������ҵĵ����д��ļ�����1������" << endl;
	cout << excelNamec9 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

void Excel9::setScoreBatch(vector<double> &scoreSection, double maxScore)
{
	Exam().clear();

	double score = -1;
	double lscore = -1;
	cout << "�����ܷ���" << maxScore << "��";
	score = Exam().inputDouble(0, maxScore);
	lscore = score;
	scoreSection.push_back(score);
	while (true)
	{
		do {
			if (lscore != -1) cout << "��һ����������" << lscore;
			cout << "���������,��������ֱ����ǵ����ݼ���:" << endl;
			score = Exam().inputDouble(0, lscore);
			if (lscore == -1) lscore = score + 1;
		} while (lscore <= score);
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
	}
}

int Excel9::initClass(vector<vector<int>> &Class, string classS, int scoreSectionSize)
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
				vector<int> classData(scoreSectionSize + 2, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

int Excel9::findScoreSection(vector<double> scoreSection, double score)
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

void Excel9::getData(Csv csv, vector<vector<int>> &Class, vector<double> scoreSection, string typeS)
{
	auto table = csv.getTable();
	// ���ԭʼ���ݱ��������Ƿ�Ϊ�����ࡱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((table[0][3].compare("����") == 0) &&
		(table[0][4].compare("�༶") == 0) &&
		(table[0][6].compare("�ܷ�") == 0)
		)
	{

		int typeN = 0;
		
		if (typeS.compare("����") == 0)
		{
			for (int l = 7; l <= 12; l++)
				if (table[0][l].compare("����") == 0)
					typeN = l;
		}
		else if (typeS.compare("����") == 0)
		{
			for (int l = 7; l <= 12; l++)
				if (table[0][l].compare("����") == 0)
					typeN = l;
		}
		else
		{
			for (int l = 7; l <= 12; l++)
				if (table[0][l].compare(typeS) == 0)
					typeN = l;
		}

		int i = 1; // ����
		int classN = -1; // ��ǰѧ���İ༶
		double score = 0; // ��ǰѧ���ķ���
		int section = -1; // ��ǰѧ���������ڷ�����

		if (!table.empty() && typeN >= 7) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // ���е�����Ϊ����ʱ
			{
				classN = initClass(Class, table[i][4], (int)scoreSection.size()); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					if (typeS.compare("����") == 0 || typeS.compare("����") == 0)
						score = atof(table[i][typeN].c_str()) + atof(table[i][typeN + 1].c_str()) + atof(table[i][typeN + 2].c_str());
					else 
						score = ceill(atof(table[i][typeN].c_str())); // ��ȡ��ǰѧ������
					if (score > 0.0)
					{
						Class[classN][0]++; // ѧ��������Ч����ο�������һ
						section = findScoreSection(scoreSection, score);
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

