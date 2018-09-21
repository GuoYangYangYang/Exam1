#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-20
Description: 表二：XXXX高X年级理（文）科总分分数段人数及比例
********************************************************************************/

typedef struct classData
{
	string className;
	int allNumber;
	int fristNumber;
	int secondNumber;
	bool SorA;
} classData;

int initClass(vector<classData> &Class, string gradeS, string typeS, string classS)
{
	bool type = false;
	classS = classS.substr(2, 2);
	if (!typeS.compare("理科")) type = true;
	else type = false;
	//cout << type << classS << endl;
	if (isNum(classS))
	{
		int classN = atoi(classS.c_str());
		if (classN > Class.size())
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				string className = "高" + gradeS + "（";
				className += to_string(ClassN + 1);
				className += "）";
				classData classNew = {className, 0, 0, 0, true};
				Class.push_back(classNew);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

void getData3(const char * excelName, Csv csv, vector<classData> &Class, string gradeS, double fristBatch, double secondBatch)
{
	// 检测原始数据表格第四列是否为“班级”和第六列是否为“总分”
	if ((csv.table[0][3].compare("科类") == 0) && (csv.table[0][4].compare("班级") == 0) && (csv.table[0][6].compare("总分") == 0))
	{
		ofstream excel3;
		excel3.open(excelName, std::ios::out | std::ios::app); // 打开分析文件数据流

		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int classN = -1; // 当前学生的班级

		if (!csv.table.empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass(Class, gradeS, csv.table[i][3], csv.table[i][4]);
				if (classN != -1)
				{
					if (!csv.table[i][3].compare("理科")) Class[classN - 1].SorA = true;
					else Class[classN - 1].SorA = false;
					score = atoi(csv.table[i][6].c_str());
					if (score >= 0) Class[classN - 1].allNumber++;
					if (score >= secondBatch) Class[classN - 1].secondNumber++;
					if (score >= fristBatch) Class[classN - 1].fristNumber++;
				}
			}
		}

		excel3.close();
	}
}

bool getExcel3(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName3 = folderOutput + "\\" + name + "高" + gradeS + "年级各班一本人数与本科人数及比例.csv";
	const char * excelNamec3 = excelName3.c_str();

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

	/*
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
	*/

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 班级信息
	vector<classData> Class;

	// 分析四种数据
	string type = "";
	type = "理科";
	getData3(excelNamec3, csv1, Class, gradeS, scienceFristBatch, scienceSecondBatch); // 分析理科总成绩
	type = "文科";
	getData3(excelNamec3, csv2, Class, gradeS, artsFristBatch, artsSecondBatch); // 分析文科总成绩
	type = "艺理";
	getData3(excelNamec3, csv3, Class, gradeS, scienceFristBatch, scienceSecondBatch); // 分析理科总成绩
	type = "艺文";
	getData3(excelNamec3, csv4, Class, gradeS, artsFristBatch, artsSecondBatch); // 分析文科总成绩


	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec3);
	ofstream excel3;
	excel3.open(excelNamec3, std::ios::out | std::ios::app);

	if (!excel3.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel3 << "班级,参考人数,一本人数,比例,本科人数,比例,理/文" << endl;

	for (auto c : Class)
	{
		if (c.allNumber != 0)
		{
			excel3 << c.className << "," << c.allNumber << "," << c.fristNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.fristNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			excel3 << "," << c.secondNumber << ",";
			excel3 << fixed << setprecision(2) << (100 * (c.secondNumber * 1.0) / (c.allNumber * 1.0)) << "%";
			if (c.SorA) excel3 << ",理科" << endl;
			else excel3 << ",文科" << endl;
		}
	}

	excel3 << endl;
	excel3 << "注,一本线,本科线" << endl;
	excel3 << "理科," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel3 << "文科," << artsFristBatch << "," << artsSecondBatch << endl;

	excel3.close();
	return true;
}