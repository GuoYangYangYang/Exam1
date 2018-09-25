#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-25
Description: 表四：XXXX高X年级各班成绩分数段人数及比例
********************************************************************************/

int initClass4(vector<vector<int>> &Class, string gradeS, string classS, int scoreSectionNumber)
{
	classS = classS.substr(2, 2);
	if (isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN > Class.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				vector<int> classData(scoreSectionNumber + 3, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

int findScoreSection(vector<int> scoreSection, int score)
{
	int i = scoreSection.size() - 1;
	if (score < scoreSection[i]) return i + 1;
	if (score >= scoreSection[0]) return 0;
	while (i > 0)
	{
		if (score >= scoreSection[i] && score < scoreSection[i - 1]) return i;
		i--;
	}
	return -1;
}

void getData4(Csv csv, vector<vector<int>> &Class, string gradeS, vector<int> scoreSection)
{
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”
	if ((csv.table[0][3].compare("科类") == 0) && (csv.table[0][4].compare("班级") == 0) && (csv.table[0][6].compare("总分") == 0))
	{
		if (scoreSection.size() != 0)
		{
			int i = 1; // 行数
			int score = -1; // 当前学生的分数
			int classN = -1; // 当前学生的班级

			if (!csv.table.empty()) // 如果原始数据表格不为空
			{
				for (i = 1; (isNum(csv.table[i][6])); i++) // 当行第六列的数据为数字时
				{
					classN = initClass4(Class, gradeS, csv.table[i][4], scoreSection.size()); // 获取班级号码，若数据表中不存在则进行初始化
					if (classN != -1)
					{
						if (!csv.table[i][3].compare("理科")) Class[classN - 1][0] = 1; // 理科置为1
						else Class[classN - 1][0] = 0; // 文科置为false
						score = atoi(csv.table[i][6].c_str()); // 获取当前学生分数
						if (score >= 0) Class[classN - 1][1]++; // 学生数据有效，则参考人数加一
						int section = findScoreSection(scoreSection, score);
						if (section != -1) Class[classN - 1][section + 2]++;
					}
				}
			}
		}
	}
}

bool getExcel4(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName4 = folderOutput + "\\" + name + "高" + gradeS + "年级各班成绩分数段人数及比例.csv";
	const char * excelNamec4 = excelName4.c_str();

	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Intput = folderIntput + "\\理科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\文科总成绩.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\艺理总成绩.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\艺文总成绩.csv";
	const char * file4 = file4Intput.c_str();

	// 输入分数段
	vector<int> scoreSection;

	double score = -1;
	double lscore = -1;
	while (true)
	{
		do {
			if (lscore != -1) cout << "上一个分数段是" << lscore;
			cout << "输入分数段,输入的数字必须是单调递减的:" << endl;
			cin >> score;
			if (lscore == -1) lscore = score + 1;
		} while (lscore <= score);
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
	}

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	vector<vector<int>> Class;
	
	getData4(csv1, Class, gradeS, scoreSection);
	getData4(csv2, Class, gradeS, scoreSection);
	getData4(csv3, Class, gradeS, scoreSection);
	getData4(csv4, Class, gradeS, scoreSection);

	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec4);
	ofstream excel4;
	excel4.open(excelNamec4, std::ios::out | std::ios::app);

	if (!excel4.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel4 << "班级,参考人数";
	for (auto ss : scoreSection) excel4 << ",>=" << ss;
	excel4 << ",<=" << scoreSection[scoreSection.size() - 1];

	excel4 << endl;

	for (int i = 0; i < Class.size(); i++)
	{
		if (Class[i][1] != 0)
		{
			excel4 << "高" << gradeS << "（" << (i + 1) << "）";
			for (int j = 1; j < Class[i].size(); j++)
			{
				excel4 << "," << Class[i][j];
			}
			excel4 << endl;
			excel4 << ",";
			for (int j = 2; j < Class[i].size(); j++)
			{
				excel4 << ",";
				excel4 << fixed << setprecision(2) << (100 * (Class[i][j] * 1.0) / (Class[i][1] * 1.0)) << "%";
			}
			excel4 << endl;
		}
	}

	excel4.close();
	return true;
}