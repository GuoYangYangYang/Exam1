#include "stdafx.h"
#include "exam.h"

bool Exam::getExcel(string folderInput, string folderOutput, string name, string gradeS, int number)
{
	
	Excel1* excel1;

	switch (number)
	{
	case (1):
		excel1 = new Excel1(folderInput, folderOutput, name, gradeS);
		excel1->getExcel();
		break;
	default:
		return false;
	}
	return true;
}