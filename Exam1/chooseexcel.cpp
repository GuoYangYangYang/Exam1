#include "stdafx.h"
#include "exam.h"

bool Exam::chooseExcel(string folder)
{
	if (folder.empty()) return false;
	if (!folder.compare("")) return false;

	string name;
	int name1 = folder.find('\\') + 1;
	int name2 = folder.find('��');
	name = folder.substr(name1, name2 - name1 - 1);

	int grade = 0;
	string gradeS = "";
	int grade1 = (folder.find("���ģ��Ƹ�"));
	gradeS = folder.substr(grade1 + 12, 2);

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

	for (excelnumber = 1; excelnumber <= initExcelType.size(); excelnumber++)
	{
		cout << "---+-----------------------------------------------------------------------------------------------" << endl;
		excelnameS = name + "��" + gradeS + initExcelType[excelnumber - 1];
		cout << setw(3) << setfill(' ') << excelnumber;
		cout << "|" << excelnameS << endl;
		excelType.push_back(excelnameS);
	}

	cout << "---------------------------------------------------------------------------------------------------" << endl;

	string fileOutput = "D://�ɼ�����\\" + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";

	int type = 0;
	type = inputInteger(1, 9);

	getExcel(folder, fileOutput, name, gradeS, type);

	return true;
}