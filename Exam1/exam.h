#pragma once
#include "stdafx.h"

bool init();
bool createDirectory(const std::string folder);
void GetAllFiles(std::string path, vector<std::string>& files);
string chooseExam();
void chooseExcel(string);