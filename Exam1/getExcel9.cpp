#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-27
Description: 表九：XXXX高X年级XX单科分数段人数及比例
********************************************************************************/

void setScoreBatch9(vector<float> &scoreSection)
{
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
}

int initClass9(vector<vector<int>> &Class, string classS, int scoreSectionSize)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN >= Class.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
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

int findScoreSection9(vector<float> scoreSection, float score)
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

void getData9(Csv csv, vector<vector<int>> &Class, vector<float> scoreSection, string typeS)
{
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”
	if ((csv.getTable()[0][3].compare("科类") == 0) &&
		(csv.getTable()[0][4].compare("班级") == 0) &&
		(csv.getTable()[0][6].compare("总分") == 0)
		)
	{

		int typeN = 0;
		for (int l = 7; l <= 12; l++)
			if (csv.getTable()[0][l].compare(typeS) == 0)
				typeN = l;

		int i = 1; // 行数
		int classN = -1; // 当前学生的班级
		float score =  0; // 当前学生的分数
		int section = -1; // 当前学生单科所在分数段

		if (!csv.getTable().empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // 当列的数据为数字时
			{
				classN = initClass9(Class, csv.getTable()[i][4], scoreSection.size()); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					score = atof(csv.getTable()[i][typeN].c_str()); // 获取当前学生分数
					if (score > 0.0)
					{
						Class[classN][0]++; // 学生数据有效，则参考人数加一
						section = findScoreSection9(scoreSection, score);
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

bool getExcel9(string folderIntput, string folderOutput, string name, string gradeS)
{
	string typeS = " ";

	int typeN = 0;

	vector<string> name9 = { "语文","理数","文数","英语","物理","化学","生物","理综","政治","历史","地理","文综" };
	cout << "+--------------------------------------" << endl;
	cout << "|选择科目：" << endl;
	cout << "+--------------------------------------" << endl;
	for (int i = 1; i <= name9.size(); i++)
	{
		cout << "|";
		printf("%2d", i);
		cout << "|" << name9[i - 1];
		cout << endl;
	}
	cout << "+--------------------------------------" << endl;
	cin >> typeN;

	if (typeN > 0 && typeN <= name9.size()) typeS = name9[typeN - 1];
	else return false;

	// 数据分析输出文件的绝对路径
	string excelName9 = folderOutput + "\\" + name + "高" + gradeS + "年级"+ typeS +"单科分数段人数及比例.csv";
	const char * excelNamec9 = excelName9.c_str();

	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Intput = folderIntput + "\\理科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\文科总成绩.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\艺理总成绩.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\艺文总成绩.csv";
	const char * file4 = file4Intput.c_str();

	// 班级信息
	vector<vector<int>> Class;

	vector<float> scoreSection;

	setScoreBatch9(scoreSection);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	getData9(csv1, Class, scoreSection, typeS); // 分析理科总成绩
	getData9(csv2, Class, scoreSection, typeS); // 分析艺理总成绩
	getData9(csv3, Class, scoreSection, typeS); // 分析理科总成绩
	getData9(csv4, Class, scoreSection, typeS); // 分析艺理总成绩

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
	// 初始化数据分析表
	excel9 << "科目:" << typeS << ",参考人数";
	for (auto ss : scoreSection) excel9 << ",>=" << ss;
	excel9 << ",<" << scoreSection[scoreSection.size() - 1] << endl;;

	for (int i = 1; i < Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel9 << "高" << gradeS << "（" << i << "）";
			for (int j = 0; j < Class[i].size(); j++) excel9 << "," << Class[i][j];
			excel9 << endl;
			excel9 << ",";
			for (int j = 1; j < Class[i].size(); j++)
			{
				excel9 << ",";
				excel9 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%";
			}
			excel9 << endl;
		}
	}


	excel9.close();
	return true;
}