#include "stdafx.h"
#include "exam.h"

bool Exam::getExcel(string folderInput, string folderOutput, string name, string gradeS, int number)
{
	
	Excel1* excel1;
	Excel2* excel2;
	Excel3* excel3;
	Excel4* excel4;
	Excel5* excel5;
	Excel6* excel6;
	Excel7* excel7;
	Excel8* excel8;
	Excel9* excel9;

	switch (number)
	{
	case (1):
		excel1 = new Excel1(folderInput, folderOutput, name, gradeS);
		excel1->getExcel();
		break;
	case (2):
		excel2 = new Excel2(folderInput, folderOutput, name, gradeS);
		excel2->getExcel();
		break;
	case (3):
		excel3 = new Excel3(folderInput, folderOutput, name, gradeS);
		excel3->getExcel();
		break;
	case (4):
		excel4 = new Excel4(folderInput, folderOutput, name, gradeS);
		excel4->getExcel();
		break;
	case (5):
		excel5 = new Excel5(folderInput, folderOutput, name, gradeS);
		excel5->getExcel();
		break;
	case (6):
		excel6 = new Excel6(folderInput, folderOutput, name, gradeS);
		excel6->getExcel();
		break;
	case (7):
		excel7 = new Excel7(folderInput, folderOutput, name, gradeS);
		excel7->getExcel();
		break;
	case (8):
		excel8 = new Excel8(folderInput, folderOutput, name, gradeS);
		excel8->getExcel();
		break;
	case (9):
		excel9 = new Excel9(folderInput, folderOutput, name, gradeS);
		excel9->getExcel();
		break;
	default:
		return false;
	}
	return true;
}