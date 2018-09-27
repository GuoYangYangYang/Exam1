#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-27
Description: 表八：XXXX高X年级文科各班单科一本人数、本科人数及比例
********************************************************************************/

void setScoreBatch8(vector<vector<int>> &Class)
{
	int flag = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	if (Class.size() < 1)
	{
		vector<int> batch(15, 0);
		Class.push_back(batch);
	}
	while (Class.size() > 0)
	{
		vector<string> name = { "语文","文数","英语","政治","历史","地理","文综" };
		cout << "+--------------------------------------" << endl;
		cout << "|选择数字设置对应科目的一本线和本科线" << endl;
		cout << "+--------------------------------------" << endl;
		for (int i = 1; i <= name.size(); i++)
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
		cout << "+--------------------------------------" << endl;
		cin >> flag;
		if (flag < 1) break;
		cout << "请设置" << name[flag - 1] << "的一本线：" << endl;
		cin >> firstBatch;
		cout << "请设置" << name[flag - 1] << "的本科线：" << endl;
		cin >> secondBatch;
		Class[0][2 * flag - 1] = firstBatch;
		Class[0][2 * flag] = secondBatch;
	}
}

int initClass8(vector<vector<int>> &Class, string classS)
{
	classS = classS.substr(2, 2);
	if (isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN >= Class.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
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

void getData8(Csv csv, vector<vector<int>> &Class)
{
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”。。。。。。
	if ((csv.table[0][3].compare("科类") == 0) &&
		(csv.table[0][4].compare("班级") == 0) &&
		(csv.table[0][6].compare("总分") == 0) &&
		(csv.table[0][7].compare("语文") == 0) &&
		(csv.table[0][8].compare("文数") == 0) &&
		(csv.table[0][9].compare("英语") == 0) &&
		(csv.table[0][10].compare("政治") == 0) &&
		(csv.table[0][11].compare("历史") == 0) &&
		(csv.table[0][12].compare("地理") == 0)
		)
	{
		int i = 1; // 行数
		int classN = -1; // 当前学生的班级
		float score[8] = { 0 };

		if (!csv.table.empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass8(Class, csv.table[i][4]); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					for (int j = 0; j < 7; j++)
					{
						score[j] = atof(csv.table[i][j + 6].c_str()); // 获取当前学生分数
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

bool getExcel8(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName8 = folderOutput + "\\" + name + "高" + gradeS + "年级文科各班单科一本人数、本科人数及比例.csv";
	const char * excelNamec8 = excelName8.c_str();

	// 原始输入数据文件的绝对路径，有两个，分别代表理科，艺理
	string file1Intput = folderIntput + "\\文科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\艺文总成绩.csv";
	const char * file2 = file2Intput.c_str();

	// 班级信息
	vector<vector<int>> Class;

	setScoreBatch8(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);

	// 分析四种数据
	string typeS = " ";
	typeS = "文科";
	getData8(csv1, Class); // 分析理科总成绩
	typeS = "艺文";
	getData8(csv2, Class); // 分析艺理总成绩

						   // 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec8);
	ofstream excel8;
	excel8.open(excelNamec8, std::ios::out | std::ios::app);

	if (!excel8.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel8 << ",,语文,,文数,,英语,,政治,,历史,,地理,,文综,," << endl;
	excel8 << ",参考人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数," << endl;

	for (int i = 1; i < Class.size(); i++)
	{
		if (Class[i][0] != 0)
		{
			excel8 << "高" << gradeS << "（" << i << "）";
			for (int j = 0; j < Class[i].size(); j++) excel8 << "," << Class[i][j];
			excel8 << endl;
			excel8 << ",,";
			for (int j = 1; j < Class[i].size(); j++)
				excel8 << fixed << setprecision(2) << 100 * (1.0 * Class[i][j]) / (1.0 *Class[i][0]) << "%,";
			excel8 << endl;
		}
	}

	excel8 << endl << "注,一本线,本科线" << endl;
	excel8 << "语文," << Class[0][1] << "," << Class[0][2] << endl;
	excel8 << "文数," << Class[0][3] << "," << Class[0][4] << endl;
	excel8 << "英语," << Class[0][5] << "," << Class[0][6] << endl;
	excel8 << "政治," << Class[0][7] << "," << Class[0][8] << endl;
	excel8 << "历史," << Class[0][9] << "," << Class[0][10] << endl;
	excel8 << "地理," << Class[0][11] << "," << Class[0][12] << endl;
	excel8 << "文综," << Class[0][13] << "," << Class[0][14] << endl;

	excel8.close();
	return true;
}
