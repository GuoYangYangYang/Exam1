#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-20
Description: �����XXXX��X�꼶���ģ����ַܷ���������������
********************************************************************************/

/********************************************************************************
Function: getData2
Description: ͳ��һ��csv���С��ܷ֡���һ�еķ�����
Calls: getExcel2
Table Accessed: XXXX��X�꼶���ģ����ַܷ���������������
Table Updated: XXXX��X�꼶���ģ����ַܷ���������������
Input:
1. const char * excelName: ���ݷ�����ľ��Ե�ַ
2. Csv csv: �Ѿ�����õ�Csv�����ں�ԭʼ���ݱ�table
3. string type: �˴η������ݵ����ͣ���Ҫ�У���ƣ��Ŀƣ���������
4. vector<double> scoreSection: ÿ��Ԫ��Ϊ��������ÿ�εķ���
Output: ��ָ��csv�ļ�����һ�з�������
Return: null
Others: null
********************************************************************************/
void getData2(const char * excelName, Csv csv, string type, vector<double> scoreSection)
{
	if (csv.table[0][6].compare("�ܷ�") == 0) // ���ԭʼ���ݱ��������Ƿ�Ϊ���ܷ֡�
	{
		ofstream excel2;
		excel2.open(excelName, std::ios::out | std::ios::app); // �򿪷����ļ�������

		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int student = 0; // ѧ����Ŀ
		int scoreEvery[1000] = { 0 }; // һ��һ�α�
		int scoreSectionSize = scoreSection.size(); // �����ֵķ�������Ŀ
		vector<int> scoreNumber(scoreSectionSize + 1); // ÿ�������ε�ѧ������
		vector<double> scoreBatch(scoreSectionSize + 1); // ÿ�������ε�ѧ������

		if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				score = atoi(csv.table[i][6].c_str()); // ��¼��ǰѧ�����ܷ�
				scoreEvery[score]++;
				student++;
				score = -1; // �û�ѧ������
			}
			if (student != 0) // ���ο�������Ϊ0
			{
				for (int i = 0, j = scoreSectionSize - 1; i < 1000; i++) // ��һ��һ�α�����ȡÿһ�ֵ�����
				{
					if (scoreEvery[i] > 0) // ����ǰ��������������0
					{
						if (i < scoreSection[j]) // ����ǰ����С����Сֵ���򽫵�ǰ������������ӵ����һ��������
						{
							scoreNumber[j + 1] += scoreEvery[i];
						}
						else // ����ǰ����������Сֵ
						{
							while (j > 0 && i >= scoreSection[j - 1]) j--; // �����һ����������ǰ�Ƚϣ��ҵ��ʺϸ÷����ķ�����
							scoreNumber[j] += scoreEvery[i]; // �ҵ��󽫸÷�����������ӵ���Ӧ�ķ�����
						}
					}
				}
				for (int i = 0; i <= scoreSectionSize; i++) // ͨ��ÿ�������ε���������ÿ�������ε�ѧ������
				{
					scoreBatch[i] = 100 * (1.0 * scoreNumber[i]) / (1.0 * student);
				}
			}

		}

		// ���������ݵ�ָ��csv�ļ���
		excel2 << type << "," << student;
		for (auto n : scoreNumber) excel2 << "," << n;
		excel2 << endl;
		excel2 << ",";
		for (auto b : scoreBatch) excel2 << "," << fixed << setprecision(2) << b << "%";
		excel2 << endl;

		excel2.close(); // �ر������
	}
}

/********************************************************************************
Function: getExcel2
Description: ����ָ����ԭʼ���ݱ����ɷ�����XXXX��X�꼶���ģ����ַܷ���������������
Calls: chooseExcel
Table Accessed:
1. ����ܳɼ�.csv
2. �Ŀ��ܳɼ�.csv
3. �����ܳɼ�.csv
4. �����ܳɼ�.csv
Table Updated: XXXX��X�꼶���ģ����ַܷ���������������
Input:
1. string folderIntput: ԭʼ�������ڵ��ļ��еľ��Ե�ַ
2. string folderOutput�������������ڵ��ļ��еľ��Ե�ַ
3. string name: �˴ο��Ե����ֻ��߳ƺ�
4. string gradeS: �ο�ѧ�����꼶
Output: XXXX��X�꼶���ģ����ַܷ���������������
Return: true�������ݷ����ɹ���false�����ʧ��
Others: null
********************************************************************************/
bool getExcel2(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName2 = folderOutput + "\\" + name + "���ģ���" + "��" + gradeS + "�꼶�ַܷ���������������.csv";
	const char * excelNamec2 = excelName2.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	vector<double> scoreSection;
	
	double score = -1;
	double lscore = -1;
	while (true)
	{ 
		do {
			if (lscore != -1) cout << "��һ����������" << lscore;
			cout << "���������,��������ֱ����ǵ����ݼ���:" << endl;
			cin >> score;
			if (lscore == -1) lscore = score + 1;
		} while (lscore <= score) ;
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
		//for (auto a : scoreSection) cout << a;
		//cout << endl;
	}

	/*
	for (int i = 600; i >= 200; i-=50)
		scoreSection.push_back(i);
	for (auto a : scoreSection) cout << a;
		cout << endl;*/

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec2);
	ofstream excel2;
	excel2.open(excelNamec2, std::ios::out | std::ios::app);

	if (!excel2.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel2 << "����,�ο�����";
	for (auto ss : scoreSection) excel2 << ",>=" << ss;
	excel2 << ",<=" << scoreSection[scoreSection.size() - 1];

	excel2 << endl;

	excel2.close();

	// cout << file1 << endl;

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	string type = "";
	type = "���";
	getData2(excelNamec2, csv1, type, scoreSection);
	type = "�Ŀ�";
	getData2(excelNamec2, csv2, type, scoreSection);
	type = "����";
	getData2(excelNamec2, csv3, type, scoreSection);
	type = "����";
	getData2(excelNamec2, csv4, type, scoreSection);
	excel2.close();
	return true;
}