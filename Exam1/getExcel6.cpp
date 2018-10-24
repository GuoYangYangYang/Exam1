#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-25
Description: 表六：XXXX高X年级各班理（文）科单科一本人数、本科人数及比例
********************************************************************************/

Excel6::Excel6(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel6::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel6::getExcel()
{
	Exam().clear();

	// 数据分析输出文件的绝对路径
	string excelName6 = folderOutput + "\\" + "表六：" + name + "高" + gradeS + "年级各班理（文）科单科一本人数、本科人数及比例.csv";
	const char * excelNamec6 = excelName6.c_str();

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
	int Class[20][5] = { 0 };

	setScoreBatch(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	string typeS = " ";
	typeS = "理科";
	getData(csv1, Class, typeS); // 分析理科总成绩
	typeS = "文科";
	getData(csv2, Class, typeS); // 分析文科总成绩
	typeS = "艺理";
	getData(csv3, Class, typeS); // 分析艺理总成绩
	typeS = "艺文";
	getData(csv4, Class, typeS); // 分析艺文总成绩

								 // 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec6);
	ofstream excel6;
	excel6.open(excelNamec6, std::ios::out | std::ios::app);

	if (!excel6.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel6 << "理科,参考人数,一本人数,比例,本科人数,比例" << endl;

	vector<string> type = { "理语","理数","理英","物理","化学","生物","理综",
							"文语","文数","文英","政治","历史","地理","文综" };

	for (int i = 0; i < 7; i++) // 输出理科
	{
		excel6 << type[i] << "," << Class[i + 1][0] << "," << Class[i + 1][2] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][2]) / (1.0 *Class[i + 1][0]) << "%,";
		excel6 << Class[i + 1][4] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][4]) / (1.0 *Class[i + 1][0]) << "%";
		excel6 << endl;
	}

	excel6 << endl;
	excel6 << "文科,参考人数,一本人数,比例,本科人数,比例" << endl;

	for (int i = 7; i < 14; i++) // 输出文科
	{
		excel6 << type[i] << "," << Class[i + 1][0] << "," << Class[i + 1][2] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][2]) / (1.0 *Class[i + 1][0]) << "%,";
		excel6 << Class[i + 1][4] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][4]) / (1.0 *Class[i + 1][0]) << "%";
		excel6 << endl;
	}

	excel6.close();

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec6 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

void Excel6::setScoreBatch(int Class[][5])
{
	int flag = -1;
	int maxScore = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	while (true)
	{
		Exam().clear();
		vector<string> name = { "理语","理数","理英","物理","化学","生物","理综",
			"文语","文数","文英","政治","历史","地理","文综" };
		cout << "+--------------------------------------" << endl;
		cout << "|选择数字设置对应科目的一本线和本科线" << endl;
		cout << "+--------------------------------------" << endl;
		for (int i = 1; i <= (int)name.size(); i++)
		{
			cout << "|";
			printf("%2d", i);
			cout << "|" << name[i - 1];
			cout << "|一本线：";
			printf("%3d", Class[i][1]);
			cout << "|本科线：";
			printf("%3d", Class[i][3]);
			cout << endl;
		}
		cout << "+--------------------------------------" << endl;
		flag = Exam().inputInteger(0, name.size());
		switch (flag)
		{
		case(1): // 理语
			maxScore = MaxChineseScore;
			break;
		case(2): // 理数
			maxScore = MaxMathScore;
			break;
		case(3): // 理英
			maxScore = MaxEnglishScore;
			break;
		case(4): // 物理
			maxScore = MaxPhysicsScore;
			break;
		case(5): // 化学
			maxScore = MaxChemistryScore;
			break;
		case(6): // 生物
			maxScore = MaxBiologyScore;
			break;
		case(7): // 理综
			maxScore = MaxScienceComprehensiveScore;
			break;
		case(8): // 文语
			maxScore = MaxChineseScore;
			break;
		case(9): // 文数
			maxScore = MaxMathScore;
			break;
		case(10): // 文英
			maxScore = MaxEnglishScore;
			break;
		case(11): // 政治
			maxScore = MaxPoliticsScore;
			break;
		case(12): // 历史
			maxScore = MaxHistoryScore;
			break;
		case(13): // 地理
			maxScore = MaxGeographyScore;
			break;
		case(14): // 文综
			maxScore = MaxArtsComprehensiveScore;
			break;
		default:
			break;
		}
		if (flag == 0) break;
		cout << "请设置" << name[flag - 1] << "的一本线：" << endl;
		firstBatch = Exam().inputInteger(0, maxScore);
		cout << "请设置" << name[flag - 1] << "的本科线：" << endl;
		secondBatch = Exam().inputInteger(0, firstBatch - 1);
		Class[flag][1] = firstBatch;
		Class[flag][3] = secondBatch;
	}
}

