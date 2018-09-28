#include "stdafx.h"
#include "exam.h"

Excel::Excel()
{

}

Excel::Excel(string folderInput, string folderOutput, string name, string gradeS)
{
	this->folderInput = folderInput;
	this->folderOutput = folderOutput;
	this->name = name;
	this->gradeS = gradeS;
}

void Excel::setFolderInput(string folderInput)
{
	Excel().folderInput = folderInput;
}

string Excel::getFolderInput()
{
	return this->folderInput;
}

void Excel::setFolderOutput(string folderOutput)
{
	Excel().folderOutput = folderOutput;
}

string Excel::getFolderOutput()
{
	return this->folderOutput;
}

void Excel::setName(string name)
{
	Excel().name = name;
}

string Excel::getName()
{
	return this->name;
}

void Excel::setGradeString(string gradeS)
{
	Excel().gradeS = gradeS;
}

string Excel::getGradeString()
{
	return this->gradeS;
}
