#include "CocktailSimulator.h"
using namespace std;

void CocktailSimulator::makeCocktail(Cocktail *cocktail)
{
	cout << "== CocktailMix | Making Cocktail ==" << endl;
	vector<int> dispenserNumber;
	vector<int> amount;
	for (int i = 0; i < dispensers.size(); i++)
	{
		for (int k = 0; k < cocktail->getIngredients().size(); k++)
		{
			if (dispensers[i]->getIngredient()->getName() == cocktail->getIngredients()[k].getName())
			{
				dispenserNumber.push_back(i);   // vector with active dispenser
				amount.push_back(cocktail->getIngredients()[k].getAmount());   // vector with ingredients amount
			}
		}
	}

	bool while_value = true;
	bool value = false;
	unsigned int counter_time = 0;
	while (while_value) 
	{
		if (value)   // if all amounts <= 0
			while_value = false;
		
		cout << counter_time << " - ";
		for (int i = 0; i < dispensers.size(); i++)
		{
			int counter = 0;
			for (int k = 0; k < dispenserNumber.size(); k++)
			{
				if (dispenserNumber[k] == i && amount.at(k) > 0)   // dispenser is "on"
				{
					cout << "ON";
					break;
				}
				else
					counter++;
				if (counter == dispenserNumber.size())   // dispenser is "off"
					cout << "OFF";
			}
			if (i < dispensers.size() - 1)   // no "," at end of line 
				cout << ", ";
		}
		cout << endl;
		
		int counter = 0;
		for (int i = 0; i < amount.size(); i++)   // reduce amount of ingredient (amount - 1 ml)
		{
			int newamount = amount[i];
			newamount--;
			amount.at(i) = newamount;

			if (amount.at(i) <= 0)
				counter++;
			if (counter == amount.size())   // all amounts <= 0
				value = true;
		}
		usleep(1000000);   // wait 1sec.
		counter_time++;
	}
	cout << "Enjoy your cocktail. " << endl;
}

void CocktailSimulator::makeCocktail(int number)
{
	this->cocktails[number - 1]->print();
}
