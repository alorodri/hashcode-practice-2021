#ifndef _PROBLEM_ALGORITHM
#define _PROBLEM_ALGORITHM

#include "fileutils.h"
#include "pizza.h"

#include <algorithm>
#include <vector>

constexpr int MAX_ITERATIONS = 10000;

namespace algorithm
{
	struct Resolution
	{
		std::vector<Pizza> pizzasFor2;
		std::vector<Pizza> pizzasFor3;
		std::vector<Pizza> pizzasFor4;
	};
}

class Algorithm
{
public:
	enum class PRIORIZE { TWO, THREE, FOUR };
	void computeAlgorithm(PRIORIZE prio);
	void writeOutput();
private:
	int maxRepeatedIngredients = 0;
	int algorithmIteration = 0;
	int maxPizzas = 0;
	int resolvedPizzas = 0;
	bool team2Fullfilled();
	bool team3Fullfilled();
	bool team4Fullfilled();
	bool teamsAreFullfilledOfPizzas();
	void backInsertAllPizzas(std::vector<Pizza>& all, std::vector<Pizza>& chosen);
	void addPizzaToChosenPizzas(std::vector<Pizza>& pizzas, Pizza& p) const;
	bool insertFromPrio(PRIORIZE prio, std::vector<Pizza>& chosenPizzas);

	algorithm::Resolution resolution;
};

#endif