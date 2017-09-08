#include "CocktailMachine.h"
#include <fstream>

bool CocktailMachine::check_ingredients(string name)
{
	for (unsigned int i = 1; i <= all_ingredients.size(); i++)
	{
		if (name == all_ingredients[i - 1]->getName())
			return false;
	}
	return true;
}

void CocktailMachine::check_input(unsigned int &choice)
{
	cout << "Entry > ";
	cin >> choice;
	while (!cin)   // if choice is no number
	{
		try
		{
			throw "- Wrong input! Enter a number -";
		}

		catch (const char* str)
		{
			cout << str << endl;
		}
		cin.clear();
		cin.ignore();

		cout << "Entry > ";
		cin >> choice;
	}
}

void CocktailMachine::add_cocktail()
{
	vector<Ingredient> ingredients;
	string cocktailName = "";
	string ingredientName = "";
	unsigned int amount = 0;
	bool check = true;
	unsigned int choice = 1;

	cout << "== CocktailMix | Add Cocktail ==" << endl;
	string tmp = "";
	cout << "Cocktail: ";
	cin.ignore();
	getline(cin, tmp);
	if (tmp != "")
		cocktailName = tmp;
	while (check)
	{
		cout << "0 - Back" << endl;
		cout << "1 - Add ingredient" << endl;
		check_input(choice);
		if (choice == 0)
			check = false;
		if (choice == 1)
		{
			cout << "Ingredient: ";
			cin.ignore();
			getline(cin, tmp);
			if (tmp != "")
				ingredientName = tmp;
			cout << "Amount: ";
			getline(cin, tmp);
			if (tmp != "")
				amount = atoi(tmp.c_str());
			ingredients.push_back(Ingredient(ingredientName, amount));
			if (check_ingredients(ingredientName))   // check of duplicate (ingredientName)
				all_ingredients.push_back(new Ingredient(ingredientName));   // import all ingredients once
		}
		if (choice >= 2)
			cout << "- Wrong input -" << endl;
	}
	cocktails.push_back(new Cocktail(cocktailName, ingredients));
	system("clear");
}

void CocktailMachine::edit_cocktail(unsigned int cocktail_number)
{
	vector<Ingredient> ingredients;
	string cocktailName = "";
	string ingredientName = "";
	unsigned int amount = 0;
	bool check = true;
	unsigned int choice = 1;

	cout << "== CocktailMix | Edit Cocktail ==" << endl;
	string tmp = "";
	cout << "Cocktail Name: ";
	cin.ignore();
	getline(cin, tmp);
	if (tmp != "")
	{
		cocktailName = tmp;
		cocktails[cocktail_number]->setName(cocktailName);
	}
	while (check)
	{
		cout << "0 - Back" << endl;
		cout << "1 - Add ingredient" << endl;
		check_input(choice);
		if (choice == 0)
			check = false;
		if (choice == 1)
		{
			cout << "Ingredient: ";
			cin.ignore();
			getline(cin, tmp);
			if (tmp != "")
				ingredientName = tmp;
			cout << "Amount: ";
			getline(cin, tmp);
			if (tmp != "")
				amount = atoi(tmp.c_str());
			ingredients.push_back(Ingredient(ingredientName, amount));
			cocktails[cocktail_number]->setIngredients(ingredients);
			if (check_ingredients(ingredientName))   // check of duplicate (ingredientName)
				all_ingredients.push_back(new Ingredient(ingredientName));   // import all ingredients once
		}
		if (choice >= 2)
			cout << "- Wrong input -" << endl;
	}
	system("clear");
}

void CocktailMachine::delete_cocktail(unsigned int cocktail_number)
{
	for (int i = cocktail_number; i < cocktails.size() - 1; i++) 
	{
		cocktails[i] = cocktails[i + 1];
	}
	cocktails.pop_back();
}

vector<Dispenser*> CocktailMachine::getDispensers() const
{
	return this->dispensers;
}

vector<Cocktail*> CocktailMachine::getCocktails() const
{
	return this->cocktails;
}

vector<Ingredient*> CocktailMachine::getIngredients() const
{
	return this->all_ingredients;
}

