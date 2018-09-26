#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-26
Description: 表七：XXXX高X年级理科各班单科一本人数、本科人数及比例
********************************************************************************/

void setScoreBatch7(vector<vector<int>> &Class)
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
		vector<string> name = { "语文","理数","英语","物理","化学","生物","理综" };
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
		Class[0][flag] = firstBatch;
		Class[0][flag] = secondBatch;
	}
}

int initClass7(vector<vector<int>> &Class, string classS)
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

void getData7(Csv csv, vector<vector<int>> &Class, string gradeS, string typeS)
{
	// 检测原始数据表格第三列是否为“科类”，第四列是否为“班级”和第六列是否为“总分”。。。。。。
	if ((csv.table[0][3].compare("科类") == 0) && 
		(csv.table[0][4].compare("班级") == 0) && 
		(csv.table[0][6].compare("总分") == 0) &&
		(csv.table[0][7].compare("语文") == 0) &&
		(csv.table[0][8].compare("数学") == 0) &&
		(csv.table[0][9].compare("英语") == 0) &&
		(csv.table[0][10].compare("物理") == 0) &&
		(csv.table[0][11].compare("化学") == 0) &&
		(csv.table[0][12].compare("生物") == 0)
		)
	{
		int i = 1; // 行数
		int classN = -1; // 当前学生的班级
		int score[8] = { 0 };

		if (!csv.table.empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (isNum(csv.table[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass7(Class, csv.table[i][4]); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					for (int j = 0; j < 7; j++)
					{
						score[j] = atof(csv.table[i][j + 6].c_str()); // 获取当前学生分数
					}
					if (score[0] >= 0) Class[classN][0]++; // 学生数据有效，则参考人数加一
					for (int j = 1; j < 7; j++)
					{
						if (score[j] > Class[0][2 * j - 1]) Class[j][2 * j - 1]++;
						if (score[j] > Class[0][2 * j]) Class[j][2 * j]++;
					}
				}
			}
		}
	}
}

bool getExcel7(string folderIntput, string folderOutput, string name, string gradeS)
{
	// 数据分析输出文件的绝对路径
	string excelName7 = folderOutput + "\\" + name + "高" + gradeS + "年级理科各班单科一本人数、本科人数及比例.csv";
	const char * excelNamec7 = excelName7.c_str();

	// 原始输入数据文件的绝对路径，有两个，分别代表理科，艺理
	string file1Intput = folderIntput + "\\理科总成绩.csv";
	const char * file1 = file1Intput.c_str();
	string file2Intput = folderIntput + "\\艺理总成绩.csv";
	const char * file2 = file2Intput.c_str();

	// 班级信息
	vector<vector<int>> Class;

	setScoreBatch7(Class);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);

	// 分析四种数据
	string typeS = " ";
	typeS = "理科";
	//getData7(csv1, Class, typeS); // 分析理科总成绩
	typeS = "艺理";
	//getData7(csv3, Class, typeS); // 分析艺理总成绩

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
	excel7 << ",,语,文,理,数,英,语,物,理,化,学,生,物,理,综," << endl;
	excel7 << ",参考人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数,一本人数,本科人数," << endl;




	excel7.close();
	return true;
	return true;
}
