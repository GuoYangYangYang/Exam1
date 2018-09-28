#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-25
Description: 表五：XXXX高X年级各班成绩平均分和标准差
********************************************************************************/

int initClass5(vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN + 4 > Class1.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
		{
			int ClassN = Class1.size();
			while (classN + 4 > ClassN)
			{
				vector<int> classData1(3, 0);
				vector<double> classData2(3, 0.0);
				Class1.push_back(classData1);
				Class2.push_back(classData2);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

void getData5_1(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS)
{
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”
	if ((csv.getTable()[0][3].compare("科类") == 0) && (csv.getTable()[0][4].compare("班级") == 0) && (csv.getTable()[0][6].compare("总分") == 0))
	{
		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int classN = -1; // 当前学生的班级
		int type = 0; // 当前学生类型

		if (!csv.getTable().empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass5(Class1, Class2, gradeS, csv.getTable()[i][4]); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					classN += 3;
					if (!typeS.compare("理科")) type = 0;
					if (!typeS.compare("文科")) type = 1;
					if (!typeS.compare("艺理")) type = 2;
					if (!typeS.compare("艺文")) type = 3;
					if (!csv.getTable()[i][3].compare("理科")) Class1[classN][0] = 1; // 理科置为1
					else Class1[classN][0] = 0; // 文科置为false
					score = atoi(csv.getTable()[i][6].c_str()); // 获取当前学生分数
					if (score >= 0) // 学生数据有效，则参考人数加一
					{
						Class1[type][1]++;
						Class1[type][2] += score;
						Class1[classN][1]++;
						Class1[classN][2] += score;
					}
				}
			}
		}
	}
}

void getData5_2(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS)
{
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”
	if ((csv.getTable()[0][3].compare("科类") == 0) && (csv.getTable()[0][4].compare("班级") == 0) && (csv.getTable()[0][6].compare("总分") == 0))
	{
		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int classN = -1; // 当前学生的班级
		int type = 0; // 当前学生类型

		if (!csv.getTable().empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(csv.getTable()[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass5(Class1, Class2, gradeS, csv.getTable()[i][4]); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					classN += 3;
					if (!typeS.compare("理科")) type = 0;
					if (!typeS.compare("文科")) type = 1;
					if (!typeS.compare("艺理")) type = 2;
					if (!typeS.compare("艺文")) type = 3;
					score = atoi(csv.getTable()[i][6].c_str()); // 获取当前学生分数
					if (score >= 0) // 学生数据有效，则参考人数加一
					{
						Class2[type][1] += (1.0 * score - Class2[type][0]) * (1.0 * score - Class2[type][0]);
						Class2[classN][1] += (1.0 * score - Class2[classN][0]) * (1.0 * score - Class2[classN][0]);
					}
				}
			}
		}
	}
}

bool getExcel5(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName5 = folderOutput + "\\" + name + "高" + gradeS + "年级各班成绩平均分和标准差.csv";
	const char * excelNamec5 = excelName5.c_str();

	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Intput = folderIntput + "\\理科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\文科总成绩.csv";
	const char * file2 = file2Intput.c_str();
	string file3Intput = folderIntput + "\\艺理总成绩.csv";
	const char * file3 = file3Intput.c_str();
	string file4Intput = folderIntput + "\\艺文总成绩.csv";
	const char * file4 = file4Intput.c_str();

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	vector<vector<int>> Class1;
	vector<vector<double>> Class2;

	string type = " ";
	type = "理科";
	getData5_1(csv1, Class1, Class2, gradeS, type);
	type = "文科";
	getData5_1(csv2, Class1, Class2, gradeS, type);
	type = "艺理";
	getData5_1(csv3, Class1, Class2, gradeS, type);
	type = "艺文";
	getData5_1(csv4, Class1, Class2, gradeS, type);

	for (int i = 0; i < Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			Class2[i][0] = (1.0 * Class1[i][2]) / (1.0 * Class1[i][1]);
		}
	}

	type = "理科";
	getData5_2(csv1, Class1, Class2, gradeS, type);
	type = "文科";
	getData5_2(csv2, Class1, Class2, gradeS, type);
	type = "艺理";
	getData5_2(csv3, Class1, Class2, gradeS, type);
	type = "艺文";
	getData5_2(csv4, Class1, Class2, gradeS, type);

	for (int i = 0; i < Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			Class2[i][2] = sqrt((1.0 * Class2[i][1]) / (1.0 * Class1[i][1]));
		}
	}

	// 删除原分析文件，建立新的数据分析文件，并打开
	remove(excelNamec5);
	ofstream excel5;
	excel5.open(excelNamec5, std::ios::out | std::ios::app);

	if (!excel5.is_open())
	{
		cout << "创建文件出错！" << endl;
		return false;
	}

	// 初始化数据分析表
	excel5 << "类型,参考人数,平均分,标准差" << endl;

	for (int i = 0; i < Class1.size(); i++)
	{
		if (Class1[i][1] != 0)
		{
			if (i < 4)
			{
				if (i == 0) excel5 << "理科";
				if (i == 1) excel5 << "文科";
				if (i == 2) excel5 << "艺理";
				if (i == 3) excel5 << "艺文";
			}
			else
			{
				excel5 << "高" << gradeS << "（" << (i - 3) << "）";
			}
			excel5 << "," << Class1[i][1] << ",";
			excel5 << fixed << setprecision(2) << Class2[i][0] << ",";
			excel5 << fixed << setprecision(2) << Class2[i][2] << endl;
		}
	}

	excel5.close();
	return true;
}