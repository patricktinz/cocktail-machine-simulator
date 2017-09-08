#include "Ingredient.h"
using namespace std;

void Ingredient::setName(string name) {
	this->name = name;
}

string Ingredient::getName() const {
	return this->name;
}

void Ingredient::setAmount(unsigned int amount)
{
	this->amount = amount;
}

unsigned int Ingredient::getAmount() const
{
	return this->amount;
}

Ingredient::Ingredient()
{
}

Ingredient::Ingredient(string name)
{
	this->name = name;
}

Ingredient::Ingredient(string name, unsigned int amount)
{
	this->name = name;
	this->amount = amount;
}

Ingredient::~Ingredient()
{
}
