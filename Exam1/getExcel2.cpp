#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-20
Description: 表二：XXXX高X年级理（文）科总分分数段人数及比例
********************************************************************************/

Excel2::Excel2(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel2::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

/********************************************************************************
Function: getExcel2
Description: 根据指定的原始数据表生成分析表：XXXX高X年级理（文）科总分分数段人数及比例
Calls: chooseExcel
Table Accessed:
1. 理科总成绩.csv
2. 文科总成绩.csv
3. 艺理总成绩.csv
4. 艺文总成绩.csv
Table Updated: XXXX高X年级理（文）科总分分数段人数及比例
Input:
1. string folderInput: 原始数据所在的文件夹的绝对地址
2. string folderOutput：分析数据所在的文件夹的绝对地址
3. string name: 此次考试的名字或者称号
4. string gradeS: 参考学生的年级
Output: XXXX高X年级理（文）科总分分数段人数及比例
Return: true代表数据分析成功，false则代表失败
Others: null
********************************************************************************/
bool Excel2::getExcel()
{
	Exam().clear();
	// 数据分析输出文件的绝对路径
	string excelName2 = folderOutput + "\\" + "表二：" + name + "理（文）科" + "高" + gradeS + "年级总分分数段人数及比例.csv";
	const char * excelNamec2 = excelName2.c_str();

	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Input = folderInput + "\\理科总成绩.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\文科总成绩.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\艺理总成绩.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\艺文总成绩.csv";
	const char * file4 = file4Input.c_str();

	// 输入分数段
	vector<int> scoreSection;
	
	int score = -1;
	int lscore = -1;
	while (true)
	{ 
		do {
			if (lscore != -1) cout << "上一个分数段是" << lscore;
			cout << "输入分数段,输入的数字必须是单调递减的,";
			
			if (lscore == -1) {
				score = Exam().inputInteger(0, MaxScore);
				lscore = score + 1;
			}
			else
			{
				score = Exam().inputInteger(0, lscore - 1);
			}
		} while (lscore <= score) ;
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
	}

	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec2);
	ofstream excel2;
	excel2.open(excelNamec2, std::ios::out | std::ios::app);

	if (!excel2.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel2 << "类型,参考人数";
	for (auto ss : scoreSection) excel2 << ",>=" << ss;
	excel2 << ",<=" << scoreSection[scoreSection.size() - 1];

	excel2 << endl;

	excel2.close();

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	string type = "";
	type = "理科";
	getData(excelNamec2, csv1, type, scoreSection);
	type = "文科";
	getData(excelNamec2, csv2, type, scoreSection);
	type = "艺理";
	getData(excelNamec2, csv3, type, scoreSection);
	type = "艺文";
	getData(excelNamec2, csv4, type, scoreSection);

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec2 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}


/********************************************************************************
Function: getData2
Description: 统计一个csv表中“总分”这一列的分数段
Calls: getExcel2
Table Accessed: XXXX高X年级理（文）科总分分数段人数及比例
Table Updated: XXXX高X年级理（文）科总分分数段人数及比例
Input:
1. const char * excelName: 数据分析表的绝对地址
2. Csv csv: 已经处理好的Csv对象，内含原始数据表table
3. string type: 此次分析数据的类型，主要有：理科，文科，艺理，艺文
4. vector<int> scoreSection: 每个元素为分数段中每段的分数
Output: 在指定csv文件生成一行分析数据
Return: null
Others: null
********************************************************************************/
void Excel2::getData(const char * excelName, Csv &csv, string type, vector<int> scoreSection)
{
	vector<vector<string>> &table = csv.getTable();
	if (table[0][6].compare("总分") == 0) // 检测原始数据表格第六列是否为“总分”
	{
		ofstream excel2;
		excel2.open(excelName, std::ios::out | std::ios::app); // 打开分析文件数据流

		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int student = 0; // 学生数目
		int scoreEvery[1000] = { 0 }; // 一分一段表
		int scoreSectionSize = scoreSection.size(); // 所划分的分数段数目
		vector<int> scoreNumber(scoreSectionSize + 1); // 每个分数段的学生人数
		vector<double> scoreBatch(scoreSectionSize + 1); // 每个分数段的学生比例

		if (!table.empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // 当行第六列的数据为数字时
			{
				score = (int)ceill(atof(table[i][6].c_str())); // 记录当前学生的总分
				scoreEvery[score]++;
				student++;
				score = -1; // 置回学生分数
			}
			if (student != 0) // 若参考人数不为0
			{
				for (int i = 0, j = scoreSectionSize - 1; i < 1000; i++) // 从一分一段表中提取每一分的人数
				{
					if (scoreEvery[i] > 0) // 若当前分数的人数大于0
					{
						if (i < scoreSection[j]) // 若当前分数小于最小值，则将当前分数的人数相加到最后一个分数段
						{
							scoreNumber[j + 1] += scoreEvery[i];
						}
						else // 若当前分数大于最小值
						{
							while (j > 0 && i >= scoreSection[j - 1]) j--; // 从最后一个分数段往前比较，找到适合该分数的分数段
							scoreNumber[j] += scoreEvery[i]; // 找到后将该分数的人数相加到相应的分数段
						}
					}
				}
				for (int i = 0; i <= scoreSectionSize; i++) // 通过每个分数段的人数计算每个分数段的学生比例
				{
					scoreBatch[i] = 100 * (1.0 * scoreNumber[i]) / (1.0 * student);
				}
			}

		}

		// 最后输出数据到指定csv文件中
		excel2 << type << "," << student;
		for (auto n : scoreNumber) excel2 << "," << n;
		excel2 << endl;
		excel2 << ",";
		for (auto b : scoreBatch) excel2 << "," << fixed << setprecision(2) << b << "%";
		excel2 << endl;

		excel2.close(); // 关闭输出流
	}
}