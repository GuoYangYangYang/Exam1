#pragma once
#include "stdafx.h"

using std::string;
using std::vector;

class Csv
{
private:
	vector <vector <string>> table;    //存储表格结构的二维vector
	int RowsCount;
	int ColumnsCount;
	int my_split(const std::string& src, const char& delim,
		std::vector<std::string>& vec);
public:
	vector <vector <string>> getTable();
	Csv(const char* filename);
	Csv();
};

bool getExcel2(string, string, string, string);
bool getExcel3(string, string, string, string);
bool getExcel4(string, string, string, string);
bool getExcel5(string, string, string, string);
bool getExcel6(string, string, string, string);
bool getExcel7(string, string, string, string);
bool getExcel8(string, string, string, string);
bool getExcel9(string, string, string, string);

class Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;
	void setFolderInput(string);
	void setFolderOutput(string);
	void setName(string);
	void setGradeString(string);

protected:

	string getFolderInput();
	string getFolderOutput();
	string getName();
	string getGradeString();

public :

	Excel();
	Excel(string folderInput, string folderOutput, string name, string gradeS);

};

class Excel1 : virtual public Excel
{
private:

	int MaxScienceScore = 750;
	int MaxArtsScore = 750;

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	void getData(const char * excelName, Csv &csv, string type, double fristBatch, double secondBatch);

public :

	Excel1(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel2 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	void getData(const char * excelName, Csv csv, string type, double fristBatch, double secondBatch);

public:

	Excel2(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();
};

class Exam
{
private:
	bool init();
	bool createDirectory(const std::string folder);
	void GetAllFiles(std::string path, vector<std::string>& files);
	string chooseExam();
	string chooseInsert(vector<string> folder);
	string chooseCreate();
	string chooseDelete();
	bool chooseExcel(string);
	bool getExcel(string, string, string, string, int number);
public :
	Exam();
	void getExam();
	static void clear();
	static bool isNum(string);
	static int inputInteger(int start);
	static int inputInteger(int begin, int end);
	static float inputFloat(float begin, float end);
	static string inputString();
};