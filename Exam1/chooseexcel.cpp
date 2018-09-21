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

void chooseExcel(string folder)
{
	cout << folder << endl;

	string name;
	int name1 = folder.find('\\') + 1;
	int name2 = folder.find('��');
	name = folder.substr(name1, name2 - name1 - 1);
	//cout << name << endl;

	int grade = 0;
	string gradeS = "";
	int grade1 = (folder.find("���ģ��Ƹ�"));
	gradeS = folder.substr(grade1 + 12, 2);

	if (gradeS == "һ") grade = 1;
	if (gradeS == "��") grade = 2;
	if (gradeS == "��") grade = 3;
	
	string excelnameS = "";
	int excelnumber = 1;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "��ѡ��������ͣ�ѡ����������ָ���ļ�" << endl;
	
	vector<string> excelType;

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ���һ���ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ����ַܷ���������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶����һ��������������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶����ɼ�����������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶����ɼ�ƽ���ֺͱ�׼��";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ��Ƶ���һ�������ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶��Ƹ��൥��һ�������ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶�ĿƸ��൥��һ�������ͱ�������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);

	cout << "---+-----------------------------------------------------------------------------------------------" << endl;
	excelnameS = name + "��" + gradeS + "�꼶���ģ��Ƹ��൥�Ƴɼ�����������������";
	cout << setw(3) << setfill(' ') << excelnumber;
	cout << "|" << excelnameS << endl;
	excelnumber++;
	excelType.push_back(excelnameS);
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	string fileOutput = "D://�ɼ�����\\" + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";

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