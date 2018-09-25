#include "stdafx.h"
#include "exam.h"


LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

string chooseInsert(vector<string> folder)
{
	int chooseFolder = 0;
	cout << "再次输入要选择的考试信息，输入数字为上方考试信息最前面的数字" << endl;
	cin >> chooseFolder;
	while (chooseFolder > folder.size() || chooseFolder < 1)
	{
		cout << "请输入上方已有考试信息前面的数字：" << endl;
		cin >> chooseFolder;
	}
	cout << "已选择的考试信息为：" << folder[chooseFolder - 1] << endl;
	string Folder = folder[chooseFolder - 1];
	//string csv = folder[chooseFolder - 1] + "\\理科总成绩.csv";
	//cout << ShellExecute(nullptr, _T("open"), stringToLPCWSTR(folder[chooseFolder - 1]), stringToLPCWSTR("/理科总成绩.csv"), _T(""), 0);
	/*
	int type = 0;
	cout << "请输入数字1到4其中一个，选择要分析的类型：" << endl;
	cout << "1: 理科" << endl;
	cout << "2: 文科" << endl;
	cout << "3: 艺理" << endl;
	cout << "4: 艺文" << endl;
	cin >> type;
	while (type < 1 || type > 4)
	{
		cout << "请输入正确数字，选择1到4：" << endl;
		cin >> type;
	}
	switch (type)
	{
	case (1):
		cout << "已选择理科" << endl;
		Folder += "\\理科总成绩.csv";
		return Folder;
	case (2):
		cout << "已选择文科" << endl;
		Folder += "\\文科总成绩.csv";
		return Folder;
	case (3):
		cout << "已选择艺理" << endl;
		Folder += "\\艺理总成绩.csv";
		return Folder;
	case (4):
		cout << "已选择艺文" << endl;
		Folder += "\\艺文总成绩.csv";
		return Folder;
	default:
		cout << "非法输入" << endl;
	}*/
	return Folder;
}

string chooseCreate()
{
	cout << "新建新的考试信息" << endl;
	int is = 0;
	string school;
	string name;
	int grade = 0;
	string gradeS;
	string dirName;
	string dirNameOut;
	while (!is)
	{
		cout << "输入学校名字：";
		cin >> school;
		cout << "输入考试名字：";
		cin >> name;
		while (grade < 1 || grade >3)
		{
			cout << "输入考生年级：（例如高一输入“1”；高二输入“2”；高三输入“3”）：";
			cin >> grade;
		}
		if (grade == 1) gradeS = "一";
		if (grade == 2) gradeS = "二";
		if (grade == 3) gradeS = "三";
		cout << "确定输入是否正确：" << school << name << "理（文）科高" << gradeS << "年级所有科目总成绩" << endl;
		cout << "输入1表示正确，输入0重新输入以上数据：";
		cin >> is;
		dirName = "D:\\成绩录入\\" + school + name + "理（文）科高" + gradeS + "年级所有科目总成绩";
		dirNameOut = "D:\\成绩分析\\" + school + name + "理（文）科高" + gradeS + "年级所有科目总成绩";
		if (_access(dirName.c_str(), 0) == -1 && _access(dirNameOut.c_str(), 0) == -1)
		{
			_mkdir(dirName.c_str());
			_mkdir(dirNameOut.c_str());
			cout << "新考试信息创建成功" << endl;
		}
		else
		{
			cout << "该考试信息已存在，请重新输入" << endl;
			grade = 0;
			is = 0;
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
	return dirName;
}

string chooseDelete()
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
	return "OK";
}

string chooseExam()
{
	vector<string> folder;

	cout << "已有下列考试结果信息：" << endl;

	GetAllFiles("D://成绩录入", folder);

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
	cout << "输入3：删除已有考试数据" << endl;

	int choose = 0;
	
	//while (true)
	{
		cin >> choose;
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
		else
		{
			cout << "请重新输入1到3的数字：" << endl;
		}
	}

	return " ";
}

