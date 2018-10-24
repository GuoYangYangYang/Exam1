#include "stdafx.h"
#include "exam.h"

/********************************************************************************
copyright: hust
Author: 果羊羊
Last Date: 2018-9-20
Description: 表三：XXXX高X年级各班一本人数与本科人数及比例
********************************************************************************/

Excel3::Excel3(string folderInput, string folderOutput, string name, string gradeS)
	: Excel(folderInput, folderOutput, name, gradeS)
{
	initData();
}

void Excel3::initData()
{
	this->folderInput = getFolderInput();
	this->folderOutput = getFolderOutput();
	this->name = getName();
	this->gradeS = getGradeString();
}

/********************************************************************************
Function: getExcel3
Description: 根据指定的原始数据表生成分析表：XXXX高X年级各班一本人数与本科人数及比例
Calls: chooseExcel
Table Accessed:
1. 理科总成绩.csv
2. 文科总成绩.csv
3. 艺理总成绩.csv
4. 艺文总成绩.csv
Table Updated: XXXX高X年级各班一本人数与本科人数及比例
Input:
1. string folderInput: 原始数据所在的文件夹的绝对地址
2. string folderOutput：分析数据所在的文件夹的绝对地址
3. string name: 此次考试的名字或者称号
4. string gradeS: 参考学生的年级
Output: XXXX高X年级理（文）科总分分数段人数及比例
Return: true代表数据分析成功，false则代表失败
Others: null
********************************************************************************/
bool Excel3::getExcel()
{
	Exam().clear();

	// 数据分析输出文件的绝对路径
	string excelName3 = folderOutput + "\\" + "表三：" + name + "高" + gradeS + "年级各班一本人数与本科人数及比例.csv";
	const char * excelNamec3 = excelName3.c_str();

	// 原始输入数据文件的绝对路径，有四个，分别代表理科，文科，艺理，艺文
	string file1Input = folderInput + "\\理科总成绩.csv";
	const char * file1 = file1Input.c_str();
	string file2Input = folderInput + "\\文科总成绩.csv";
	const char * file2 = file2Input.c_str();
	string file3Input = folderInput + "\\艺理总成绩.csv";
	const char * file3 = file3Input.c_str();
	string file4Input = folderInput + "\\艺文总成绩.csv";
	const char * file4 = file4Input.c_str();

	int scienceFristBatch = 512; // 理科一本分数线
	int scienceSecondBatch = 375; // 理科本科分数线
	int artsFristBatch = 561; // 文科一本分数线
	int artsSecondBatch = 441; // 文科本科分数线

							   // 输入分数线
	cout << "请输入一本线（理科）:";
	scienceFristBatch = Exam().inputInteger(0, MaxScienceScore);
	cout << "请输入本科线（理科）:";
	scienceSecondBatch = Exam().inputInteger(0, scienceFristBatch - 1);
	cout << "请输入一本线（文科）:";
	artsFristBatch = Exam().inputInteger(0, MaxArtsScore);
	cout << "请输入本科线（文科）:";
	artsSecondBatch = Exam().inputInteger(0, artsFristBatch - 1);

	Exam().clear();

	// 显示分数线
	cout << "一本线（理科）：" << scienceFristBatch << endl;
	cout << "本科线（理科）：" << scienceSecondBatch << endl;
	cout << "一本线（文科）：" << artsFristBatch << endl;
	cout << "本科线（文科）：" << artsSecondBatch << endl;

	cout << "输入1继续。。。" << endl;
	while (Exam().inputInteger(1) != 1);

	// 从原来的四个表读取所有学生数据到内存中，并建立相应的Csv对象
	Csv csv1(file1);
	Csv csv2(file2);
	Csv csv3(file3);
	Csv csv4(file4);

	// 班级信息
	vector<ClassData> Class;

	// 分析四种数据
	getData(csv1, Class, gradeS, scienceFristBatch, scienceSecondBatch); // 分析理科总成绩
	getData(csv2, Class, gradeS, artsFristBatch, artsSecondBatch); // 分析文科总成绩
	getData(csv3, Class, gradeS, scienceFristBatch, scienceSecondBatch); // 分析理科总成绩
	getData(csv4, Class, gradeS, artsFristBatch, artsSecondBatch); // 分析文科总成绩

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

	// 从临时数据分析表中输出数据到csv表中
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

	// 最后输出一本理科文科线和本科理科文科线
	excel3 << endl;
	excel3 << "注,一本线,本科线" << endl;
	excel3 << "理科," << scienceFristBatch << "," << scienceSecondBatch << endl;
	excel3 << "文科," << artsFristBatch << "," << artsSecondBatch << endl;

	excel3.close();

	Exam().clear();
	cout << "已生成文件，地址如下，请在我的电脑中打开文件，按1继续：" << endl;
	cout << excelNamec3 << endl;
	while (Exam().inputInteger(1) != 1);

	return true;
}

