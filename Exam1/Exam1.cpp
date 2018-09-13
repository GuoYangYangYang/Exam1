// Exam1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CSV.h"
#include "delete.h"

#define PATH_DELIMITER '\\'

using namespace std;

#define APP_VERSION 1.1
#define DEFAULT_SCHOOL "����ѧУ"

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
	if (createDirectory("D://�ɼ�¼��"))
	{
		cout << "�ɼ�¼���ʼ���ɹ�, ���ļ���ΪD���µġ��ɼ�¼�롱��" << endl;
	}
	else
	{
		cout << "�ɼ�¼���ʼ��ʧ��" << endl;
		return false;
	}
	if (createDirectory("D://�ɼ�����"))
	{
		cout << "�ɼ�������ʼ���ɹ������ļ���ΪD���µġ��ɼ���������" << endl;
	}
	else
	{
		cout << "�ɼ�������ʼ��ʧ��" << endl;
		return false;
	}
	return true;
}

void GetAllFiles(string path, vector<string>& files)
{
	long   hFile = 0;
	//�ļ���Ϣ    
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

	cout << "�������п��Խ����Ϣ��" << endl;
	
	GetAllFiles("D://�ɼ�¼��", folder);

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
		cout << "û���κο�����Ϣ�����½���" << endl;
	}
	cout << "---+-----------------------------------------------------------------------------------------------" << endl;

	cout << "����1��ѡ�����п�������" << endl;
	cout << "����2���½��µĿ�������" << endl;
	cout << "����3��ɾ�����п�������" << endl;

	int choose = 0;
	int chooseFolder = 0;
	while (true)
	{
		cin >> choose;
		if (choose == 1) {
			cout << "�ٴ�����Ҫѡ��Ŀ�����Ϣ����������Ϊ�Ϸ�������Ϣ��ǰ�������" << endl;
			cin >> chooseFolder;
			while (chooseFolder > folder.size() || chooseFolder < 1)
			{
				cout << "�������Ϸ����п�����Ϣǰ������֣�" << endl;
				cin >> chooseFolder;
			}
			cout << "��ѡ��Ŀ�����ϢΪ��" << folder[chooseFolder - 1] << endl;
			//ShellExecute(nullptr, _T("open"), _T("C:\Users\lenovo\Desktop\abc.csv"), _T(""), _T(""), SW_SHOW);

			return folder[chooseFolder - 1];
		}
		else if (choose == 2)
		{
			cout << "�½��µĿ�����Ϣ" << endl;
			int is = 0;
			string school;
			string name;
			int grade = 0;
			string gradeS;
			string dirName;
			while (!is)
			{
				cout << "����ѧУ���֣�";
				cin >> school;
				cout << "���뿼�����֣�";
				cin >> name;
				while (grade < 1 || grade >3) 
				{
					cout << "���뿼���꼶���������һ���롰1�����߶����롰2�����������롰3������";
					cin >> grade;
				}
				if (grade == 1) gradeS = "һ";
				if (grade == 2) gradeS = "��";
				if (grade == 3) gradeS = "��";
				cout << "ȷ�������Ƿ���ȷ��" << school << name << "���ģ��Ƹ�" << gradeS << "�꼶���п�Ŀ�ܳɼ�" << endl;
				cout << "����1��ʾ��ȷ������0���������������ݣ�";
				cin >> is;
				dirName = "D://�ɼ�¼��\\" + school + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";
				if (_access(dirName.c_str(), 0) == -1)
				{
					_mkdir(dirName.c_str());
					cout << "�¿�����Ϣ�����ɹ�" << endl;
				}
				else
				{
					cout << "�ÿ�����Ϣ�Ѵ��ڣ�����������" << endl;
					grade = 0;
					is = 0;
				}
			}
			ofstream file1, file2, file3, file4;
			file1.open(dirName + "\\����ܳɼ�.csv", std::ios::out | std::ios::app);
			if (!file1.is_open())
			{
				cout << "�����ļ�����" << endl;
				return "ERROR";
			}
			file1 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ѧ,����" << endl;
			file1.close();
			file2.open(dirName + "\\�Ŀ��ܳɼ�.csv", std::ios::out | std::ios::app);
			if (!file2.is_open())
			{
				cout << "�����ļ�����" << endl;
				return "ERROR";
			}
			file2 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ʷ,����" << endl;
			file2.close();
			file3.open(dirName + "\\�����ܳɼ�.csv", std::ios::out | std::ios::app);
			if (!file3.is_open())
			{
				cout << "�����ļ�����" << endl;
				return "ERROR";
			}
			file3 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ѧ,����" << endl;
			file3.close();
			file4.open(dirName + "\\�����ܳɼ�.csv", std::ios::out | std::ios::app);
			if (!file4.is_open())
			{
				cout << "�����ļ�����" << endl;
				return "ERROR";
			}
			file4 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ʷ,����" << endl;
			file4.close();
			return "OK";
		}
		else if (choose == 3)
		{
			/*
			cout << "�ٴ�����Ҫɾ���Ŀ�����Ϣ����������Ϊ�Ϸ�������Ϣ��ǰ�������" << endl;
			cin >> chooseFolder;
			while (chooseFolder > folder.size() || chooseFolder < 1)
			{
				cout << "�������Ϸ����п�����Ϣǰ������֣�" << endl;
				cin >> chooseFolder;
			}
			//cout << "��ɾ���Ŀ�����ϢΪ��" << folder[chooseFolder - 1] << endl;
			//const char * c = folder[chooseFolder - 1].c_str();
			//delete_file(c, "*");
			*/
			break;
		}
		else
		{
			cout << "����������1��3�����֣�" << endl;
		}
	}

	return " ";
}

int main()
{
	cout << "���Գɼ�����ϵͳ��" << APP_VERSION << endl;

	if (!init()) exit(0);

	chooseExam();

	/*
	//�����ļ������ 
	ofstream oFile;

	//��Ҫ������ļ�
	oFile.open("E:\\scoresheet1.csv", ios::out | ios::trunc);    // �����ͺ����׵����һ����Ҫ��excel �ļ�
	oFile << "����" << "," << "����" << "," << "�༶" << "," << "������" << endl;
	oFile << "����" << "," << "22" << "," << "1" << "," << "JIM" << endl;
	oFile << "����" << "," << "23" << "," << "3" << "," << "TOM" << endl;

	oFile.close();
	

	
	//��Ҫ������ļ�
	ifstream iFile("E:\\14��Ƴɼ������.csv");
	string   readStr((std::istreambuf_iterator<char>(iFile)), std::istreambuf_iterator<char>());
	cout << readStr.c_str() << endl;
	cout << readStr.length() << endl; 
	
	*/

	/*
	char filename[] = "E:\\14��Ƴɼ������.CSV"; //�ļ���
	Csv csv(filename);//Ԫ����ʾ����
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

