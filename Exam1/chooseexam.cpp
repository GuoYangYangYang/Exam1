#include "stdafx.h"
#include "exam.h"

string Exam::chooseExam()
{
	clear();

	vector<string> folder;

	cout << "现在已有下列考试结果信息：" << endl;

	GetAllFiles(rootS + "\\成绩录入", folder);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	if (folder.size())
	{
		int i = 1;
		for (auto s : folder)
		{
			cout << setw(3) << setfill(' ') << i << "| " << s << endl;
			i++;
		}
	}
	else
	{
		cout << "没有任何考试信息，请新建！" << endl;
	}
	cout << "---+-----------------------------------------------------------------------------------------------" << endl;

	cout << "输入1：选择已有考试数据" << endl;
	cout << "输入2：新建新的考试数据" << endl;
	//cout << "输入3：删除已有考试数据" << endl;

	int choose = 0;

	//while (true)
	{
		choose = inputInteger(1, 2);
		if (choose == 1) {
			return chooseInsert(folder);
		}
		else if (choose == 2)
		{
			return chooseCreate();
		}
		else if (choose == 3)
		{
			return chooseDelete();
		}
	}

	return " ";
}

string Exam::chooseInsert(vector<string> folder)
{
	int chooseFolder = 0;
	cout << "再次输入要选择的考试信息，输入数字为上方考试信息最前面的数字" << endl;
	chooseFolder = inputInteger(1, folder.size());
	// 清屏
	clear();
	if (chooseFolder == 0) return "";
	cout << "已选择的考试信息为：" << folder[chooseFolder - 1] << endl;
	string Folder = folder[chooseFolder - 1];
	return Folder;
}

string Exam::chooseCreate()
{
	// 清屏
	clear();

	cout << "新建新的考试信息" << endl;
	cout << "新建信息时，输入的名称不能带有“理”字！！！" << endl;

	int is = 0; // 数据是否有效
	string school; // 考试学校
	string name; // 考试名称
	int grade = 0; // 考试年级
	string gradeS; 
	string dirName; // 成绩录入文件夹
	string dirNameOut; // 成绩分析文件夹

	while (true)
	{
		while (!is)
		{
			cout << "输入学校名字：";
			school = inputString();

			cout << "输入考试名字：";
			name = inputString();

			cout << "输入考生年级：（例如高一输入“1”；高二输入“2”；高三输入“3”）：";
			grade = inputInteger(1, 3);

			if (grade == 1) gradeS = "一";
			if (grade == 2) gradeS = "二";
			if (grade == 3) gradeS = "三";

			cout << "确定输入是否正确：" << school << name << "理（文）科高" << gradeS << "年级所有科目总成绩" << endl;
			cout << "输入1表示正确，输入0重新输入以上数据：";
			is = inputInteger(1);
		}

		dirName = rootS + "\\成绩录入\\" + school + name + "理（文）科高" + gradeS + "年级所有科目总成绩";
		dirNameOut = rootS + "\\成绩分析\\" + school + name + "理（文）科高" + gradeS + "年级所有科目总成绩";

		if (_access(dirName.c_str(), 0) == -1 && _access(dirNameOut.c_str(), 0) == -1)
		{
			_mkdir(dirName.c_str());
			_mkdir(dirNameOut.c_str());
			cout << "新考试信息创建成功" << endl;
			break;
		}
		else
		{
			cout << "该考试信息已存在，请重新输入" << endl;
			grade = 0;
		}
	}

	ofstream file1, file2, file3, file4;

	file1.open(dirName + "\\理科总成绩.csv", std::ios::out | std::ios::app);
	if (!file1.is_open())
	{
		cout << "创建文件出错！" << endl;
		return "ERROR";
	}
	file1 << "考号,姓名,学号,科类,班级,性质,总分,语文,理数,英语,物理,化学,生物," << endl;
	file1.close();

	file2.open(dirName + "\\文科总成绩.csv", std::ios::out | std::ios::app);
	if (!file2.is_open())
	{
		cout << "创建文件出错！" << endl;
		return "ERROR";
	}
	file2 << "考号,姓名,学号,科类,班级,性质,总分,语文,文数,英语,政治,历史,地理," << endl;
	file2.close();

	file3.open(dirName + "\\艺理总成绩.csv", std::ios::out | std::ios::app);
	if (!file3.is_open())
	{
		cout << "创建文件出错！" << endl;
		return "ERROR";
	}
	file3 << "考号,姓名,学号,科类,班级,性质,总分,语文,理数,英语,物理,化学,生物," << endl;
	file3.close();

	file4.open(dirName + "\\艺文总成绩.csv", std::ios::out | std::ios::app);
	if (!file4.is_open())
	{
		cout << "创建文件出错！" << endl;
		return "ERROR";
	}
	file4 << "考号,姓名,学号,科类,班级,性质,总分,语文,文数,英语,政治,历史,地理," << endl;
	file4.close();

	Exam().clear();
	return dirName;
}

string Exam::chooseDelete()
{
	/*
	cout << "再次输入要删除的考试信息，输入数字为上方考试信息最前面的数字" << endl;
	cin >> chooseFolder;
	while (chooseFolder > folder.size() || chooseFolder < 1)
	{
	cout << "请输入上方已有考试信息前面的数字：" << endl;
	cin >> chooseFolder;
	}
	//cout << "已删除的考试信息为：" << folder[chooseFolder - 1] << endl;
	//const char * c = folder[chooseFolder - 1].c_str();
	//delete_file(c, "*");
	*/
	return NULL;
}



