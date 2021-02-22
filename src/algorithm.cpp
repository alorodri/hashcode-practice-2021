#include "algorithm.h"

void Algorithm::computeAlgorithm(PRIORIZE prio)
{

	std::sort(file_utils::FileData::pizzas.begin(),
		file_utils::FileData::pizzas.end(),
		[](Pizza& p1, Pizza& p2) {
			return p1.uniqueIngredients.size() > p2.uniqueIngredients.size();
		}
	);

	// we define this there, because not always we'll want to empty the list
	std::vector<Pizza> chosenPizzas;
	while (algorithmIteration < MAX_ITERATIONS && !teamsAreFullfilledOfPizzas())
	{
		// this pizzas could be discarded, we don't add them for any team
		// at the moment we find one
		bool pizzasBeenChosen = false;
		for (Pizza& pizza : file_utils::FileData::pizzas)
		{
			int repeatedIngredientsInChosen = 0;

			if (pizza.added)
			{
				// pizzas added to any team
				continue;
			}

			if (chosenPizzas.size() == 0)
			{
				// if we don't have any other pizzas chosen, we add this
				// automatically
				addPizzaToChosenPizzas(chosenPizzas, pizza);
				continue;
			}
			else {

				for (Pizza& chosenPizza : chosenPizzas)
				{

					for (std::string ingredient : chosenPizza.uniqueIngredients)
					{

						if (pizza.hasIngredient(ingredient))
						{
							++repeatedIngredientsInChosen;

							if (maxRepeatedIngredients >= repeatedIngredientsInChosen)
							{
								goto next_pizza;
							}
						}

					}

				}

				// if we've seen all the pizzas and algorithm arrived there
				// we have to add the pizza to the chosen pizzas, because
				// the pizza hasn't too much repeated ingredients
				addPizzaToChosenPizzas(chosenPizzas, pizza);

				bool pizzasBeenChosen = insertFromPrio(prio, chosenPizzas);
				if (pizzasBeenChosen)
				{
					maxRepeatedIngredients = 0;
					goto next_iteration;
				}

				// old algorithm without prios
				/*if (!team4Fullfilled() && chosenPizzas.size() == 4)
				{
					backInsertAllPizzas(resolution.pizzasFor4, chosenPizzas);
					pizzasBeenChosen = true;
					goto next_iteration;
				}
				else if (team4Fullfilled() && !team3Fullfilled() && chosenPizzas.size() == 3)
				{
					backInsertAllPizzas(resolution.pizzasFor3, chosenPizzas);
					pizzasBeenChosen = true;
					goto next_iteration;
				}
				else if (team4Fullfilled() && team3Fullfilled() && !team2Fullfilled() && chosenPizzas.size() == 2)
				{
					backInsertAllPizzas(resolution.pizzasFor2, chosenPizzas);
					pizzasBeenChosen = true;
					goto next_iteration;
				}*/

			}

		next_pizza:;

		}

		// if we ended iterations and we have more than 2 pizzas to send
		// to any group, we send them
		if (!team2Fullfilled() && chosenPizzas.size() == 2)
		{
			backInsertAllPizzas(resolution.pizzasFor2, chosenPizzas);
			pizzasBeenChosen = true;
		}
		else if (!team3Fullfilled() && chosenPizzas.size() == 3)
		{
			backInsertAllPizzas(resolution.pizzasFor3, chosenPizzas);
			pizzasBeenChosen = true;
		}
		else if (!team4Fullfilled() && chosenPizzas.size() == 4)
		{
			backInsertAllPizzas(resolution.pizzasFor4, chosenPizzas);
			pizzasBeenChosen = true;
		}

		if (!pizzasBeenChosen)
		{
			++maxRepeatedIngredients;
		}

	next_iteration:
		pizzasBeenChosen = false;
		++algorithmIteration;
	}
}

bool Algorithm::insertFromPrio(PRIORIZE prio, std::vector<Pizza>& chosenPizzas)
{
	switch (prio)
	{
	case PRIORIZE::TWO:
		if (!team2Fullfilled() && chosenPizzas.size() == 2)
		{
			backInsertAllPizzas(resolution.pizzasFor2, chosenPizzas);
			return true;
		}
	case PRIORIZE::THREE:
		if (!team3Fullfilled() && chosenPizzas.size() == 3)
		{
			backInsertAllPizzas(resolution.pizzasFor3, chosenPizzas);
			return true;
		}
	case PRIORIZE::FOUR:
		if (!team4Fullfilled() && chosenPizzas.size() == 4)
		{
			backInsertAllPizzas(resolution.pizzasFor4, chosenPizzas);
			return true;
		}
		else if (team4Fullfilled() && !team3Fullfilled() && chosenPizzas.size() == 3)
		{
			backInsertAllPizzas(resolution.pizzasFor3, chosenPizzas);
			return true;
		}
		else if (team4Fullfilled() && team3Fullfilled() && !team2Fullfilled() && chosenPizzas.size() == 2)
		{
			backInsertAllPizzas(resolution.pizzasFor2, chosenPizzas);
			return true;
		}
	default: return false;
	}
}

void Algorithm::backInsertAllPizzas(std::vector<Pizza>& all, std::vector<Pizza>& chosen)
{
	for (Pizza& p : chosen)
	{
		all.push_back(p);
	}
	chosen.clear();
}

void Algorithm::writeOutput()
{
	std::fstream file;
	file.open(file_utils::FileData::filename + ".out", std::ios::out);
	if (!file)
	{
		hashcode_debug::errprint(
			std::ostringstream{}
			<< "File not found"
		);
	}
	else {
		// first line file
		file << resolution.pizzasFor2.size() / 2 + resolution.pizzasFor3.size() / 3 + resolution.pizzasFor4.size() / 4 << "\n";
		int counter = 0;
		for (Pizza& p : resolution.pizzasFor2)
		{
			if (counter == 0)
			{
				file << 2;
			}

			file << " ";
			file << p.index;
			++counter;

			if (counter == 2)
			{
				counter = 0;
				file << "\n";
			}
		}

		for (Pizza& p : resolution.pizzasFor3)
		{
			if (counter == 0)
			{
				file << 3;
			}

			file << " ";
			file << p.index;
			++counter;

			if (counter == 3)
			{
				counter = 0;
				file << "\n";
			}
		}

		for (Pizza& p : resolution.pizzasFor4)
		{
			if (counter == 0)
			{
				file << 4;
			}

			file << " ";
			file << p.index;
			++counter;

			if (counter == 4)
			{
				counter = 0;
				file << "\n";
			}
		}
		file.close();
	}
}

void Algorithm::addPizzaToChosenPizzas(std::vector<Pizza>& pizzas, Pizza& p) const
{
	pizzas.push_back(p);
	p.added = true;
}

bool Algorithm::teamsAreFullfilledOfPizzas()
{
	return team2Fullfilled() && team3Fullfilled() && team4Fullfilled();
}

bool Algorithm::team2Fullfilled()
{
	return resolution.pizzasFor2.size() >= file_utils::FileData::n2T * 2;
}

bool Algorithm::team3Fullfilled()
{
	return resolution.pizzasFor3.size() >= file_utils::FileData::n3T * 3;
}

bool Algorithm::team4Fullfilled()
{
	return resolution.pizzasFor4.size() >= file_utils::FileData::n4T * 4;
}