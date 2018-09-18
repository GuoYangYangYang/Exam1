// Exam1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "CSV.h"
#include "exam.h"

#define APP_VERSION 1.1
#define DEFAULT_SCHOOL "国华学校"

int main()
{
	cout << "考试成绩分析系统：" << APP_VERSION << endl;

	if (!init()) exit(0);

	


	//while (1)
	{
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		string file = chooseExam();
		chooseExcel(file);
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		//system("cls");
	}/*
	*/

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
	
	
	const char * filename = (folder + "\\理科总成绩.csv").c_str();
	
	//char filename[] = "E:\\14多科成绩表理科.CSV"; //文件名
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

