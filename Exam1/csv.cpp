#include "stdafx.h"
#include "exam.h"

Csv::Csv()
{

}

Csv::Csv(const char* filename)
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

int Csv::my_split(const std::string& src, const char& delim, std::vector<std::string>& vec)
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

vector <vector <string>> Csv::getTable()
{
	return table;
}