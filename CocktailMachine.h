#include "Dispenser.h"
#include "Cocktail.h"
#include "Ingredient.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#pragma once
class CocktailMachine
{
	public:
		CocktailMachine();
		virtual ~CocktailMachine();
		virtual void makeCocktail(Cocktail*)=0;   
		virtual void makeCocktail(int)=0;
		bool check_ingredients(string);

		void add_cocktail();
		void edit_cocktail(unsigned int); 
		void delete_cocktail(unsigned int);
		
		vector<Dispenser*> getDispensers() const;
		vector<Cocktail*> getCocktails() const;
		vector<Ingredient*> getIngredients() const;
		bool check_cocktail(unsigned int);
		void check_input(unsigned int &);
	protected:
		vector<Dispenser*> dispensers;
		vector<Cocktail*> cocktails;
		vector<Ingredient*> all_ingredients;
};


