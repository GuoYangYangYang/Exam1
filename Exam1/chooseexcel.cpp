#include "stdafx.h"
#include "exam.h"

bool Exam::chooseExcel(string folder)
{

	string Folder = folder;
	if (Folder.empty()) return false;
	if (!Folder.compare("")) return false;

	string name;
	int name1 = Folder.find_last_of("\\") + 1;
	int name2 = Folder.find_last_of("理");
	name = Folder.substr(name1, name2 - name1 - 1);

	int grade = 0;
	string gradeS = "";
	int grade1 = (Folder.find("理（文）科高"));
	gradeS = Folder.substr(grade1 + 12, 2);

	if (gradeS == "一") grade = 1;
	if (gradeS == "二") grade = 2;
	if (gradeS == "三") grade = 3;
	
	string excelnameS = "";
	int excelnumber = 1;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "请选择分析类型，选择数字生成指定文件" << endl;
	
	vector<string> excelType;
	vector<string> initExcelType = { 
		"年级理（文）科一本和本科人数及比例",
		"年级理（文）科总分分数段人数及比例",
		"年级各班一本人数本科人数及比例",
		"年级各班成绩分数段人数及比例",
		"年级各班成绩平均分和标准差",
		"年级理（文）科单科一本人数和本科人数及比例",
		"年级理科各班单科一本人数和本科人数及比例",
		"年级文科各班单科一本人数和本科人数及比例",
		"年级理（文）科各班单科成绩分数段人数及比例"
	};

	for (excelnumber = 1; excelnumber <= (int)initExcelType.size(); excelnumber++)
	{
		cout << "---+-----------------------------------------------------------------------------------------------" << endl;
		excelnameS = name + "高" + gradeS + initExcelType[excelnumber - 1];
		cout << setw(3) << setfill(' ') << excelnumber;
		cout << "|" << excelnameS << endl;
		excelType.push_back(excelnameS);
	}

	cout << "---------------------------------------------------------------------------------------------------" << endl;

	string rootD = root;
	string fileOutput = rootD + "\\成绩分析\\" + name + "理（文）科高" + gradeS + "年级所有科目总成绩";

	int type = 0;
	type = inputInteger(1, 9);

	getExcel(Folder, fileOutput, name, gradeS, type);

	return true;
}