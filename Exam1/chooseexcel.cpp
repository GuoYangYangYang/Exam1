#include "stdafx.h"
#include "exam.h"

bool Exam::chooseExcel(string folder)
{

	string Folder = folder;
	if (Folder.empty()) return false;
	if (!Folder.compare("")) return false;

	string name;
	int name1 = Folder.find_last_of("\\") + 1;
	int name2 = Folder.find_last_of("��");
	name = Folder.substr(name1, name2 - name1 - 1);

	int grade = 0;
	string gradeS = "";
	int grade1 = (Folder.find("���ģ��Ƹ�"));
	gradeS = Folder.substr(grade1 + 12, 2);

	if (gradeS == "һ") grade = 1;
	if (gradeS == "��") grade = 2;
	if (gradeS == "��") grade = 3;
	
	string excelnameS = "";
	int excelnumber = 1;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "��ѡ��������ͣ�ѡ����������ָ���ļ�" << endl;
	
	vector<string> excelType;
	vector<string> initExcelType = { 
		"�꼶���ģ���һ���ͱ�������������",
		"�꼶���ģ����ַܷ���������������",
		"�꼶����һ��������������������",
		"�꼶����ɼ�����������������",
		"�꼶����ɼ�ƽ���ֺͱ�׼��",
		"�꼶���ģ��Ƶ���һ�������ͱ�������������",
		"�꼶��Ƹ��൥��һ�������ͱ�������������",
		"�꼶�ĿƸ��൥��һ�������ͱ�������������",
		"�꼶���ģ��Ƹ��൥�Ƴɼ�����������������"
	};

	for (excelnumber = 1; excelnumber <= (int)initExcelType.size(); excelnumber++)
	{
		cout << "---+-----------------------------------------------------------------------------------------------" << endl;
		excelnameS = name + "��" + gradeS + initExcelType[excelnumber - 1];
		cout << setw(3) << setfill(' ') << excelnumber;
		cout << "|" << excelnameS << endl;
		excelType.push_back(excelnameS);
	}

	cout << "---------------------------------------------------------------------------------------------------" << endl;

	string rootD = root;
	string fileOutput = rootD + "\\�ɼ�����\\" + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";

	int type = 0;
	type = inputInteger(1, 9);

	getExcel(Folder, fileOutput, name, gradeS, type);

	return true;
}