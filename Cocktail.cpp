#include "Cocktail.h"
using namespace std;

void Cocktail::print()   // output of cocktails
{
	cout << "== Cocktail ==" << endl;
	cout << name << endl;
	
	for (int i = 0; i < ingredients.size(); i++)
	{
		cout << "=> " << ingredients[i].getName();
		cout << " " << ingredients[i].getAmount() << " ml" << endl;
	}
}

void Cocktail::setName(string name) {
	this->name = name;
}

string Cocktail::getName() const {
	return name;
}

void Cocktail::setIngredients(vector<Ingredient> ingredients)
{
	this->ingredients = ingredients;
}

vector<Ingredient> Cocktail::getIngredients() const
{
	return this->ingredients;
}

Cocktail::Cocktail()
{
}

Cocktail::Cocktail(string name, vector<Ingredient> ingredients)
{
	this->name = name;
	this->ingredients = ingredients;
}

Cocktail::~Cocktail()
{
}

/*void Cocktail::add_ingredients(Ingredient name)
{
	ingredients.push_back(name);
}*/
