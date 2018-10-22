#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-27
Description: 表七：XXXX高X年级理科各班单科一本人数、本科人数及比例
********************************************************************************/

Excel7::Excel7(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel7::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel7::getExcel()
{
	Exam().clear();
	// 数据分析输出文件的绝对路径
	string excelName7 = folderOutput + "\\" + "表七：" + name + "高" + gradeS + "年级理科各班单科一本人数、本科人数及比例.csv";
	const char * excelNamec7 = excelName7.c_str();

	// 原始输入数据文件的绝对路径，有两个，分别代表理科，艺理
	string file1Input = folderInput + "\\理科总成绩.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\艺理总成绩.csv";
	const char * file2 = file2Input.c_str();

	// 班级信息
	vector<vector<int>> Class;

	setScoreBatch(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);

	// 分析四种数据
	string typeS = " ";
	typeS = "理科";
	getData(csv1, Class); // 分析理科总成绩
	typeS = "艺理";
	getData(csv2, Class); // 分析艺理总成绩

						  // 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec7);
	ofstream excel7;
	excel7.open(excelNamec7, std::ios::out | std::ios::app);

	if (!excel7.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel7 << ",,语文,,理数,,英语,,物理,,化学,,生物,,理综,," << endl;
	excel7 << ",参考人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数," << endl;

	for (int i = 1; i < (int)Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel7 << "高" << gradeS << "（" << i << "）";
			for (int j = 0; j < (int)Class[i].size(); j++) excel7 << "," << Class[i][j];
			excel7 << endl;
			excel7 << ",,";
			for (int j = 1; j < (int)Class[i].size(); j++)
				excel7 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%,";
			excel7 << endl;
		}
	}

	excel7 << endl << "注,一本线,本科线" << endl;
	excel7 << "语文," << Class[0][1] << "," << Class[0][2] << endl;
	excel7 << "理数," << Class[0][3] << "," << Class[0][4] << endl;
	excel7 << "英语," << Class[0][5] << "," << Class[0][6] << endl;
	excel7 << "物理," << Class[0][7] << "," << Class[0][8] << endl;
	excel7 << "化学," << Class[0][9] << "," << Class[0][10] << endl;
	excel7 << "生物," << Class[0][11] << "," << Class[0][12] << endl;
	excel7 << "理综," << Class[0][13] << "," << Class[0][14] << endl;

	excel7.close();

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec7 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}


void Excel7::setScoreBatch(vector<vector<int>> &Class)
{
	int flag = -1;
	int maxScore = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	if (Class.size() < 1)
	{
		vector<int> batch(15, 0);
		Class.push_back(batch);
	}
	while (Class.size() > 0)
	{
		Exam().clear();
		vector<string> name = { "语文","理数","英语","物理","化学","生物","理综" };
		cout << "+--------------------------------------------------------" << endl;
		cout << "|选择数字设置对应科目的一本线和本科线，输入0生成分析数据" << endl;
		cout << "+--------------------------------------------------------" << endl;
		for (int i = 1; i <= (int)name.size(); i++)
		{
			cout << "|";
			printf("%2d", i);
			cout << "|" << name[i - 1];
			cout << "|一本线：";
			printf("%3d", Class[0][2 * i - 1]);
			cout << "|本科线：";
			printf("%3d", Class[0][2 * i]);
			cout << endl;
		}
		cout << "+--------------------------------------------------------" << endl;
		flag = Exam().inputInteger(0, 7);
		switch (flag)
		{
		case(1):
			maxScore = MaxChineseScore;
			break;
		case(2):
			maxScore = MaxMathScore;
			break;
		case(3):
			maxScore = MaxEnglishScore;
			break;
		case(4):
			maxScore = MaxPhysicsScore;
			break;
		case(5):
			maxScore = MaxChemistryScore;
			break;
		case(6):
			maxScore = MaxBiologyScore;
			break;
		case(7):
			maxScore = MaxScienceComprehensiveScore;
			break;
		default:
			break;
		}
		if (flag == 0) break;
		cout << "请设置" << name[flag - 1] << "的一本线：" << endl;
		firstBatch = Exam().inputInteger(0, maxScore);
		cout << "请设置" << name[flag - 1] << "的本科线：" << endl;
		secondBatch = Exam().inputInteger(0, firstBatch - 1);
		Class[0][2 * flag - 1] = firstBatch;
		Class[0][2 * flag] = secondBatch;
	}
}

int Excel7::initClass(vector<vector<int>> &Class, string classS)
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
				vector<int> classData(15, 0);
				Class.push_back(classData);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

void Excel7::getData(Csv csv, vector<vector<int>> &Class)
{
	auto table = csv.getTable();
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”。。。。。。
	if ((table[0][3].compare("科类") == 0) &&
		(table[0][4].compare("班级") == 0) &&
		(table[0][6].compare("总分") == 0) &&
		(table[0][7].compare("语文") == 0) &&
		(table[0][8].compare("理数") == 0) &&
		(table[0][9].compare("英语") == 0) &&
		(table[0][10].compare("物理") == 0) &&
		(table[0][11].compare("化学") == 0) &&
		(table[0][12].compare("生物") == 0)
		)
	{
		int i = 1; // 行数
		int classN = -1; // 当前学生的班级
		double score[8] = { 0 };

		if (!table.empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass(Class, table[i][4]); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					for (int j = 0; j < 7; j++)
					{
						score[j] = atof(table[i][j + 6].c_str()); // 获取当前学生分数
					}
					score[7] = score[4] + score[5] + score[6]; // 计算学生理综成绩
					if (score[0] >= 0) Class[classN][0]++; // 学生数据有效，则参考人数加一
					for (int j = 1; j < 8; j++)
					{
						if (score[j] >= Class[0][2 * j - 1]) Class[classN][2 * j - 1]++;
						if (score[j] >= Class[0][2 * j]) Class[classN][2 * j]++;
					}
					for (int j = 0; j < 8; j++) score[j] = 0;
				}
			}
		}
	}
}