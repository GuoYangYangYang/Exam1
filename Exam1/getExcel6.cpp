#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-25
Description: 表六：XXXX高X年级各班理（文）科单科一本人数、本科人数及比例
********************************************************************************/

void setScoreBatch(int Class[][5])
{
	int flag = -1;
	int firstBatch = 0;
	int secondBatch = 0;
	while (true)
	{
		vector<string> name = { "语文","理数","文数","英语","物理","化学","生物","理综","政治","地理","历史","文综" };
		cout << "+--------------------------------------" << endl;
		cout << "|选择数字设置对应科目的一本线和本科线" << endl;
		cout << "+--------------------------------------" << endl;
		for (int i = 1; i <= name.size(); i++)
		{
			cout << "|";
			printf("%2d", i);
			cout << "|" << name[i - 1];
			cout << "|一本线：";
			printf("%3d", Class[i - 1][1]);
			cout << "|本科线：";
			printf("%3d", Class[i - 1][3]);
			cout << endl;
		}
		cout << "+--------------------------------------" << endl;
		cin >> flag;
		if (flag < 1) break;
		cout << "请设置" << name[flag - 1] << "的一本线：" << endl;
		cin >> firstBatch;
		cout << "请设置" << name[flag - 1] << "的本科线：" << endl;
		cin >> secondBatch;
		Class[flag - 1][1] = firstBatch;
		Class[flag - 1][3] = secondBatch;
	}
}

void getData6(Csv csv, int Class[][5])
{
	// 检测原始数据表格第四列是否为“班级”和第六列是否为“总分”
	if ((csv.table[0][3].compare("科类") == 0) && (csv.table[0][4].compare("班级") == 0) && (csv.table[0][6].compare("总分") == 0))
	{
		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int classN = -1; // 当前学生的班级

		if (!csv.table.empty()) // 如果原始数据表格不为空
		{
			int type = -1;

			for (int i = 7; i <= 12; i++)
			{
				if (csv.table[0][i].compare("语文") == 0) type = 0;
				if (csv.table[0][i].compare("理数") == 0) type = 1;
				if (csv.table[0][i].compare("文数") == 0) type = 2;
				if (csv.table[0][i].compare("英语") == 0) type = 3;
				if (csv.table[0][i].compare("物理") == 0) type = 4;
				if (csv.table[0][i].compare("化学") == 0) type = 5;
				if (csv.table[0][i].compare("生物") == 0) type = 6;
				if (csv.table[0][i].compare("理综") == 0) type = 7;
				if (csv.table[0][i].compare("政治") == 0) type = 8;
				if (csv.table[0][i].compare("地理") == 0) type = 9;
				if (csv.table[0][i].compare("历史") == 0) type = 10;
				if (csv.table[0][i].compare("文综") == 0) type = 11;
				if (type != -1)
				{
					for (int j = 1; (isNum(csv.table[j][i])); j++) // 当行第七列的数据为数字时
					{
						float score = atof(csv.table[j][i].c_str());
						if (score >= 0.0) Class[type][0]++;
						if (score >= (1.0 * Class[type][1])) Class[type][2]++;
						if (score >= (1.0 * Class[type][3])) Class[type][4]++;
					}
				}
				type = -1;
			}
		}
	}
}


bool getExcel6(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName6 = folderOutput + "\\" + name + "高" + gradeS + "年级各班一本人数与本科人数及比例.csv";
	const char * excelNamec6 = excelName6.c_str();

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
	int Class[13][5] = {0};

	setScoreBatch(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	getData6(csv1, Class); // 分析理科总成绩
	getData6(csv2, Class); // 分析文科总成绩
	getData6(csv3, Class); // 分析艺理总成绩
	getData6(csv4, Class); // 分析艺文总成绩

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << Class[i][j] << " ";
		}
		cout << endl;
	}

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
	excel6 << "科目,参考人数,一本人数,比例,本科人数,比例" << endl;


	// 最后输出一本理科文科线和本科理科文科线
	excel6 << endl;

	excel6.close();
	return true;
}