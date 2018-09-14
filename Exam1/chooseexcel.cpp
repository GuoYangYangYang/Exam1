#include "stdafx.h"
#include "exam.h"

void chooseExcel(string file)
{
	string name;
	int name1 = file.find('\\') + 1;
	int name2 = file.find('理');
	name = file.substr(name1, name2 - name1 - 1);
	cout << name << endl;

	int grade = 0;
	string gradeS = "";
	int grade1 = (file.find("理（文）科高"));
	gradeS = file.substr(grade1 + 12, 2);

	if (gradeS == "一") grade = 1;
	if (gradeS == "二") grade = 2;
	if (gradeS == "三") grade = 3;
	
	string excelnameS = "";
	int excelnumber = 1;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "请选择分析类型，选择数字生成指定文件" << endl;
	
	vector<string> excelType;

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科一本和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科总分分数段人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级各班一本人数本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级各班成绩分数段人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级各班成绩平均分和标准差";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科单科一本人数和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理科各班单科一本人数和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级文科各班单科一本人数和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科各班单科成绩分数段人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	

	int type = 0;

}