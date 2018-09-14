#include "stdafx.h"
#include "exam.h"

bool init()
{
	if (createDirectory("D://成绩录入"))
	{
		std::cout << "成绩录入初始化成功, 此文件夹为D盘下的“成绩录入”。" << std::endl;
	}
	else
	{
		std::cout << "成绩录入初始化失败" << std::endl;
		return false;
	}
	if (createDirectory("D://成绩分析"))
	{
		std::cout << "成绩分析初始化成功，此文件夹为D盘下的“成绩分析”。" << std::endl;
	}
	else
	{
		std::cout << "成绩分析初始化失败" << std::endl;
		return false;
	}
	return true;
}