#include "stdafx.h"
#include "exam.h"

Csv::Csv()
{

}

Csv::Csv(const char* filename)
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

int Csv::my_split(const std::string& src, const char& delim, std::vector<std::string>& vec)
{
	int src_len = src.length();
	int find_cursor = 0;
	int read_cursor = 0;

	if (src_len <= 0) return -1;

	vec.clear();
	while (read_cursor < src_len) {

		find_cursor = src.find(delim, find_cursor);

		//1.�Ҳ����ָ���
		if (-1 == find_cursor) {
			if (read_cursor <= 0) return -1;

			//���һ���Ӵ�, src��βû�зָ���
			if (read_cursor < src_len) {
				vec.push_back(src.substr(read_cursor, src_len - read_cursor));
				return 0;
			}
		}
		//2.�������ָ��������
		else if (find_cursor == read_cursor) {
			//�ַ�����ͷΪ�ָ���, Ҳ�����Ӵ�����, �粻��Ҫ�ɼ����ж�&&(read_cursor!=0)
			vec.push_back(std::string(""));
		}
		//3.�ҵ��ָ���
		else
			vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));

		read_cursor = ++find_cursor;
		if (read_cursor == src_len) {
			//�ַ����Էָ�����β, �粻��Ҫĩβ���Ӵ�, ֱ��return
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