#include "stdafx.h"
#include "exam.h"

bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
}

void getData(const char * excelName, Csv csv, string type, double fristBatch, double secondBatch)
{
	if (csv.table[0][6].compare("总分") == 0)
	{
		ofstream excel1;
		excel1.open(excelName, std::ios::out | std::ios::app);
		int i = 0;
		int student = 0;
		int fristStudent = 0;
		int secondStudent = 0;
		double fristBatchDouble = 0;
		double secondBatchDouble = 0;
		for (i = 1; ((isNum(csv.table[i][6]) && (csv.table[i][6].compare(""))); i++)
		{
			if (atoi(csv.table[student][6].c_str()) >= fristBatch) fristStudent++;
			if (atoi(csv.table[student][6].c_str()) >= secondBatch) secondStudent++;
		}

		fristBatchDouble = 100.0 * (fristStudent * 1.0) / (student * 1.0);
		secondBatchDouble = 100.0 * (secondStudent * 1.0) / (student * 1.0);

		excel1 << type << "," << student << "," << fristStudent << ",";
		excel1 << fixed << setprecision(2) << fristBatchDouble << "%,";
		excel1 << secondStudent << ",";
		excel1 << fixed << setprecision(2) << secondBatchDouble << "%" << endl;
		excel1.close();

	}
}

string getExcel1(string folderIntput, string folderOutput, string name, string gradeS)
{
	string excelName1 = folderOutput + "\\" + name + "理（文）科" + "高" + gradeS + "年级一本人数与本科人数及比例.csv";
	const char * excelNamec1 = excelName1.c_str();
	
	string file1Intput = folderIntput + "\\理科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\文科总成绩.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\艺理总成绩.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\艺文总成绩.csv";
	const char * file4 = file4Intput.c_str();

	int scienceFirstBatch = 512;
	int scienceSecondBatch = 375;
	int artsFirstBatch = 561;
	int artsSecondBatch = 441;

	/*
	cout << "请输入一本线（理科）:";
	cin >> scienceFirstBatch;
	cout << "请输入本科线（理科）:";
	cin >> scienceSecondBatch;
	cout << "请输入一本线（文科）:";
	cin >> artsFirstBatch;
	cout << "请输入本科线（文科）:";
	cin >> artsSecondBatch;

	cout << "一本线（理科）：" << scienceFirstBatch << endl;
	cout << "本科线（理科）：" << scienceSecondBatch << endl;
	cout << "一本线（文科）：" << artsFirstBatch << endl;
	cout << "本科线（文科）：" << artsSecondBatch << endl;
*/

	remove(excelNamec1);
	ofstream excel1;
	excel1.open(excelNamec1, std::ios::out | std::ios::app);

	if (!excel1.is_open())
	{
		cout << "创建文件出错！" << endl;
		return "ERROR";
	}
	excel1 << "类型,参考人数,一本人数,比例,本科人数,比例" << endl;

	excel1.close();
	cout << file1 << endl;

	
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	string type = "";
	type = "理科";
	getData(excelNamec1, csv1, type, scienceFirstBatch, scienceSecondBatch);
	type = "文科";
	getData(excelNamec1, csv2, type, artsFirstBatch, artsSecondBatch);
	type = "艺理";
	getData(excelNamec1, csv3, type, scienceFirstBatch, scienceSecondBatch);
	type = "艺文";
	getData(excelNamec1, csv4, type, artsFirstBatch, artsSecondBatch);

	return " ";
}