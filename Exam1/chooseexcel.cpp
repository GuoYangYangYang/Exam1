#include "stdafx.h"
#include "exam.h"

void chooseExcel(string file)
{
	string name;
	int name1 = file.find('\\') + 1;
	int name2 = file.find('��');
	name = file.substr(name1, name2 - name1 - 1);
	cout << name << endl;

	int grade = 0;
	string gradeS = "";
	int grade1 = (file.find("���ģ��Ƹ�"));
	gradeS = file.substr(grade1 + 12, 2);

	if (gradeS == "һ") grade = 1;
	if (gradeS == "��") grade = 2;
	if (gradeS == "��") grade = 3;
	
	string excelnameS = "";
	int excelnumber = 1;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "��ѡ��������ͣ�ѡ����������ָ���ļ�" << endl;
	
	vector<string> excelType;

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ���һ���ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ����ַܷ���������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶����һ��������������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶����ɼ�����������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶����ɼ�ƽ���ֺͱ�׼��";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ��Ƶ���һ�������ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶��Ƹ��൥��һ�������ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶�ĿƸ��൥��һ�������ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ��Ƹ��൥�Ƴɼ�����������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	

	int type = 0;

}