void Excel6::getData(Csv csv, int Class[][5], string typeS)
{
	auto table = csv.getTable();
	// 检测原始数据表格第四列是否为“班级”和第六列是否为“总分”
	if ((table[0][3].compare("科类") == 0) && (table[0][4].compare("班级") == 0) && (table[0][6].compare("总分") == 0))
	{
		if (!table.empty()) // 如果原始数据表格不为空
		{
			int type = -1;
			int flag = 0;

			if (!typeS.compare("理科")) flag = 1;
			if (!typeS.compare("文科")) flag = 2;
			if (!typeS.compare("艺理")) flag = 3;
			if (!typeS.compare("艺文")) flag = 4;

			if (flag == 1 || flag == 3) // 理科
			{
				for (int i = 0; i <= 12; i++)
				{
					if (table[0][i].compare("总分") == 0) type = 0;
					if (table[0][i].compare("语文") == 0) type = 1;
					if (table[0][i].compare("理数") == 0) type = 2;
					if (table[0][i].compare("英语") == 0) type = 3;
					if (table[0][i].compare("物理") == 0) type = 4;
					if (table[0][i].compare("化学") == 0) type = 5;
					if (table[0][i].compare("生物") == 0) type = 6;

					if (type == 0)
					{
						double score = 0.0;
						for (int j = 1; (score = atof(table[j][i].c_str())) != 0.0; j++) // 可能存在bug
							Class[0][flag]++;
					}

					if (type != -1 && type != 0)
					{
						double score = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score = ceill(atof(table[i][6].c_str())); // 获取当前学生分数
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type][0]++;
								if (score >= (1.0 * Class[type][1])) Class[type][2]++;
								if (score >= (1.0 * Class[type][3])) Class[type][4]++;
							}
						}
					}

					if (type == 4) // 当检测到物理时，计算理综
					{
						double score = 0.0, score1 = 0.0, score2 = 0.0, score3 = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score1 = atof(table[j][i].c_str()), // 获取物理
							score2 = atof(table[j][i + 1].c_str()), // 获取化学
							score3 = atof(table[j][i + 2].c_str()), // 获取生物
							score = score1 + score2 + score3; // 计算理综
							score = ceill(score); // 四舍五入
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type + 3][0]++;
								if (score >= (1.0 * Class[type + 3][1])) Class[type + 3][2]++;
								if (score >= (1.0 * Class[type + 3][3])) Class[type + 3][4]++;
							}
						}
					}

					type = -1; // 重置type
				}
			} // if

			if (flag == 2 || flag == 4) // 文科
			{
				for (int i = 0; i <= 12; i++)
				{
					if (table[0][i].compare("总分") == 0) type = 0;
					if (table[0][i].compare("语文") == 0) type = 8;
					if (table[0][i].compare("文数") == 0) type = 9;
					if (table[0][i].compare("英语") == 0) type = 10;
					if (table[0][i].compare("政治") == 0) type = 11;
					if (table[0][i].compare("历史") == 0) type = 12;
					if (table[0][i].compare("地理") == 0) type = 13;

					if (type == 0)
					{
						double score = 0.0;
						for (int j = 1; (score = atof(table[j][i].c_str())) != 0.0; j++) // 可能存在bug
							Class[0][flag]++;
					}

					if (type != -1 && type != 0)
					{
						double score = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score = ceill(atof(table[i][6].c_str())); // 获取当前学生分数
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type][0]++;
								if (score >= (1.0 * Class[type][1])) Class[type][2]++;
								if (score >= (1.0 * Class[type][3])) Class[type][4]++;
							}
						}
					}

					if (type == 11) // 当检测到政治时，计算文综
					{
						double score = 0.0, score1 = 0.0, score2 = 0.0, score3 = 0.0;
						for (int j = 1; j <= Class[0][flag]; j++)
						{
							score1 = atof(table[j][i].c_str()), // 获取政治
							score2 = atof(table[j][i + 1].c_str()), // 获取地理
							score3 = atof(table[j][i + 2].c_str()), // 获取历史
							score = score1 + score2 + score3; // 计算文综
							score = ceill(score); // 四舍五入
							if (score != 0.0)
							{
								if (score >= 0.0) Class[type + 3][0]++;
								if (score >= (1.0 * Class[type + 3][1])) Class[type + 3][2]++;
								if (score >= (1.0 * Class[type + 3][3])) Class[type + 3][4]++;
							}
						}
					}

					type = -1; // 重置type
				}
			} // if

		}
	}
}
