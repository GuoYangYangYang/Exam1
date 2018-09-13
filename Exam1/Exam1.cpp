// Exam1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CSV.h"
#include "delete.h"

#define PATH_DELIMITER '\\'

using namespace std;

#define APP_VERSION 1.1
#define DEFAULT_SCHOOL "国华学校"

bool createDirectory(const std::string folder) {
	std::string folder_builder;
	std::string sub;
	sub.reserve(folder.size());
	for (auto it = folder.begin(); it != folder.end(); ++it)
	{
		const char c = *it;
		sub.push_back(c);
		if (c == PATH_DELIMITER || it == folder.end() - 1)
		{
			folder_builder.append(sub);
			if (0 != ::_access(folder_builder.c_str(), 0))
			{
				// this folder not exist
				if (0 != ::_mkdir(folder_builder.c_str()))
				{
					// create failed
					return false;
				}
			}
			sub.clear();
		}
	}
	return true;
}

bool init()
{
	if (createDirectory("D://成绩录入"))
	{
		cout << "成绩录入初始化成功, 此文件夹为D盘下的“成绩录入”。" << endl;
	}
	else
	{
		cout << "成绩录入初始化失败" << endl;
		return false;
	}
	if (createDirectory("D://成绩分析"))
	{
		cout << "成绩分析初始化成功，此文件夹为D盘下的“成绩分析”。" << endl;
	}
	else
	{
		cout << "成绩分析初始化失败" << endl;
		return false;
	}
	return true;
}

void GetAllFiles(string path, vector<string>& files)
{
	long   hFile = 0;
	//文件信息    
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					//GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

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
	int chooseFolder = 0;
	while (true)
	{
		cin >> choose;
		if (choose == 1) {
			cout << "再次输入要选择的考试信息，输入数字为上方考试信息最前面的数字" << endl;
			cin >> chooseFolder;
			while (chooseFolder > folder.size() || chooseFolder < 1)
			{
				cout << "请输入上方已有考试信息前面的数字：" << endl;
				cin >> chooseFolder;
			}
			cout << "已选择的考试信息为：" << folder[chooseFolder - 1] << endl;
			//ShellExecute(nullptr, _T("open"), _T("C:\Users\lenovo\Desktop\abc.csv"), _T(""), _T(""), SW_SHOW);

			return folder[chooseFolder - 1];
		}
		else if (choose == 2)
		{
			cout << "新建新的考试信息" << endl;
			int is = 0;
			string school;
			string name;
			int grade = 0;
			string gradeS;
			string dirName;
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
				dirName = "D://成绩录入\\" + school + name + "理（文）科高" + gradeS + "年级所有科目总成绩";
				if (_access(dirName.c_str(), 0) == -1)
				{
					_mkdir(dirName.c_str());
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
			file1 << "考号,姓名,学号,科类,班级,性质,总分,语文,理数,英语,物理,化学,生物" << endl;
			file1.close();
			file2.open(dirName + "\\文科总成绩.csv", std::ios::out | std::ios::app);
			if (!file2.is_open())
			{
				cout << "创建文件出错！" << endl;
				return "ERROR";
			}
			file2 << "考号,姓名,学号,科类,班级,性质,总分,语文,文数,英语,政治,历史,地理" << endl;
			file2.close();
			file3.open(dirName + "\\艺理总成绩.csv", std::ios::out | std::ios::app);
			if (!file3.is_open())
			{
				cout << "创建文件出错！" << endl;
				return "ERROR";
			}
			file3 << "考号,姓名,学号,科类,班级,性质,总分,语文,理数,英语,物理,化学,生物" << endl;
			file3.close();
			file4.open(dirName + "\\艺文总成绩.csv", std::ios::out | std::ios::app);
			if (!file4.is_open())
			{
				cout << "创建文件出错！" << endl;
				return "ERROR";
			}
			file4 << "考号,姓名,学号,科类,班级,性质,总分,语文,文数,英语,政治,历史,地理" << endl;
			file4.close();
			return "OK";
		}
		else if (choose == 3)
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
			break;
		}
		else
		{
			cout << "请重新输入1到3的数字：" << endl;
		}
	}

	return " ";
}

int main()
{
	cout << "考试成绩分析系统：" << APP_VERSION << endl;

	if (!init()) exit(0);

	chooseExam();

	/*
	//定义文件输出流 
	ofstream oFile;

	//打开要输出的文件
	oFile.open("E:\\scoresheet1.csv", ios::out | ios::trunc);    // 这样就很容易的输出一个需要的excel 文件
	oFile << "姓名" << "," << "年龄" << "," << "班级" << "," << "班主任" << endl;
	oFile << "张三" << "," << "22" << "," << "1" << "," << "JIM" << endl;
	oFile << "李四" << "," << "23" << "," << "3" << "," << "TOM" << endl;

	oFile.close();
	

	
	//打开要输出的文件
	ifstream iFile("E:\\14多科成绩表理科.csv");
	string   readStr((std::istreambuf_iterator<char>(iFile)), std::istreambuf_iterator<char>());
	cout << readStr.c_str() << endl;
	cout << readStr.length() << endl; 
	
	*/

	/*
	char filename[] = "E:\\14多科成绩表理科.CSV"; //文件名
	Csv csv(filename);//元素显示测试
		for (auto it1 = 0; it1 != csv.table.size(); ++it1)
		{
			for (auto it2 = 0; it2 != csv.table[it1].size(); ++it2)
			{
				cout << setw(9) << setfill(' ') << csv.table[it1][it2];
			}
			cout << endl;
		}
	*/

	system("pause");
	return 0;
}

