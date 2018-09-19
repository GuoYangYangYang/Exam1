#include "stdafx.h"
#include "exam.h"
/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-19
Description: 表一：XXXX高X年级理（文）科一本人数与本科人数及比例
********************************************************************************/

/********************************************************************************
********************************************************************************/

/********************************************************************************
Function: isNum
Description: 判断一个字符串是否可以被转化为数字
Calls: getExcel1
Table Accessed: null
Table Updated: null
Input: 简单的字符串
Output: null
Return: true代表字符串可以转化为数字，false则不能
Others: null
********************************************************************************/
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

/********************************************************************************
Function: getData
Description: 统计一个csv表中“总分”这一列的一本数和本科数
Calls: getExcel1
Table Accessed: XXXX高X年级理（文）科一本人数与本科人数及比例
Table Updated: XXXX高X年级理（文）科一本人数与本科人数及比例
Input:
		1. const char * excelName: 数据分析表的绝对地址
		2. Csv csv: 已经处理好的Csv对象，内含原始数据表table
		3. string type: 此次分析数据的类型，主要有：理科，文科，艺理，艺文 
		4. double fristBatch: 一本线分数
		5. double secondBatch: 本科线分数
Output: 在指定csv文件生成一行分析数据
Return: null
Others: null
********************************************************************************/
void getData(const char * excelName, Csv csv, string type, double fristBatch, double secondBatch)
{
	if (csv.table[0][6].compare("总分") == 0)
	{
		ofstream excel1;
		excel1.open(excelName, std::ios::out | std::ios::app);
		int i = 1;
		int score = -1;
		int student = 0;
		int fristStudent = 0;
		int secondStudent = 0;
		double fristBatchDouble = 0;
		double secondBatchDouble = 0;
		if (!csv.table.empty())
		{
			cout << isNum(csv.table[i][6]) << csv.table[i][6].compare("") << endl;
			for (i = 1; (isNum(csv.table[i][6])); i++)
			{
				score = atoi(csv.table[i][6].c_str());
				if (score >= fristBatch) fristStudent++;
				if (score >= secondBatch) secondStudent++;
				if (score >= 0) student++;
				score = -1;
			}
			if (student != 0)
			{
				fristBatchDouble = 100.0 * (fristStudent * 1.0) / (student * 1.0);
				secondBatchDouble = 100.0 * (secondStudent * 1.0) / (student * 1.0);
			}
			else
			{
				fristBatchDouble = secondBatchDouble = 0;
			}
		}
		
		excel1 << type << "," << student << "," << fristStudent << ",";
		excel1 << fixed << setprecision(2) << fristBatchDouble << "%,";
		excel1 << secondStudent << ",";
		excel1 << fixed << setprecision(2) << secondBatchDouble << "%" << endl;

		excel1.close();
	}
}

/********************************************************************************
Function: getExcel1
Description: 根据指定的原始数据表生成分析表：XXXX高X年级理（文）科一本人数与本科人数及比例
Calls: chooseExcel
Table Accessed: 
		1. 理科总成绩.csv
		2. 文科总成绩.csv
		3. 艺理总成绩.csv
		4. 艺文总成绩.csv
Table Updated: XXXX高X年级理（文）科一本人数与本科人数及比例
Input: 
		1. string folderIntput: 原创数据所在的文件夹的绝对地址
		2. string folderOutput：分析数据所在的文件夹的绝对地址
		3. string name: 此次考试的名字或者称号
		4. string gradeS: 参考学生的年级
Output: XXXX高X年级理（文）科一本人数与本科人数及比例
Return: true代表数据分析成功，false则代表失败
Others: null
********************************************************************************/
bool getExcel1(string folderIntput, string folderOutput, string name, string gradeS)
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

	int scienceFristBatch = 512;
	int scienceSecondBatch = 375;
	int artsFristBatch = 561;
	int artsSecondBatch = 441;

	/*
	cout << "请输入一本线（理科）:";
	cin >> scienceFristBatch;
	cout << "请输入本科线（理科）:";
	cin >> scienceSecondBatch;
	cout << "请输入一本线（文科）:";
	cin >> artsFristBatch;
	cout << "请输入本科线（文科）:";
	cin >> artsSecondBatch;

	cout << "一本线（理科）：" << scienceFristBatch << endl;
	cout << "本科线（理科）：" << scienceSecondBatch << endl;
	cout << "一本线（文科）：" << artsFristBatch << endl;
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
	getData(excelNamec1, csv1, type, scienceFristBatch, scienceSecondBatch);
	type = "文科";
	getData(excelNamec1, csv2, type, artsFristBatch, artsSecondBatch);
	type = "艺理";
	getData(excelNamec1, csv3, type, scienceFristBatch, scienceSecondBatch);
	type = "艺文";
	getData(excelNamec1, csv4, type, artsFristBatch, artsSecondBatch);

	excel1.open(excelNamec1, std::ios::out | std::ios::app);
	excel1 << endl;
	excel1 << "注,一本线,本科线" << endl;
	excel1 << "理科," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel1 << "文科," << artsFristBatch << "," << artsSecondBatch << endl;
	excel1.close();

	return true;
}