#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-25
Description: 表四：XXXX高X年级各班成绩分数段人数及比例
********************************************************************************/

Excel4::Excel4(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel4::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel4::getExcel()
{
	Exam().clear();

	// 数据分析输出文件的绝对路径
	string excelName4 = folderOutput + "\\" + name + "高" + gradeS + "年级各班成绩分数段人数及比例.csv";
	const char * excelNamec4 = excelName4.c_str();

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

	getData(csv1, Class, gradeS, scoreSection);
	getData(csv2, Class, gradeS, scoreSection);
	getData(csv3, Class, gradeS, scoreSection);
	getData(csv4, Class, gradeS, scoreSection);

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

	for (int i = 0; i < (int)Class.size(); i++)
	{
		if (Class[i][1] != 0)
		{
			excel4 << "高" << gradeS << "（" << (i + 1) << "）";
			for (int j = 1; j < (int)Class[i].size(); j++)
			{
				excel4 << "," << Class[i][j];
			}
			excel4 << endl;
			excel4 << ",";
			for (int j = 2; j < (int)Class[i].size(); j++)
			{
				excel4 << ",";
				excel4 << fixed << setprecision(2) << (100 * (Class[i][j] * 1.0) / (Class[i][1] * 1.0)) << "%";
			}
			excel4 << endl;
		}
	}

	excel4.close();

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec4 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

int Excel4::initClass(vector<vector<int>> &Class, string gradeS, string classS, int scoreSectionNumber)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN > (int)Class.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
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

int Excel4::findScoreSection(vector<int> scoreSection, int score)
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

void Excel4::getData(Csv csv, vector<vector<int>> &Class, string gradeS, vector<int> scoreSection)
{
	auto table = csv.getTable();
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”
	if ((table[0][3].compare("科类") == 0) && (table[0][4].compare("班级") == 0) && (table[0][6].compare("总分") == 0))
	{
		if (scoreSection.size() != 0)
		{
			int i = 1; // 行数
			int score = -1; // 当前学生的分数
			int classN = -1; // 当前学生的班级

			if (!table.empty()) // 如果原始数据表格不为空
			{
				for (i = 1; (Exam().isNum(table[i][6])); i++) // 当行第六列的数据为数字时
				{
					classN = initClass(Class, gradeS, table[i][4], scoreSection.size()); // 获取班级号码，若数据表中不存在则进行初始化
					if (classN != -1)
					{
						if (!table[i][3].compare("理科")) Class[classN - 1][0] = 1; // 理科置为1
						else Class[classN - 1][0] = 0; // 文科置为false
						score = atoi(table[i][6].c_str()); // 获取当前学生分数
						if (score >= 0) Class[classN - 1][1]++; // 学生数据有效，则参考人数加一
						int section = findScoreSection(scoreSection, score);
						if (section != -1) Class[classN - 1][section + 2]++;
					}
				}
			}
		}
	}
}