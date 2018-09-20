#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-20
Description: 表一：XXXX高X年级理（文）科一本人数与本科人数及比例
********************************************************************************/

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
	if (csv.table[0][6].compare("总分") == 0) // 检测原始数据表格第六列是否为“总分”
	{
		ofstream excel1;
		excel1.open(excelName, std::ios::out | std::ios::app); // 打开分析文件数据流

		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int student = 0; // 学生数目
		int fristStudent = 0; // 过一本线的学生数目
		int secondStudent = 0; // 过本科线的学生数目
		double fristBatchDouble = 0; // 一本学生比例
		double secondBatchDouble = 0; // 本科学生比例

		if (!csv.table.empty()) // 如果原始数据表格不为空
		{
			//cout << isNum(csv.table[i][6]) << csv.table[i][6].compare("") << endl;
			for (i = 1; (isNum(csv.table[i][6])); i++) // 当行第六列的数据为数字时
			{
				score = atoi(csv.table[i][6].c_str()); // 记录当前学生的总分
				if (score >= fristBatch) fristStudent++; // 记录超过或等于一本线的学生人数
				if (score >= secondBatch) secondStudent++; // 记录超过或等于本科线的学生人数
				if (score >= 0) student++; // 记录参考学生人数
				score = -1; // 置回学生分数
			}
			if (student != 0) // 若参考人数不为0
			{
				fristBatchDouble = 100.0 * (fristStudent * 1.0) / (student * 1.0); // 计算一本学生所占比例
				secondBatchDouble = 100.0 * (secondStudent * 1.0) / (student * 1.0); // 计算本科学生所占比例
			}
			else // 若无参数数据，则将一本学生比例和本科学生比例置为0
			{
				fristBatchDouble = secondBatchDouble = 0;
			}
		}
		
		// 最后输出相应的分析数据到指定分析文件中
		excel1 << type << "," << student << "," << fristStudent << ",";
		excel1 << fixed << setprecision(2) << fristBatchDouble << "%,";
		excel1 << secondStudent << ",";
		excel1 << fixed << setprecision(2) << secondBatchDouble << "%" << endl;

		excel1.close(); // 关闭输出流
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
		1. string folderIntput: 原始数据所在的文件夹的绝对地址
		2. string folderOutput：分析数据所在的文件夹的绝对地址
		3. string name: 此次考试的名字或者称号
		4. string gradeS: 参考学生的年级
Output: XXXX高X年级理（文）科一本人数与本科人数及比例
Return: true代表数据分析成功，false则代表失败
Others: null
********************************************************************************/
bool getExcel1(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName1 = folderOutput + "\\" + name + "理（文）科" + "高" + gradeS + "年级一本人数与本科人数及比例.csv";
	const char * excelNamec1 = excelName1.c_str();
	
	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Intput = folderIntput + "\\理科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\文科总成绩.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\艺理总成绩.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\艺文总成绩.csv";
	const char * file4 = file4Intput.c_str();

	int scienceFristBatch = 512; // 理科一本分数线
	int scienceSecondBatch = 375; // 理科本科分数线
	int artsFristBatch = 561; // 文科一本分数线
	int artsSecondBatch = 441; // 文科本科分数线

	// 输入分数线
	cout << "请输入一本线（理科）:";
	cin >> scienceFristBatch;
	cout << "请输入本科线（理科）:";
	cin >> scienceSecondBatch;
	cout << "请输入一本线（文科）:";
	cin >> artsFristBatch;
	cout << "请输入本科线（文科）:";
	cin >> artsSecondBatch;

	// 显示分数线
	cout << "一本线（理科）：" << scienceFristBatch << endl;
	cout << "本科线（理科）：" << scienceSecondBatch << endl;
	cout << "一本线（文科）：" << artsFristBatch << endl;
	cout << "本科线（文科）：" << artsSecondBatch << endl;

	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec1);
	ofstream excel1;
	excel1.open(excelNamec1, std::ios::out | std::ios::app);

	if (!excel1.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel1 << "类型,参考人数,一本人数,比例,本科人数,比例" << endl;

	excel1.close();

	// cout << file1 << endl;

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	string type = "";
	type = "理科";
	getData(excelNamec1, csv1, type, scienceFristBatch, scienceSecondBatch); // 分析理科总成绩
	type = "文科";
	getData(excelNamec1, csv2, type, artsFristBatch, artsSecondBatch); // 分析文科总成绩
	type = "艺理";
	getData(excelNamec1, csv3, type, scienceFristBatch, scienceSecondBatch); // 分析艺理总成绩
	type = "艺文";
	getData(excelNamec1, csv4, type, artsFristBatch, artsSecondBatch); // 分析艺文总成绩

	// 最后输出所有分数线到分析文件中
	excel1.open(excelNamec1, std::ios::out | std::ios::app);
	excel1 << endl;
	excel1 << "注,一本线,本科线" << endl;
	excel1 << "理科," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel1 << "文科," << artsFristBatch << "," << artsSecondBatch << endl;

	excel1.close(); 
	return true;
}