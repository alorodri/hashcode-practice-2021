#include "fileutils.h"

std::string file_utils::FileData::filename;
std::vector<Pizza> file_utils::FileData::pizzas;
uint32_t file_utils::FileData::nPizzas;
uint32_t file_utils::FileData::n2T;
uint32_t file_utils::FileData::n3T;
uint32_t file_utils::FileData::n4T;
uint32_t file_utils::FileData::totalTeams;
uint32_t file_utils::FileData::totalPeople;

void file_utils::parseFile(const std::string filename)
{
	FileData::filename = filename;
	std::fstream file;
	file.open(filename, std::ios::in);
	if (!file)
	{
		hashcode_debug::errprint(
			std::ostringstream{}
			<< "File not found"
		);
	}
	else {
		std::string line;
		int lineNumber = 0;

		hashcode_debug::dbgprint(
			std::ostringstream{}
			<< "Begin parsing file "
			<< filename,
			hashcode_debug::LEVEL::INFO
		);

		while (std::getline(file, line))
		{

			if (lineNumber == 0)
			{
				std::vector<std::string> values = split(line, ' ');

				FileData::nPizzas = std::stoi(values[0].c_str());
				FileData::n2T = std::stoi(values[1].c_str());
				FileData::n3T = std::stoi(values[2].c_str());
				FileData::n4T = std::stoi(values[3].c_str());

				FileData::totalTeams =
					FileData::n2T
					+ FileData::n3T
					+ FileData::n4T;

				FileData::totalPeople =
					FileData::n2T * 2
					+ FileData::n3T * 3
					+ FileData::n4T * 4;

				FileData::pizzas.clear();
			}
			else {
				std::vector<std::string> values = split(line, ' ');

				int totalIngredientsInThisPizza = std::stoi(values[0].c_str());

				Pizza p;
				p.index = lineNumber - 1;
				for (int i = 1; i <= totalIngredientsInThisPizza; ++i)
				{
					p.uniqueIngredients.insert(values[i]);
				}

				FileData::pizzas.push_back(p);

				hashcode_debug::dbgprint(
					Pizza::printPizza(p, hashcode_debug::LEVEL::VERBOSE),
					hashcode_debug::LEVEL::VERBOSE
				);

			}

			++lineNumber;
		}

		hashcode_debug::dbgprint(
			std::ostringstream{}
			<< "File parsed. We have a total of "
			<< FileData::nPizzas
			<< " pizzas, "
			<< FileData::n2T
			<< " teams of 2 people, "
			<< FileData::n3T
			<< " teams of 3 people, "
			<< FileData::n4T
			<< " teams of 4 people, "
			<< "with a total of "
			<< FileData::totalTeams
			<< " teams and "
			<< FileData::totalPeople
			<< " people.",
			hashcode_debug::LEVEL::INFO
		);

		hashcode_debug::printBlankLines(1);
	}

	if (file)
	{
		file.close();
	}
}

const std::string file_utils::getFileNameStr(FileName f)
{
	switch (f)
	{
	case file_utils::FileName::FILE_A: return "a_example";
	case file_utils::FileName::FILE_B: return "b_little_bit_of_everything.in";
	case file_utils::FileName::FILE_C: return "c_many_ingredients.in";
	case file_utils::FileName::FILE_D: return "d_many_pizzas.in";
	case file_utils::FileName::FILE_E: return "e_many_teams.in";
	default: assert(false);
	}
}
