#include "stdafx.h"
#include "exam.h"




int my_split(const std::string& src, const char& delim,
	std::vector<std::string>& vec)
{
	int src_len = src.length();
	int find_cursor = 0;
	int read_cursor = 0;

	if (src_len <= 0) return -1;

	vec.clear();
	while (read_cursor < src_len) {

		find_cursor = src.find(delim, find_cursor);

		//1.找不到分隔符
		if (-1 == find_cursor) {
			if (read_cursor <= 0) return -1;

			//最后一个子串, src结尾没有分隔符
			if (read_cursor < src_len) {
				vec.push_back(src.substr(read_cursor, src_len - read_cursor));
				return 0;
			}
		}
		//2.有连续分隔符的情况
		else if (find_cursor == read_cursor) {
			//字符串开头为分隔符, 也按空子串处理, 如不需要可加上判断&&(read_cursor!=0)
			vec.push_back(std::string(""));
		}
		//3.找到分隔符
		else
			vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));

		read_cursor = ++find_cursor;
		if (read_cursor == src_len) {
			//字符串以分隔符结尾, 如不需要末尾空子串, 直接return
			vec.push_back(std::string(""));
			return 0;
		}
	}//end while()

	return 0;
}

void chooseExcel(string folder)
{
	cout << folder << endl;

	string name;
	int name1 = folder.find('\\') + 1;
	int name2 = folder.find('理');
	name = folder.substr(name1, name2 - name1 - 1);
	//cout << name << endl;

	int grade = 0;
	string gradeS = "";
	int grade1 = (folder.find("理（文）科高"));
	gradeS = folder.substr(grade1 + 12, 2);

	if (gradeS == "一") grade = 1;
	if (gradeS == "二") grade = 2;
	if (gradeS == "三") grade = 3;
	
	string excelnameS = "";
	int excelnumber = 1;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "请选择分析类型，选择数字生成指定文件" << endl;
	
	vector<string> excelType;

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科一本和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科总分分数段人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级各班一本人数本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级各班成绩分数段人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级各班成绩平均分和标准差";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科单科一本人数和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理科各班单科一本人数和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级文科各班单科一本人数和本科人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "高" + gradeS + "年级理（文）科各班单科成绩分数段人数及比例";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	string fileOutput = "D://成绩分析\\" + name + "理（文）科高" + gradeS + "年级所有科目总成绩";

	int type = 0;

	cin >> type;

	switch (type)
	{
	case (1) :
		//cout << folder << endl;
		getExcel1(folder, fileOutput, name, gradeS);
		break;
	case (2):
		getExcel2(folder, fileOutput, name, gradeS);
		break;
	case (3):
		getExcel3(folder, fileOutput, name, gradeS);
		break;
	default:
		break;
	}
}