/********************************************************************************
Function: initClass3
Description: 检测班级信息是否存在，若不存在则初始化班级信息
Calls: getData3
Table Accessed: null
Table Updated: null
Input:
1. vector<ClassData> &Class: 数据统计表
2. string gradeS: 学生年级
3. string classS: 学生班级
Output: 在Class生成一行班级初始数据
Return: 班级号码
Others: null
********************************************************************************/
int Excel3::initClass(vector<ClassData> &Class, string gradeS, string classS)
{
	classS = classS.substr(2, 2);
	if (Exam().isNum(classS)) // 检测班级号码是否合法
	{
		int classN = atoi(classS.c_str()); // 获取班级号码
		if (classN > (int)Class.size()) // 若班级号码超过现有数据表的行数，则进行初始化，直到班级号码等于数据表最大行数
		{
			int ClassN = Class.size();
			while (classN > ClassN)
			{
				string className = "高" + gradeS + "（";
				className += to_string(ClassN + 1);
				className += "）";
				ClassData classNew = {className, 0, 0, 0, true}; // 初始化数据表，默认为“理科”
				Class.push_back(classNew);
				ClassN++;
			}
		}
		return classN;
	}
	else return -1;
}

/********************************************************************************
Function: getData3
Description: 分析当前表中所有数据，统计参考人数，一本人数和本科人数
Calls: getExcel3
Table Accessed: null
Table Updated: null
Input:
		1. Csv csv: 已经处理好的Csv对象，内含原始数据表table
		2. vector<ClassData> &Class: 临时数据分析表
		3. double fristBatch: 一本线分数
		4. double secondBatch: 本科线分数
Output: 将各班参考人数，一本人数和本科人数统计到临时数据分析表中
Return: null
Others: null
********************************************************************************/
void Excel3::getData(Csv csv, vector<ClassData> &Class, string gradeS, double fristBatch, double secondBatch)
{
	auto table = csv.getTable();
	// 检测原始数据表格第四列是否为“班级”和第六列是否为“总分”
	if ((table[0][3].compare("科类") == 0) && (table[0][4].compare("班级") == 0) && (table[0][6].compare("总分") == 0))
	{
		int i = 1; // 行数
		int score = -1; // 当前学生的分数
		int classN = -1; // 当前学生的班级

		if (!table.empty()) // 如果原始数据表格不为空
		{
			for (i = 1; (Exam().isNum(table[i][6])); i++) // 当行第六列的数据为数字时
			{
				classN = initClass(Class, gradeS, table[i][4]); // 获取班级号码，若数据表中不存在则进行初始化
				if (classN != -1)
				{
					if (!table[i][3].compare("理科")) Class[classN - 1].SorA = true; // 理科置为true
					else Class[classN - 1].SorA = false; // 文科置为false
					score = (int)ceill(atoi(table[i][6].c_str())); // 获取当前学生分数
					if (score >= 0) Class[classN - 1].allNumber++; // 学生数据有效，则参考人数加一
					if (score >= secondBatch) Class[classN - 1].secondNumber++; // 成绩达到本科线，则本科人数加一
					if (score >= fristBatch) Class[classN - 1].fristNumber++; // 成绩达到一本线，则一本人数加一
				}
			}
		}
	}
}