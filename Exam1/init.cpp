#include "stdafx.h"
#include "exam.h"

bool init()
{
	if (createDirectory("D://�ɼ�¼��"))
	{
		std::cout << "�ɼ�¼���ʼ���ɹ�, ���ļ���ΪD���µġ��ɼ�¼�롱��" << std::endl;
	}
	else
	{
		std::cout << "�ɼ�¼���ʼ��ʧ��" << std::endl;
		return false;
	}
	if (createDirectory("D://�ɼ�����"))
	{
		std::cout << "�ɼ�������ʼ���ɹ������ļ���ΪD���µġ��ɼ���������" << std::endl;
	}
	else
	{
		std::cout << "�ɼ�������ʼ��ʧ��" << std::endl;
		return false;
	}
	return true;
}