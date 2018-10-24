#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: ������
Last Date: 2018-9-20
Description: ������XXXX��X�꼶����һ�������뱾������������
********************************************************************************/

Excel3::Excel3(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel3::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

/********************************************************************************
Function: getExcel3
Description: ����ָ����ԭʼ���ݱ����ɷ�����XXXX��X�꼶����һ�������뱾������������
Calls: chooseExcel
Table Accessed:
1. ����ܳɼ�.csv
2. �Ŀ��ܳɼ�.csv
3. �����ܳɼ�.csv
4. �����ܳɼ�.csv
Table Updated: XXXX��X�꼶����һ�������뱾������������
Input:
1. string folderInput: ԭʼ�������ڵ��ļ��еľ��Ե�ַ
2. string folderOutput�������������ڵ��ļ��еľ��Ե�ַ
3. string name: �˴ο��Ե����ֻ��߳ƺ�
4. string gradeS: �ο�ѧ�����꼶
Output: XXXX��X�꼶���ģ����ַܷ���������������
Return: true�������ݷ����ɹ���false�����ʧ��
Others: null
********************************************************************************/
bool Excel3::getExcel()
{
	Exam().clear();

	// ���ݷ�������ļ��ľ���·��
	string excelName3 = folderOutput + "\\" + "������" + name + "��" + gradeS + "�꼶����һ�������뱾������������.csv";
	const char * excelNamec3 = excelName3.c_str();

	// ԭʼ���������ļ��ľ���·�������ĸ����ֱ������ƣ��Ŀƣ���������
	string file1Input = folderInput + "\\����ܳɼ�.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\�Ŀ��ܳɼ�.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\�����ܳɼ�.csv";
	const char * file4 = file4Input.c_str();

	int scienceFristBatch = 512; // ���һ��������
	int scienceSecondBatch = 375; // ��Ʊ��Ʒ�����
	int artsFristBatch = 561; // �Ŀ�һ��������
	int artsSecondBatch = 441; // �ĿƱ��Ʒ�����

							   // ���������
	cout << "������һ���ߣ���ƣ�:";
	scienceFristBatch = Exam().inputInteger(0, MaxScienceScore);
	cout << "�����뱾���ߣ���ƣ�:";
	scienceSecondBatch = Exam().inputInteger(0, scienceFristBatch - 1);
	cout << "������һ���ߣ��Ŀƣ�:";
	artsFristBatch = Exam().inputInteger(0, MaxArtsScore);
	cout << "�����뱾���ߣ��Ŀƣ�:";
	artsSecondBatch = Exam().inputInteger(0, artsFristBatch - 1);

	Exam().clear();

	// ��ʾ������
	cout << "һ���ߣ���ƣ���" << scienceFristBatch << endl;
	cout << "�����ߣ���ƣ���" << scienceSecondBatch << endl;
	cout << "һ���ߣ��Ŀƣ���" << artsFristBatch << endl;
	cout << "�����ߣ��Ŀƣ���" << artsSecondBatch << endl;

	cout << "����1����������" << endl;
	while (Exam().inputInteger(1) != 1);

	// ��ԭ�����ĸ����ȡ����ѧ�����ݵ��ڴ��У���������Ӧ��Csv����
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// �༶��Ϣ
	vector<ClassData> Class;

	// ������������
	getData(csv1, Class, gradeS, scienceFristBatch, scienceSecondBatch); // ��������ܳɼ�
	getData(csv2, Class, gradeS, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�
	getData(csv3, Class, gradeS, scienceFristBatch, scienceSecondBatch); // ��������ܳɼ�
	getData(csv4, Class, gradeS, artsFristBatch, artsSecondBatch); // �����Ŀ��ܳɼ�

																   // ɾ��ԭ�����ļ��������µ����ݷ����ļ�������
	remove(excelNamec3);
	ofstream excel3;
	excel3.open(excelNamec3, std::ios::out | std::ios::app);

	if (!excel3.is_open())
	{
		cout << "�����ļ�����" << endl;
		return false;
	}

	// ��ʼ�����ݷ�����
	excel3 << "�༶,�ο�����,һ������,����,��������,����,��/��" << endl;

	// ����ʱ���ݷ�������������ݵ�csv����
	for (auto c : Class)
	{
		if (c.allNumber != 0)
		{
			excel3 << c.className << "," << c.allNumber << "," << c.fristNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.fristNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			excel3 << "," << c.secondNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.secondNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			if (c.SorA) excel3 << ",���" << endl;
			else excel3 << ",�Ŀ�" << endl;
		}
	}

	// ������һ������Ŀ��ߺͱ�������Ŀ���
	excel3 << endl;
	excel3 << "ע,һ����,������" << endl;
	excel3 << "���," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel3 << "�Ŀ�," << artsFristBatch << "," << artsSecondBatch << endl;

	excel3.close();

	Exam().clear();
	cout << "�������ļ�����ַ���£������ҵĵ����д��ļ�����1������" << endl;
	cout << excelNamec3 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

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
int Excel3::initClass(vector<ClassData> &Class, string gradeS, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // ���༶�����Ƿ�Ϸ�
	{
		int classN = atoi(classS.c_str()); // ��ȡ�༶����
		if (classN > (int)Class.size()) // ���༶���볬���������ݱ������������г�ʼ����ֱ���༶����������ݱ��������
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				string className = "��" + gradeS + "��";
				className += to_string(ClassN + 1);
				className += "��";
				ClassData classNew = {className, 0, 0, 0, true}; // ��ʼ�����ݱ�Ĭ��Ϊ����ơ�
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
		1. Csv csv: �Ѿ�����õ�Csv�����ں�ԭʼ���ݱ�table
		2. vector<ClassData> &Class: ��ʱ���ݷ�����
		3. double fristBatch: һ���߷���
		4. double secondBatch: �����߷���
Output: ������ο�������һ�������ͱ�������ͳ�Ƶ���ʱ���ݷ�������
Return: null
Others: null
********************************************************************************/
void Excel3::getData(Csv csv, vector<ClassData> &Class, string gradeS, double fristBatch, double secondBatch)
{
	auto table = csv.getTable();
	// ���ԭʼ���ݱ��������Ƿ�Ϊ���༶���͵������Ƿ�Ϊ���ܷ֡�
	if ((table[0][3].compare("����") == 0) && (table[0][4].compare("�༶") == 0) && (table[0][6].compare("�ܷ�") == 0))
	{
		int i = 1; // ����
		int score = -1; // ��ǰѧ���ķ���
		int classN = -1; // ��ǰѧ���İ༶

		if (!table.empty()) // ���ԭʼ���ݱ��Ϊ��
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // ���е����е�����Ϊ����ʱ
			{
				classN = initClass(Class, gradeS, table[i][4]); // ��ȡ�༶���룬�����ݱ��в���������г�ʼ��
				if (classN != -1)
				{
					if (!table[i][3].compare("���")) Class[classN - 1].SorA = true; // �����Ϊtrue
					else Class[classN - 1].SorA = false; // �Ŀ���Ϊfalse
					score = (int)ceill(atoi(table[i][6].c_str())); // ��ȡ��ǰѧ������
					if (score >= 0) Class[classN - 1].allNumber++; // ѧ��������Ч����ο�������һ
					if (score >= secondBatch) Class[classN - 1].secondNumber++; // �ɼ��ﵽ�����ߣ��򱾿�������һ
					if (score >= fristBatch) Class[classN - 1].fristNumber++; // �ɼ��ﵽһ���ߣ���һ��������һ
				}
			}
		}
	}
}