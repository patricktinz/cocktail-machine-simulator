#include "Ingredient.h"
using namespace std;

#pragma once
class Dispenser
{
	public:
		Dispenser();
		Dispenser(int, Ingredient*);
		~Dispenser();

		void setNumber(int);
		int getNumber() const;

		void setIngredient(Ingredient* ingredient);
		Ingredient* getIngredient() const;
	
	private:
		unsigned int number;
		Ingredient *ingredient = NULL;
};
