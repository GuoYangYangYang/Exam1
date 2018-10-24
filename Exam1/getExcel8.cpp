#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-28
Description: 表七：XXXX高X年级文科各班单科一本人数、本科人数及比例
********************************************************************************/

Excel8::Excel8(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel8::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

bool Excel8::getExcel()
{
	Exam().clear();
	// 数据分析输出文件的绝对路径
	string excelName8 = folderOutput + "\\" + "表八：" + name + "高" + gradeS + "年级文科各班单科一本人数、本科人数及比例.csv";
	const char * excelNamec8 = excelName8.c_str();

	// 原始输入数据文件的绝对路径，有两个，分别代表文科，艺文
	string file1Input = folderInput + "\\文科总成绩.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\艺文总成绩.csv";
	const char * file2 = file2Input.c_str();

	// 班级信息
	vector<vector<int>> Class;

	setScoreBatch(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);

	// 分析四种数据
	string typeS = " ";
	typeS = "文科";
	getData(csv1, Class); // 分析文科总成绩
	typeS = "艺文";
	getData(csv2, Class); // 分析艺文总成绩

	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec8);
	ofstream Excel8;
	Excel8.open(excelNamec8, std::ios::out | std::ios::app);

	if (!Excel8.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	Excel8 << ",,语文,,文数,,英语,,政治,,历史,,地理,,文综,," << endl;
	Excel8 << ",参考人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数," << endl;

	for (int i = 1; i < (int)Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			Excel8 << "高" << gradeS << "（" << i << "）";
			for (int j = 0; j < (int)Class[i].size(); j++) Excel8 << "," << Class[i][j];
			Excel8 << endl;
			Excel8 << ",,";
			for (int j = 1; j < (int)Class[i].size(); j++)
				Excel8 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%,";
			Excel8 << endl;
		}
	}

	Excel8 << endl << "注,一本线,本科线" << endl;
	Excel8 << "语文," << Class[0][1] << "," << Class[0][2] << endl;
	Excel8 << "文数," << Class[0][3] << "," << Class[0][4] << endl;
	Excel8 << "英语," << Class[0][5] << "," << Class[0][6] << endl;
	Excel8 << "政治," << Class[0][7] << "," << Class[0][8] << endl;
	Excel8 << "历史," << Class[0][9] << "," << Class[0][10] << endl;
	Excel8 << "地理," << Class[0][11] << "," << Class[0][12] << endl;
	Excel8 << "文综," << Class[0][13] << "," << Class[0][14] << endl;

	Excel8.close();

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec8 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}


void Excel8::setScoreBatch(vector<vector<int>> &Class)
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
		vector<string> name = { "语文","文数","英语","政治","历史","地理","文综" };
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
			maxScore = MaxPoliticsScore;
			break;
		case(5):
			maxScore = MaxHistoryScore;
			break;
		case(6):
			maxScore = MaxGeographyScore;
			break;
		case(7):
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
		Class[0][2 * flag - 1] = firstBatch;
		Class[0][2 * flag] = secondBatch;
	}
}

int Excel8::initClass(vector<vector<int>> &Class, string classS)
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

void Excel8::getData(Csv csv, vector<vector<int>> &Class)
{
	auto table = csv.getTable();
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”。。。。。。
	if ((table[0][3].compare("科类") == 0) &&
		(table[0][4].compare("班级") == 0) &&
		(table[0][6].compare("总分") == 0) &&
		(table[0][7].compare("语文") == 0) &&
		(table[0][8].compare("文数") == 0) &&
		(table[0][9].compare("英语") == 0) &&
		(table[0][10].compare("政治") == 0) &&
		(table[0][11].compare("历史") == 0) &&
		(table[0][12].compare("地理") == 0)
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
						score[j] = ceill(atof(table[i][j + 6].c_str())); // 获取当前学生分数
					}
					score[7] = score[4] + score[5] + score[6]; // 计算学生文综成绩
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