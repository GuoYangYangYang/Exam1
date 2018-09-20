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
	vector <vector <string>> table;    //�洢���ṹ�Ķ�άvector
	int RowsCount;
	int ColumnsCount;
	Csv(const char* filename)
	{
		FILE *fp;
		char StrLine[1024];             //ÿ������ȡ���ַ���
		ColumnsCount = 13;
		if ((fp = fopen(filename, "r")) == NULL) //�ж��ļ��Ƿ���ڼ��ɶ�
		{

		}
		vector <vector<string>> map;
		while (!feof(fp))
		{
			vector <string> row;
			fgets(StrLine, 1024, fp);  //��ȡһ��
									   //ÿһ�и��ݶ����ٽ��зָ�
			const char * split = ",";

			my_split(StrLine, ',', row);

			map.push_back(row);    //ÿһ��row����map��
		}
		RowsCount = map.size();
		table = map;

	};

};

bool getExcel1(string, string, string, string);
bool getExcel1(string, string, string, string);