#include "stdafx.h"
#include "exam.h"

string Exam::chooseExam()
{
	clear();

	vector<string> folder;

	cout << "�����������п��Խ����Ϣ��" << endl;

	GetAllFiles(rootS + "\\�ɼ�¼��", folder);

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
	//cout << "����3��ɾ�����п�������" << endl;

	int choose = 0;

	//while (true)
	{
		choose = inputInteger(1, 2);
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
	}

	return " ";
}

string Exam::chooseInsert(vector<string> folder)
{
	int chooseFolder = 0;
	cout << "�ٴ�����Ҫѡ��Ŀ�����Ϣ����������Ϊ�Ϸ�������Ϣ��ǰ�������" << endl;
	chooseFolder = inputInteger(1, folder.size());
	// ����
	clear();
	if (chooseFolder == 0) return "";
	cout << "��ѡ��Ŀ�����ϢΪ��" << folder[chooseFolder - 1] << endl;
	string Folder = folder[chooseFolder - 1];
	return Folder;
}

string Exam::chooseCreate()
{
	// ����
	clear();

	cout << "�½��µĿ�����Ϣ" << endl;
	cout << "�½���Ϣʱ����������Ʋ��ܴ��С����֣�����" << endl;

	int is = 0; // �����Ƿ���Ч
	string school; // ����ѧУ
	string name; // ��������
	int grade = 0; // �����꼶
	string gradeS; 
	string dirName; // �ɼ�¼���ļ���
	string dirNameOut; // �ɼ������ļ���

	while (true)
	{
		while (!is)
		{
			cout << "����ѧУ���֣�";
			school = inputString();

			cout << "���뿼�����֣�";
			name = inputString();

			cout << "���뿼���꼶���������һ���롰1�����߶����롰2�����������롰3������";
			grade = inputInteger(1, 3);

			if (grade == 1) gradeS = "һ";
			if (grade == 2) gradeS = "��";
			if (grade == 3) gradeS = "��";

			cout << "ȷ�������Ƿ���ȷ��" << school << name << "���ģ��Ƹ�" << gradeS << "�꼶���п�Ŀ�ܳɼ�" << endl;
			cout << "����1��ʾ��ȷ������0���������������ݣ�";
			is = inputInteger(1);
		}

		dirName = rootS + "\\�ɼ�¼��\\" + school + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";
		dirNameOut = rootS + "\\�ɼ�����\\" + school + name + "���ģ��Ƹ�" + gradeS + "�꼶���п�Ŀ�ܳɼ�";

		if (_access(dirName.c_str(), 0) == -1 && _access(dirNameOut.c_str(), 0) == -1)
		{
			_mkdir(dirName.c_str());
			_mkdir(dirNameOut.c_str());
			cout << "�¿�����Ϣ�����ɹ�" << endl;
			break;
		}
		else
		{
			cout << "�ÿ�����Ϣ�Ѵ��ڣ�����������" << endl;
			grade = 0;
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

	Exam().clear();
	return dirName;
}

string Exam::chooseDelete()
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
	return NULL;
}



