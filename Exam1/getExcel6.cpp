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

void getData6(Csv csv, int Class[][5], string typeS)
{
	// 检测原始数据表格第四列是否为“班级”和第六列是否为“总分”
	if ((csv.table[0][3].compare("科类") == 0) && (csv.table[0][4].compare("班级") == 0) && (csv.table[0][6].compare("总分") == 0))
	{
		if (!csv.table.empty()) // 如果原始数据表格不为空
		{
			int type = -1;
			int flag = 0;

			if (!typeS.compare("理科")) flag = 1;
			if (!typeS.compare("文科")) flag = 2;
			if (!typeS.compare("艺理")) flag = 3;
			if (!typeS.compare("艺文")) flag = 4;

			for (int i = 6; i <= 12; i++)
			{
				if (csv.table[0][i].compare("总分") == 0) type = 0;
				if (csv.table[0][i].compare("语文") == 0) type = 1;
				if (csv.table[0][i].compare("理数") == 0) type = 2;
				if (csv.table[0][i].compare("文数") == 0) type = 3;
				if (csv.table[0][i].compare("英语") == 0) type = 4;
				if (csv.table[0][i].compare("物理") == 0) type = 5;
				if (csv.table[0][i].compare("化学") == 0) type = 6;
				if (csv.table[0][i].compare("生物") == 0) type = 7;
				if (csv.table[0][i].compare("理综") == 0) type = 8;
				if (csv.table[0][i].compare("政治") == 0) type = 9;
				if (csv.table[0][i].compare("地理") == 0) type = 10;
				if (csv.table[0][i].compare("历史") == 0) type = 11;
				if (csv.table[0][i].compare("文综") == 0) type = 12;

				if (type == 0)
					for (int j = 1, score = 0.0; (score = atof(csv.table[j][i].c_str())) != 0.0; j++)
						Class[0][flag]++;

				if (type != -1 && type != 0)
				{
					float score = 0.0;
					for (int j = 1; j <= Class[0][flag]; j++)
					{
						score = atof(csv.table[j][i].c_str());
						if (score != 0.0)
						{
							if (score >= 0.0) Class[type][0]++;
							if (score >= (1.0 * Class[type][1])) Class[type][2]++;
							if (score >= (1.0 * Class[type][3])) Class[type][4]++;
						}
					}
				}

				if (type == 5 || type == 9) // 当检测到物理或政治时，计算理综或文综
				{
					float score = 0.0, score1 = 0.0, score2 = 0.0, score3 = 0.0;
					for (int j = 1; j <= Class[0][flag]; j++)
					{
						score1 = atof(csv.table[j][i].c_str()), // 获取物理或政治
						score2 = atof(csv.table[j][i + 1].c_str()), // 获取化学或地理
						score3 = atof(csv.table[j][i + 2].c_str()), // 获取生物或历史
						score = score1 + score2 + score3; // 计算理综或文综
						if (score != 0.0)
						{
							if (score >= 0.0) Class[type + 3][0]++;
							if (score >= (1.0 * Class[type + 3][1])) Class[type + 3][2]++;
							if (score >= (1.0 * Class[type + 3][3])) Class[type + 3][4]++;
						}
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
	string excelName6 = folderOutput + "\\" + name + "高" + gradeS + "年级各班理（文）科单科一本人数、本科人数及比例.csv";
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
	int Class[14][5] = {0};

	setScoreBatch(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 分析四种数据
	string typeS = " ";
	typeS = "理科";
	getData6(csv1, Class, typeS); // 分析理科总成绩
	typeS = "文科";
	getData6(csv2, Class, typeS); // 分析文科总成绩
	typeS = "艺理";
	getData6(csv3, Class, typeS); // 分析艺理总成绩
	typeS = "艺文";
	getData6(csv4, Class, typeS); // 分析艺文总成绩

	for (int i = 0; i < 13; i++)
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

	vector<string> type = { "语文","理数","文数","英语","物理","化学","生物","理综","政治","地理","历史","文综" };

	for (int i = 0; i < type.size(); i++)
	{
		excel6 << type[i] << "," << Class[i + 1][0] << "," << Class[i + 1][2] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][2]) / (1.0 *Class[i + 1][0]) << "%,";
		excel6 << Class[i + 1][0] << ",";
		excel6 << fixed << setprecision(2) << 100 * (1.0 * Class[i + 1][4]) / (1.0 *Class[i + 1][0]) << "%";
		excel6 << endl;
	}

	excel6.close();
	return true;
}