#include "Ingredient.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#pragma once
class Cocktail
{
public:
	Cocktail();
	Cocktail(string, vector<Ingredient>);
	~Cocktail();

	void print();  
	//void add_ingredients(Ingredient);

	void setName(string);
	string getName() const;

	void setIngredients(vector<Ingredient> ingredients);
	vector<Ingredient> getIngredients() const;

private:
	string name;
	vector<Ingredient> ingredients;
};

