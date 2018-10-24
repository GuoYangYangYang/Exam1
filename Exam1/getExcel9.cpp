#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-27
Description: 表九：XXXX高X年级XX单科分数段人数及比例
********************************************************************************/

Excel9::Excel9(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel9::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel9::getExcel()
{
	Exam().clear();

	string typeS = " ";

	int typeN = 0;
	int maxScore = -1;

	vector<string> name9 = { "语文","理数","文数","英语","物理","化学","生物","理综","政治","历史","地理","文综" };
	cout << "+--------------------------------------------------------" << endl;
	cout << "|选择科目，输入0则生成分析数据：" << endl;
	cout << "+--------------------------------------------------------" << endl;
	for (int i = 1; i <= (int)name9.size(); i++)
	{
		cout << "|";
		printf("%2d", i);
		cout << "|" << name9[i - 1];
		cout << endl;
	}
	cout << "+--------------------------------------------------------" << endl;
	typeN = Exam().inputInteger(0, 12);
	switch (typeN)
	{
	case(1):
		maxScore = MaxChineseScore;
		break;
	case(2):
		maxScore = MaxMathScore;
		break;
	case(3):
		maxScore = MaxMathScore;
		break;
	case(4):
		maxScore = MaxEnglishScore;
		break;
	case(5):
		maxScore = MaxPhysicsScore;
		break;
	case(6):
		maxScore = MaxChemistryScore;
		break;
	case(7):
		maxScore = MaxBiologyScore;
		break;
	case(8):
		maxScore = MaxScienceComprehensiveScore;
		break;
	case(9):
		maxScore = MaxPoliticsScore;
		break;
	case(10):
		maxScore = MaxHistoryScore;
		break;
	case(11):
		maxScore = MaxGeographyScore;
		break;
	case(12):
		maxScore = MaxArtsComprehensiveScore;
		break;
	default:
		break;
	}

	if (typeN > 0 && typeN <= (int)name9.size()) typeS = name9[typeN - 1];
	else return false;

	// 数据分析输出文件的绝对路径
	string excelName9 = folderOutput + "\\" + "表九：" + name + "高" + gradeS + "年级" + typeS + "单科分数段人数及比例.csv";
	const char * excelNamec9 = excelName9.c_str();

	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Input = folderInput + "\\理科总成绩.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\文科总成绩.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\艺理总成绩.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\艺文总成绩.csv";
	const char * file4 = file4Input.c_str();

	// 班级信息
	vector<vector<int>> Class;

	vector<double> scoreSection;

	setScoreBatch(scoreSection, (double)maxScore);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	getData(csv1, Class, scoreSection, typeS); // 分析理科总成绩
	getData(csv2, Class, scoreSection, typeS); // 分析艺理总成绩
	getData(csv3, Class, scoreSection, typeS); // 分析理科总成绩
	getData(csv4, Class, scoreSection, typeS); // 分析艺理总成绩

	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec9);
	ofstream excel9;
	excel9.open(excelNamec9, std::ios::out | std::ios::app);

	if (!excel9.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel9 << "科目:" << typeS << ",参考人数";
	for (auto ss : scoreSection) excel9 << ",>=" << ss;
	excel9 << ",<" << scoreSection[scoreSection.size() - 1] << endl;;

	for (int i = 1; i < (int)Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel9 << "高" << gradeS << "（" << i << "）";
			for (int j = 0; j < (int)Class[i].size(); j++) excel9 << "," << Class[i][j];
			excel9 << endl;
			excel9 << ",";
			for (int j = 1; j < (int)Class[i].size(); j++)
			{
				excel9 << ",";
				excel9 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%";
			}
			excel9 << endl;
		}
	}

	excel9.close();

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec9 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

void Excel9::setScoreBatch(vector<double> &scoreSection, double maxScore)
{
	Exam().clear();

	double score = -1;
	double lscore = -1;
	cout << "该门总分是" << maxScore << "，";
	score = Exam().inputDouble(0, maxScore);
	lscore = score;
	scoreSection.push_back(score);
	while (true)
	{
		do {
			if (lscore != -1) cout << "上一个分数段是" << lscore;
			cout << "输入分数段,输入的数字必须是单调递减的:" << endl;
			score = Exam().inputDouble(0, lscore);
			if (lscore == -1) lscore = score + 1;
		} while (lscore <= score);
		if (score == 0) break;
		scoreSection.push_back(score);
		lscore = score;
	}
}

int Excel9::initClass(vector<vector<int>> &Class, string classS, int scoreSectionSize)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN >= (int)Class.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
		{
			int ClassN = Class.size();
			while (classN >= ClassN)
			{
				vector<int> classData(scoreSectionSize + 2, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

int Excel9::findScoreSection(vector<double> scoreSection, double score)
{
	int i = scoreSection.size() - 1;
	if (score < scoreSection[i]) return i + 1;
	if (score >= scoreSection[0]) return 0;
	while (i > 0)
	{
		if (score >= scoreSection[i] && score < scoreSection[i - 1]) return i;
		i--;
	}
	return 0;
}

void Excel9::getData(Csv csv, vector<vector<int>> &Class, vector<double> scoreSection, string typeS)
{
	auto table = csv.getTable();
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”
	if ((table[0][3].compare("科类") == 0) &&
		(table[0][4].compare("班级") == 0) &&
		(table[0][6].compare("总分") == 0)
		)
	{

		int typeN = 0;
		
		if (typeS.compare("理综") == 0)
		{
			for (int l = 7; l <= 12; l++)
				if (table[0][l].compare("物理") == 0)
					typeN = l;
		}
		else if (typeS.compare("文综") == 0)
		{
			for (int l = 7; l <= 12; l++)
				if (table[0][l].compare("政治") == 0)
					typeN = l;
		}
		else
		{
			for (int l = 7; l <= 12; l++)
				if (table[0][l].compare(typeS) == 0)
					typeN = l;
		}

		int i = 1; // 行数
		int classN = -1; // 当前学生的班级
		double score = 0; // 当前学生的分数
		int section = -1; // 当前学生单科所在分数段

		if (!table.empty() && typeN >= 7) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // 当列的数据为数字时
			{
				classN = initClass(Class, table[i][4], (int)scoreSection.size()); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					if (typeS.compare("理综") == 0 || typeS.compare("文综") == 0)
						score = atof(table[i][typeN].c_str()) + atof(table[i][typeN + 1].c_str()) + atof(table[i][typeN + 2].c_str());
					else 
						score = ceill(atof(table[i][typeN].c_str())); // 获取当前学生分数
					if (score > 0.0)
					{
						Class[classN][0]++; // 学生数据有效，则参考人数加一
						section = findScoreSection(scoreSection, score);
						if (section != -1) Class[classN][section + 1]++;
					}
				}
				classN = -1;
				score = 0;
				section = -1;
			}
		}

	}
}

