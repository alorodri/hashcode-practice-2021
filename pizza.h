#ifndef _PIZZA
#define _PIZZA

#include "debug.h"

#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>

struct Pizza
{
	int index;
	std::set<std::string> uniqueIngredients;
	bool added = false;

	inline bool hasIngredient(std::string ingredient)
	{
		return uniqueIngredients.count(ingredient);
	}

	static inline std::ostringstream printPizza(Pizza& p, hashcode_debug::LEVEL l)
	{
		#if defined(_DEBUGVERBOSE)
		return std::ostringstream{}
			<< "[index."
			<< p.index
			<< "] Ingredients: "
			<< getIngredientsCommaSeparated(p.uniqueIngredients);
		#elseif defined(_DEBUGINFO)
			return std::ostringstream{};
		#else
		return std::ostringstream{};
		#endif

	}

	static inline std::string getIngredientsCommaSeparated(std::set<std::string>& ingredients)
	{
		int n = 0;
		std::ostringstream ss{};
		for (auto& ingredient : ingredients)
		{
			if (n != ingredients.size() - 1)
			{
				ss << ingredient << ", ";
			}
			else {
				ss << ingredient;
			}
			++n;
		}

		return ss.str();
	}
};

#endif