bool CocktailMachine::check_cocktail(unsigned int cocktail_number)
{
	unsigned int counter_ingredients = 0;
	for (int i = 0; i < cocktails[cocktail_number]->getIngredients().size(); i++)   // count ingredients in cocktail
		counter_ingredients++;

	unsigned int counter = 0;
	for (int i = 0; i < dispensers.size(); i++)   
	{
		for (int k = 0; k < cocktails[cocktail_number]->getIngredients().size(); k++)
		{
			if (dispensers[i]->getIngredient()->getName() == cocktails[cocktail_number]->getIngredients()[k].getName())   // compare dispenser ingredients with cocktail ingredients
				counter++;
			if (counter_ingredients == counter)   // dispenser has all ingredients
				return true;
		}
	}
	return false;
}

CocktailMachine::CocktailMachine()
{
	all_ingredients.push_back(new Ingredient("Free"));   // first field of all_ingredients is "Free"      
	ifstream ingredientsRead;
	ingredientsRead.open("cocktails.txt", ios::in);

	if (ingredientsRead)
	{
		string cocktailName = "";
		while (getline(ingredientsRead, cocktailName, ':'))   // import cocktail name
		{
			string ingredientName = "";
			string ingredientAmount = "";
			vector<Ingredient> ingredients;
			while (getline(ingredientsRead, ingredientName, ';'))   // import ingredient name
			{
				getline(ingredientsRead, ingredientAmount, ';');    // import ingredient amount
				unsigned int amount = stoi(ingredientAmount);
				ingredients.push_back(Ingredient(ingredientName, amount));
				if (check_ingredients(ingredientName))   // check of duplicate (ingredientName)
					all_ingredients.push_back(new Ingredient(ingredientName));   // import all ingredients once

				if (ingredientsRead.peek() == '\n')
				{
					ingredientsRead.get();   // Next line in data
					break;
				}
			}
			cocktails.push_back(new Cocktail(cocktailName, ingredients));
		}
		ingredientsRead.close();
	}
	else
	{
		cout << "Reading (cocktails.txt) is not possible!" << endl;
		cout << endl;
	}

	ifstream dispensersRead;
	dispensersRead.open("dispenser.txt", ios::in);

	if (dispensersRead)
	{
		string number;
		while (getline(dispensersRead, number, ':'))   // import number of dispenser
		{
			unsigned int nr = stoi(number);
			string name;
			getline(dispensersRead, name, '\n');   // import dispenser ingredient

			if (name.size() > 0)
				dispensers.push_back(new Dispenser(nr, new Ingredient(name)));
			else
				dispensers.push_back(new Dispenser(nr, new Ingredient("Free")));
		}
	}
	else
	{
		cout << "Reading (dispenser.txt) is not possible!" << endl;
		cout << endl;
	}
	dispensersRead.close();
}

CocktailMachine::~CocktailMachine()
{
	ofstream ingredientsWrite;
	ingredientsWrite.open("cocktails.txt", ios::out);

	for (unsigned int i = 0; i < cocktails.size(); i++)
	{
		// export cocktail name
		ingredientsWrite << cocktails[i]->getName() << ":";   // inserts character (:) into the stream

		for (unsigned int k = 0; k < cocktails[i]->getIngredients().size(); k++)
		{
			// export ingredients name
			ingredientsWrite << cocktails[i]->getIngredients()[k].getName() << ";"; // inserts character (;) into the stream
			ingredientsWrite << cocktails[i]->getIngredients()[k].getAmount() << ";";   //Req01
		}
		ingredientsWrite.put('\n');   // inserts character (interlace) into the stream
	}
	ingredientsWrite.close();

	ofstream dispensersWrite;
	dispensersWrite.open("dispenser.txt", ios::out);
	for (unsigned int i = 0; i < dispensers.size(); i++)
	{
		dispensersWrite << dispensers[i]->getNumber() << ":";   // export dispenser number
		dispensersWrite << dispensers[i]->getIngredient()->getName() << "\n";   // export dispenser ingredient
	}
	dispensersWrite.close();

	// delete pointer (cocktails, dispensers and all_ingredients) 
	for (unsigned int i = 0; i < dispensers.size(); i++)
		delete dispensers[i];

	for (unsigned int i = 0; i < cocktails.size(); i++)
		delete cocktails[i];

	for (unsigned int i = 0; i < all_ingredients.size(); i++)
		delete all_ingredients[i];
}
