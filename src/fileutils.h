#ifndef _FILE_UTILS
#define _FILE_UTILS

#include "debug.h"
#include "pizza.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace file_utils
{

	enum class FileName
	{
		FILE_A,
		FILE_B,
		FILE_C,
		FILE_D,
		FILE_E
	};

	inline std::vector<std::string> split(std::string& str, char csplit)
	{
		std::ostringstream oss{};
		std::vector<std::string> returnVec;
		int charNum = 0;
		for (auto c : str)
		{
			if (c == csplit)
			{
				returnVec.push_back(oss.str());
				oss.str("");
				oss.clear();
			}
			else {
				oss << c;
				if (charNum == str.length() - 1)
				{
					returnVec.push_back(oss.str());
				}
			}
			++charNum;
		}

		return returnVec;
	}

	struct FileData
	{
		static std::string filename;
		static uint32_t nPizzas;
		static uint32_t n2T;
		static uint32_t n3T;
		static uint32_t n4T;
		static uint32_t totalTeams;
		static uint32_t totalPeople;
		static std::vector<Pizza> pizzas;
	};

	void parseFile(const std::string filename);
	const std::string getFileNameStr(FileName f);
}

#endif