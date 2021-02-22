#include "algorithm.h"
#include "fileutils.h"
#include "pizza.h"

#include <iostream>
#include <thread>
#include <vector>

int main()
{
	Algorithm algorithmA;
	Algorithm algorithmB;
	Algorithm algorithmC;
	Algorithm algorithmD;
	Algorithm algorithmE;

	file_utils::parseFile(file_utils::getFileNameStr(file_utils::FileName::FILE_A));
	algorithmA.computeAlgorithm(Algorithm::PRIORIZE::THREE);
	algorithmA.writeOutput();

	file_utils::parseFile(file_utils::getFileNameStr(file_utils::FileName::FILE_B));
	algorithmB.computeAlgorithm(Algorithm::PRIORIZE::THREE);
	algorithmB.writeOutput();

	file_utils::parseFile(file_utils::getFileNameStr(file_utils::FileName::FILE_C));
	algorithmC.computeAlgorithm(Algorithm::PRIORIZE::FOUR);
	algorithmC.writeOutput();

	file_utils::parseFile(file_utils::getFileNameStr(file_utils::FileName::FILE_D));
	algorithmD.computeAlgorithm(Algorithm::PRIORIZE::FOUR);
	algorithmD.writeOutput();

	file_utils::parseFile(file_utils::getFileNameStr(file_utils::FileName::FILE_E));
	algorithmE.computeAlgorithm(Algorithm::PRIORIZE::FOUR);
	algorithmE.writeOutput();

	hashcode_debug::printBlankLines(1);
	std::cout << "Program finished. Press enter to quit";
	std::cin.get();
}