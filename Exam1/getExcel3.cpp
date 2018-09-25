#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-20
Description: ������XXXX��X�꼶����һ�������뱾������������
********************************************************************************/

/* �༶����ͳ����Ϣ */
typedef struct ClassData
{
	string className; /* �༶���� */
	int allNumber; /* �༶�ο����� */
	int fristNumber; /* ��һ�������� */
	int secondNumber; /* ������������ */
	bool SorA; /* ���ƻ����Ŀƣ� */
} ClassData;

/********************************************************************************
Function: initClass3
Description: ���༶��Ϣ�Ƿ���ڣ������������ʼ���༶��Ϣ
Calls: getData3
Table Accessed: null
Table Updated: null
Input:
1. vector<ClassData> &Class: ����ͳ�Ʊ�
2. string gradeS: ѧ���꼶
3. string classS: ѧ���༶
Output: ��Class����һ�а༶��ʼ����
Return: �༶����
Others: null
********************************************************************************/
int initClass3(vector<ClassData> &Class, string gradeS, string classS)
{
	classS = classS.substr(2, 2);
	if (isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN > Class.size()) // ���༶���볬���������ݱ�������������г�ʼ����ֱ���༶����������ݱ��������
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				string className = "��" + gradeS + "��";
				className += to_string(ClassN + 1);
				className += "��";
				ClassData classNew = {className, 0, 0, 0, true}; // ��ʼ�����ݱ���Ĭ��Ϊ�����ơ�
				Class.push_back(classNew);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

/********************************************************************************
Function: getData3
Description: ������ǰ�����������ݣ�ͳ�Ʋο�������һ�������ͱ�������
Calls: getExcel3
Table Accessed: null
Table Updated: null
Input:
		1. Csv csv: �Ѿ������õ�Csv�����ں�ԭʼ���ݱ�table
		2. vector<ClassData> &Class: ��ʱ���ݷ�����
		3. double fristBatch: һ���߷���
		4. double secondBatch: �����߷���
Output: ������ο�������һ�������ͱ�������ͳ�Ƶ���ʱ���ݷ�������
Return: null
Others: null
********************************************************************************/
void getData3(Csv csv, vector<ClassData> &Class, string gradeS, double fristBatch, double secondBatch)
{
	// ���ԭʼ���ݱ���������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((csv.table[0][3].compare("����") == 0) && (csv.table[0][4].compare("�༶") == 0) && (csv.table[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶

		if (!csv.table.empty()) // ���ԭʼ���ݱ���Ϊ��
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass3(Class, gradeS, csv.table[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					if (!csv.table[i][3].compare("����")) Class[classN - 1].SorA = true; // ������Ϊtrue
					else Class[classN - 1].SorA = false; // �Ŀ���Ϊfalse
					score = atoi(csv.table[i][6].c_str()); // ��ȡ��ǰѧ������
					if (score >= 0) Class[classN - 1].allNumber++; // ѧ��������Ч����ο�������һ
					if (score >= secondBatch) Class[classN - 1].secondNumber++; // �ɼ��ﵽ�����ߣ��򱾿�������һ
					if (score >= fristBatch) Class[classN - 1].fristNumber++; // �ɼ��ﵽһ���ߣ���һ��������һ
				}
			}
		}
	}
}

/********************************************************************************
Function: getExcel3
Description: ����ָ����ԭʼ���ݱ����ɷ�������XXXX��X�꼶����һ�������뱾������������
Calls: chooseExcel
Table Accessed:
1. �����ܳɼ�.csv
2. �Ŀ��ܳɼ�.csv
3. �����ܳɼ�.csv
4. �����ܳɼ�.csv
Table Updated: XXXX��X�꼶����һ�������뱾������������
Input:
1. string folderIntput: ԭʼ�������ڵ��ļ��еľ��Ե�ַ
2. string folderOutput�������������ڵ��ļ��еľ��Ե�ַ
3. string name: �˴ο��Ե����ֻ��߳ƺ�
4. string gradeS: �ο�ѧ�����꼶
Output: XXXX��X�꼶�����ģ����ַܷ���������������
Return: true�������ݷ����ɹ���false�����ʧ��
Others: null
********************************************************************************/
bool getExcel3(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName3 = folderOutput + "\\" + name + "��" + gradeS + "�꼶����һ�������뱾������������.csv";
	const char * excelNamec3 = excelName3.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ�������ƣ��Ŀƣ�����������
	string file1Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	int scienceFristBatch = 512; // ����һ��������
	int scienceSecondBatch = 375; // ���Ʊ��Ʒ�����
	int artsFristBatch = 561; // �Ŀ�һ��������
	int artsSecondBatch = 441; // �ĿƱ��Ʒ�����

	// ���������
	cout << "������һ���ߣ����ƣ�:";
	cin >> scienceFristBatch;
	cout << "�����뱾���ߣ����ƣ�:";
	cin >> scienceSecondBatch;
	cout << "������һ���ߣ��Ŀƣ�:";
	cin >> artsFristBatch;
	cout << "�����뱾���ߣ��Ŀƣ�:";
	cin >> artsSecondBatch;

	// ��ʾ������
	cout << "һ���ߣ����ƣ���" << scienceFristBatch << endl;
	cout << "�����ߣ����ƣ���" << scienceSecondBatch << endl;
	cout << "һ���ߣ��Ŀƣ���" << artsFristBatch << endl;
	cout << "�����ߣ��Ŀƣ���" << artsSecondBatch << endl;

	// ��ԭ�����ĸ�����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// �༶��Ϣ
	vector<ClassData> Class;

	// ������������
	getData3(csv1, Class, gradeS, scienceFristBatch, scienceSecondBatch); // ���������ܳɼ�
	getData3(csv2, Class, gradeS, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�
	getData3(csv3, Class, gradeS, scienceFristBatch, scienceSecondBatch); // ���������ܳɼ�
	getData3(csv4, Class, gradeS, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec3);
	ofstream excel3;
	excel3.open(excelNamec3, std::ios::out | std::ios::app);

	if (!excel3.is_open())
	{
		cout << "�����ļ�������" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel3 << "�༶,�ο�����,һ������,����,��������,����,��/��" << endl;

	// for (auto c : Class) cout << c.className << ' ' << c.allNumber << ' ' << c.fristNumber << ' ' << c.secondNumber << ' ' << c.SorA << endl;

	// ����ʱ���ݷ�������������ݵ�csv����
	for (auto c : Class)
	{
		if (c.allNumber != 0)
		{
			excel3 << c.className << "," << c.allNumber << "," << c.fristNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.fristNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			excel3 << "," << c.secondNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.secondNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			if (c.SorA) excel3 << ",����" << endl;
			else excel3 << ",�Ŀ�" << endl;
		}
	}

	// ������һ�������Ŀ��ߺͱ��������Ŀ���
	excel3 << endl;
	excel3 << "ע,һ����,������" << endl;
	excel3 << "����," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel3 << "�Ŀ�," << artsFristBatch << "," << artsSecondBatch << endl;

	excel3.close();
	return true;
}