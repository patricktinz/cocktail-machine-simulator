#include "Cocktail.h"
#include "Ingredient.h"
#include "CocktailSimulator.h"
#include "CocktailMachine.h"
#include <iostream>
using namespace std;

#pragma once
class Menue
{
	public:
		Menue();
		~Menue();
		
		void submenu_mix_it();
		void submenu_configure();
		void submenu_configure_dispenser();
		void submenu_select_ingredient(int);
		int main_menue();
		void check_input(unsigned int &);
		unsigned int search_cocktail();

		void setCocktailSimulator(CocktailMachine* cocktailSimulator);
		CocktailMachine* getCocktailSimulator() const;

	private:
		CocktailMachine *cocktailSimulator = NULL;
};

