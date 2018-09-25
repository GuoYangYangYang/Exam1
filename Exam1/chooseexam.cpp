#include "stdafx.h"
#include "exam.h"


LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

string chooseInsert(vector<string> folder)
{
	int chooseFolder = 0;
	cout << "�ٴ�����Ҫѡ��Ŀ�����Ϣ����������Ϊ�Ϸ�������Ϣ��ǰ�������" << endl;
	cin >> chooseFolder;
	while (chooseFolder > folder.size() || chooseFolder < 1)
	{
		cout << "�������Ϸ����п�����Ϣǰ������֣�" << endl;
		cin >> chooseFolder;
	}
	cout << "��ѡ��Ŀ�����ϢΪ��" << folder[chooseFolder - 1] << endl;
	string Folder = folder[chooseFolder - 1];
	//string csv = folder[chooseFolder - 1] + "\\����ܳɼ�.csv";
	//cout << ShellExecute(nullptr, _T("open"), stringToLPCWSTR(folder[chooseFolder - 1]), stringToLPCWSTR("/����ܳɼ�.csv"), _T(""), 0);
	/*
	int type = 0;
	cout << "����������1��4����һ����ѡ��Ҫ���������ͣ�" << endl;
	cout << "1: ���" << endl;
	cout << "2: �Ŀ�" << endl;
	cout << "3: ����" << endl;
	cout << "4: ����" << endl;
	cin >> type;
	while (type < 1 || type > 4)
	{
		cout << "��������ȷ���֣�ѡ��1��4��" << endl;
		cin >> type;
	}
	switch (type)
	{
	case (1):
		cout << "��ѡ�����" << endl;
		Folder += "\\����ܳɼ�.csv";
		return Folder;
	case (2):
		cout << "��ѡ���Ŀ�" << endl;
		Folder += "\\�Ŀ��ܳɼ�.csv";
		return Folder;
	case (3):
		cout << "��ѡ������" << endl;
		Folder += "\\�����ܳɼ�.csv";
		return Folder;
	case (4):
		cout << "��ѡ������" << endl;
		Folder += "\\�����ܳɼ�.csv";
		return Folder;
	default:
		cout << "�Ƿ�����" << endl;
	}*/
	return Folder;
}

string chooseCreate()
{
	cout << "�½��µĿ�����Ϣ" << endl;
	int is = 0;
	string school;
	string name;
	int grade = 0;
	string gradeS;
	string dirName;
	string dirNameOut;
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
		dirName = "D:\\�ɼ�¼��\\" + school + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";
		dirNameOut = "D:\\�ɼ�����\\" + school + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";
		if (_access(dirName.c_str(), 0) == -1 && _access(dirNameOut.c_str(), 0) == -1)
		{
			_mkdir(dirName.c_str());
			_mkdir(dirNameOut.c_str());
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
	file1 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ѧ,����," << endl;
	file1.close();
	file2.open(dirName + "\\�Ŀ��ܳɼ�.csv", std::ios::out | std::ios::app);
	if (!file2.is_open())
	{
		cout << "�����ļ�����" << endl;
		return "ERROR";
	}
	file2 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ʷ,����," << endl;
	file2.close();
	file3.open(dirName + "\\�����ܳɼ�.csv", std::ios::out | std::ios::app);
	if (!file3.is_open())
	{
		cout << "�����ļ�����" << endl;
		return "ERROR";
	}
	file3 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ѧ,����," << endl;
	file3.close();
	file4.open(dirName + "\\�����ܳɼ�.csv", std::ios::out | std::ios::app);
	if (!file4.is_open())
	{
		cout << "�����ļ�����" << endl;
		return "ERROR";
	}
	file4 << "����,����,ѧ��,����,�༶,����,�ܷ�,����,����,Ӣ��,����,��ʷ,����," << endl;
	file4.close();
	return dirName;
}

string chooseDelete()
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
	return "OK";
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
	
	//while (true)
	{
		cin >> choose;
		if (choose == 1) {
			return chooseInsert(folder);
		}
		else if (choose == 2)
		{
			return chooseCreate();
		}
		else if (choose == 3)
		{
			return chooseDelete();
		}
		else
		{
			cout << "����������1��3�����֣�" << endl;
		}
	}

	return " ";
}

