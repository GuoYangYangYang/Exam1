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

class Exam
{
private:
	char root[1000];
	string rootS;
	bool init();
	bool createDirectory(const std::string folder);
	void GetAllFiles(std::string path, vector<std::string>& files);
	string chooseExam();
	string chooseInsert(vector<string> folder);
	string chooseCreate();
	string chooseDelete();
	bool chooseExcel(string);
	bool getExcel(string, string, string, string, int number);
public:
	Exam();
	void getExam();
	static void clear();
	static bool isNum(string);
	static int inputInteger(int start);
	static int inputInteger(int begin, int end);
	static double inputDouble(double begin, double end);
	static string inputString();
};

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

	const int MaxScore = 750;
	const int MaxScienceScore = 750;
	const int MaxArtsScore = 750;
	const int MaxChineseScore = 150;
	const int MaxMathScore = 150;
	const int MaxEnglishScore = 150;
	const int MaxPhysicsScore = 100;
	const int MaxChemistryScore = 100;
	const int MaxBiologyScore = 100;
	const int MaxScienceComprehensiveScore = 300;
	const int MaxPoliticsScore = 100;
	const int MaxHistoryScore = 100;
	const int MaxGeographyScore = 100;
	const int MaxArtsComprehensiveScore = 300;

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
	void getData(const char * excelName, Csv &csv, string type, vector<int> scoreSection);

public:

	Excel2(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel3 : virtual public Excel
{
private:

	/* 班级分数统计信息 */
	typedef struct ClassData
	{
		string className; /* 班级名称 */
		int allNumber; /* 班级参考人数 */
		int fristNumber; /* 过一本线人数 */
		int secondNumber; /* 过本科线人数 */
		bool SorA; /* 理科还是文科？ */
	} ClassData;

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	int initClass(vector<ClassData> &Class, string gradeS, string classS);
	void getData(Csv csv, vector<ClassData> &Class, string gradeS, double fristBatch, double secondBatch);

public:

	Excel3(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel4 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	int initClass(vector<vector<int>> &Class, string gradeS, string classS, int scoreSectionNumber);
	int findScoreSection(vector<int> scoreSection, int score);
	void getData(Csv csv, vector<vector<int>> &Class, string gradeS, vector<int> scoreSection);

public:

	Excel4(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel5 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	int initClass(vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string classS);
	void getData1(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS);
	void getData2(Csv csv, vector<vector<int>> &Class1, vector<vector<double>> &Class2, string gradeS, string typeS);

public:

	Excel5(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel6 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	void setScoreBatch(int Class[][5]);
	void getData(Csv csv, int Class[][5], string typeS);

public:

	Excel6(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel7 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	int initClass(vector<vector<int>> &Class, string classS);
	void setScoreBatch(vector<vector<int>> &Class);
	void getData(Csv csv, vector<vector<int>> &Class);

public:

	Excel7(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel8 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	int initClass(vector<vector<int>> &Class, string classS);
	void setScoreBatch(vector<vector<int>> &Class);
	void getData(Csv csv, vector<vector<int>> &Class);

public:

	Excel8(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};

class Excel9 : virtual public Excel
{
private:

	string folderInput;
	string folderOutput;
	string name;
	string gradeS;

	void initData();
	void setScoreBatch(vector<double> &scoreSection, double maxScore);
	int initClass(vector<vector<int>> &Class, string classS, int scoreSectionSize);
	int findScoreSection(vector<double> scoreSection, double score);
	void getData(Csv csv, vector<vector<int>> &Class, vector<double> scoreSection, string typeS);

public:

	Excel9(string folderInput, string folderOutput, string name, string gradeS);
	bool getExcel();

};
