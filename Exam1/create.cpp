#include "stdafx.h"
#include "exam.h"

bool Exam::createDirectory(const std::string folder) {
	const char PATH_DELIMITER = '\\';
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