#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-20
Description: �����XXXX��X�꼶���ģ����ַܷ���������������
********************************************************************************/

Excel2::Excel2(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel2::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
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
1. string folderInput: ԭʼ�������ڵ��ļ��еľ��Ե�ַ
2. string folderOutput�������������ڵ��ļ��еľ��Ե�ַ
3. string name: �˴ο��Ե����ֻ��߳ƺ�
4. string gradeS: �ο�ѧ�����꼶
Output: XXXX��X�꼶���ģ����ַܷ���������������
Return: true�������ݷ����ɹ���false�����ʧ��
Others: null
********************************************************************************/
bool Excel2::getExcel()
{
	Exam().clear();
	// ���ݷ�������ļ��ľ���·��
	string excelName2 = folderOutput + "\\" + "�����" + name + "���ģ���" + "��" + gradeS + "�꼶�ַܷ���������������.csv";
	const char * excelNamec2 = excelName2.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Input = folderInput + "\\����ܳɼ�.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Input.c_str();

	// ���������
	vector<int> scoreSection;
	
	int score = -1;
	int lscore = -1;
	while (true)
	{ 
		do {
			if (lscore != -1) cout << "��һ����������" << lscore;
			cout << "���������,��������ֱ����ǵ����ݼ���,";
			
			if (lscore == -1) {
				score = Exam().inputInteger(0, MaxScore);
				lscore = score + 1;
			}
			else
			{
				score = Exam().inputInteger(0, lscore - 1);
			}
		} while (lscore <= score) ;
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
	}

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

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	string type = "";
	type = "���";
	getData(excelNamec2, csv1, type, scoreSection);
	type = "�Ŀ�";
	getData(excelNamec2, csv2, type, scoreSection);
	type = "����";
	getData(excelNamec2, csv3, type, scoreSection);
	type = "����";
	getData(excelNamec2, csv4, type, scoreSection);

	Exam().clear();
	cout << "�������ļ�����ַ���£������ҵĵ����д��ļ�����1������" << endl;
	cout << excelNamec2 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}


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
4. vector<int> scoreSection: ÿ��Ԫ��Ϊ��������ÿ�εķ���
Output: ��ָ��csv�ļ�����һ�з�������
Return: null
Others: null
********************************************************************************/
void Excel2::getData(const char * excelName, Csv &csv, string type, vector<int> scoreSection)
{
	vector<vector<string>> &table = csv.getTable();
	if (table[0][6].compare("�ܷ�") == 0) // ���ԭʼ���ݱ��������Ƿ�Ϊ���ܷ֡�
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

		if (!table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				score = (int)ceill(atof(table[i][6].c_str())); // ��¼��ǰѧ�����ܷ�
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