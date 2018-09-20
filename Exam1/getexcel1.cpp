#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-20
Description: ��һ��XXXX��X�꼶���ģ���һ�������뱾������������
********************************************************************************/

/********************************************************************************
Function: getData
Description: ͳ��һ��csv���С��ܷ֡���һ�е�һ�����ͱ�����
Calls: getExcel1
Table Accessed: XXXX��X�꼶���ģ���һ�������뱾������������
Table Updated: XXXX��X�꼶���ģ���һ�������뱾������������
Input:
		1. const char * excelName: ���ݷ�����ľ��Ե�ַ
		2. Csv csv: �Ѿ�����õ�Csv�����ں�ԭʼ���ݱ�table
		3. string type: �˴η������ݵ����ͣ���Ҫ�У���ƣ��Ŀƣ��������� 
		4. double fristBatch: һ���߷���
		5. double secondBatch: �����߷���
Output: ��ָ��csv�ļ�����һ�з�������
Return: null
Others: null
********************************************************************************/
void getData(const char * excelName, Csv csv, string type, double fristBatch, double secondBatch)
{
	if (csv.table[0][6].compare("�ܷ�") == 0) // ���ԭʼ���ݱ��������Ƿ�Ϊ���ܷ֡�
	{
		ofstream excel1;
		excel1.open(excelName, std::ios::out | std::ios::app); // �򿪷����ļ�������

		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int student = 0; // ѧ����Ŀ
		int fristStudent = 0; // ��һ���ߵ�ѧ����Ŀ
		int secondStudent = 0; // �������ߵ�ѧ����Ŀ
		double fristBatchDouble = 0; // һ��ѧ������
		double secondBatchDouble = 0; // ����ѧ������

		if (!csv.table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			//cout << isNum(csv.table[i][6]) << csv.table[i][6].compare("") << endl;
			for (i = 1; (isNum(csv.table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				score = atoi(csv.table[i][6].c_str()); // ��¼��ǰѧ�����ܷ�
				if (score >= fristBatch) fristStudent++; // ��¼���������һ���ߵ�ѧ������
				if (score >= secondBatch) secondStudent++; // ��¼��������ڱ����ߵ�ѧ������
				if (score >= 0) student++; // ��¼�ο�ѧ������
				score = -1; // �û�ѧ������
			}
			if (student != 0) // ���ο�������Ϊ0
			{
				fristBatchDouble = 100.0 * (fristStudent * 1.0) / (student * 1.0); // ����һ��ѧ����ռ����
				secondBatchDouble = 100.0 * (secondStudent * 1.0) / (student * 1.0); // ���㱾��ѧ����ռ����
			}
			else // ���޲������ݣ���һ��ѧ�������ͱ���ѧ��������Ϊ0
			{
				fristBatchDouble = secondBatchDouble = 0;
			}
		}
		
		// ��������Ӧ�ķ������ݵ�ָ�������ļ���
		excel1 << type << "," << student << "," << fristStudent << ",";
		excel1 << fixed << setprecision(2) << fristBatchDouble << "%,";
		excel1 << secondStudent << ",";
		excel1 << fixed << setprecision(2) << secondBatchDouble << "%" << endl;

		excel1.close(); // �ر������
	}
}

/********************************************************************************
Function: getExcel1
Description: ����ָ����ԭʼ���ݱ����ɷ�����XXXX��X�꼶���ģ���һ�������뱾������������
Calls: chooseExcel
Table Accessed: 
		1. ����ܳɼ�.csv
		2. �Ŀ��ܳɼ�.csv
		3. �����ܳɼ�.csv
		4. �����ܳɼ�.csv
Table Updated: XXXX��X�꼶���ģ���һ�������뱾������������
Input: 
		1. string folderIntput: ԭʼ�������ڵ��ļ��еľ��Ե�ַ
		2. string folderOutput�������������ڵ��ļ��еľ��Ե�ַ
		3. string name: �˴ο��Ե����ֻ��߳ƺ�
		4. string gradeS: �ο�ѧ�����꼶
Output: XXXX��X�꼶���ģ���һ�������뱾������������
Return: true�������ݷ����ɹ���false�����ʧ��
Others: null
********************************************************************************/
bool getExcel1(string folderIntput, string folderOutput, string name, string gradeS)
{
	// ���ݷ�������ļ��ľ���·��
	string excelName1 = folderOutput + "\\" + name + "���ģ���" + "��" + gradeS + "�꼶һ�������뱾������������.csv";
	const char * excelNamec1 = excelName1.c_str();
	
	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Intput = folderIntput + "\\����ܳɼ�.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Intput.c_str();

	int scienceFristBatch = 512; // ���һ��������
	int scienceSecondBatch = 375; // ��Ʊ��Ʒ�����
	int artsFristBatch = 561; // �Ŀ�һ��������
	int artsSecondBatch = 441; // �ĿƱ��Ʒ�����

	// ���������
	cout << "������һ���ߣ���ƣ�:";
	cin >> scienceFristBatch;
	cout << "�����뱾���ߣ���ƣ�:";
	cin >> scienceSecondBatch;
	cout << "������һ���ߣ��Ŀƣ�:";
	cin >> artsFristBatch;
	cout << "�����뱾���ߣ��Ŀƣ�:";
	cin >> artsSecondBatch;

	// ��ʾ������
	cout << "һ���ߣ���ƣ���" << scienceFristBatch << endl;
	cout << "�����ߣ���ƣ���" << scienceSecondBatch << endl;
	cout << "һ���ߣ��Ŀƣ���" << artsFristBatch << endl;
	cout << "�����ߣ��Ŀƣ���" << artsSecondBatch << endl;

	// ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec1);
	ofstream excel1;
	excel1.open(excelNamec1, std::ios::out | std::ios::app);

	if (!excel1.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel1 << "����,�ο�����,һ������,����,��������,����" << endl;

	excel1.close();

	// cout << file1 << endl;

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// ������������
	string type = "";
	type = "���";
	getData(excelNamec1, csv1, type, scienceFristBatch, scienceSecondBatch); // ��������ܳɼ�
	type = "�Ŀ�";
	getData(excelNamec1, csv2, type, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�
	type = "����";
	getData(excelNamec1, csv3, type, scienceFristBatch, scienceSecondBatch); // ���������ܳɼ�
	type = "����";
	getData(excelNamec1, csv4, type, artsFristBatch, artsSecondBatch); // ���������ܳɼ�

	// ���������з����ߵ������ļ���
	excel1.open(excelNamec1, std::ios::out | std::ios::app);
	excel1 << endl;
	excel1 << "ע,һ����,������" << endl;
	excel1 << "���," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel1 << "�Ŀ�," << artsFristBatch << "," << artsSecondBatch << endl;

	excel1.close(); 
	return true;
}