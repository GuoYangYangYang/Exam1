#pragma once
#include "stdafx.h"

using std::string;
using std::vector;

bool init();
bool createDirectory(const std::string folder);
void GetAllFiles(std::string path, vector<std::string>& files);

string chooseExam();
void chooseExcel(string);

int my_split(const std::string& src, const char& delim,
	std::vector<std::string>& vec);

class Csv
{
public:
	vector <vector <string>> table;    //存储表格结构的二维vector
	int RowsCount;
	int ColumnsCount;
	Csv(const char* filename)
	{
		FILE *fp;
		char StrLine[1024];             //每行最大读取的字符数
		ColumnsCount = 13;
		if ((fp = fopen(filename, "r")) == NULL) //判断文件是否存在及可读
		{

		}
		vector <vector<string>> map;
		while (!feof(fp))
		{
			vector <string> row;
			fgets(StrLine, 1024, fp);  //读取一行
									   //每一行根据逗号再进行分割
			const char * split = ",";

			my_split(StrLine, ',', row);

			map.push_back(row);    //每一行row加入map中
		}
		RowsCount = map.size();
		table = map;

	};

};

bool getExcel1(string, string, string, string);
bool getExcel1(string, string, string, string);