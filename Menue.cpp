#include "Menue.h"
using namespace std;

Menue::Menue()
{
	while (true)
	{
		unsigned int choice = 0;    // first menu
		cout << "== CocktailMix | Operating Mode ==" << endl;
		cout << "1 - Simulation" << endl;
		cout << "0 - Exit" << endl;
		check_input(choice);

		system("clear");
		if (choice == 0)
			exit(0);
		if (choice == 1) 
		{
			cocktailSimulator = new CocktailSimulator();
			break;
		}
	}
}

Menue::~Menue()
{
	delete cocktailSimulator;
	cocktailSimulator = NULL;
}

void Menue::submenu_mix_it()   // submenu 1
{
	while (true)
	{
		unsigned int choice = 0;
		vector <int> cocktail_number;
		cout << "== CocktailMix | Make Cocktail ==" << endl;
		unsigned int counter = 1;
		for (unsigned int i = 0; i < cocktailSimulator->getCocktails().size(); i++)
		{
			bool check_cocktail = cocktailSimulator->check_cocktail(i);   
			if (check_cocktail) 
			{
				cout << counter++ << " - " << cocktailSimulator->getCocktails()[i]->getName() << endl;
				cocktail_number.push_back(i+1);
			}
		}
		cout << "0 - Back " << endl;

		check_input(choice);

		system("clear");
		if (choice == 0)
			break;
		
		if (choice > 0)
		{
			if(choice < counter)  
			{
				choice = cocktail_number[choice - 1];
				if (choice <= cocktailSimulator->getCocktails().size())
				{
					cocktailSimulator->makeCocktail(choice);
					cocktailSimulator->makeCocktail(cocktailSimulator->getCocktails()[choice - 1]);
				}
			}
			else
			{
				cout << "- No cocktail with this ID! -" << endl;
			}

			cout << "- Enter to continue... -";
			cin.ignore();
			cin.ignore();
		}
		system("clear");
	}
}

void Menue::submenu_configure()   // submenu 2
{
	while (true)   
	{
		unsigned int choice = 0;
		cout << "== CocktailMix | Configure ==" << endl;
		cout << "1 - Configure Dispensers" << endl;
		cout << "2 - List Cocktail" << endl;
		cout << "3 - Add Cocktail" << endl;
		cout << "4 - Edit Cocktail" << endl;
		cout << "5 - Delete Cocktail" << endl;
		cout << "0 - Back" << endl;
		
		check_input(choice);

		system("clear");

		switch (choice)
		{
			case 0:
				return;
			case 1:
				submenu_configure_dispenser();
				break;
			case 2:
				for (unsigned int i = 1; i <= cocktailSimulator->getCocktails().size(); i++)
				{
					cocktailSimulator->makeCocktail(i);
					cout << endl;
				}
				cout << "- Enter to continue... -";
				cin.ignore();
				cin.ignore();
				system("clear");
				break;
			case 3:
				cocktailSimulator->add_cocktail();
				break;
			case 4: 
			{
				unsigned int cocktail_number = search_cocktail();
				if (cocktail_number != -1)
					cocktailSimulator->edit_cocktail(cocktail_number);
				break;
			}
			case 5:
			{
				unsigned int cocktail_number = search_cocktail();
				if (cocktail_number != -1)
					cocktailSimulator->delete_cocktail(cocktail_number);
				break;
			}
			default:
				cout << "- Wrong input -" << endl;
				break;
		}
	}
}

void Menue::submenu_configure_dispenser()   //submenu 2.1
{
	while (true)
	{
		
		unsigned int choice = 0;
		cout << "== CocktailMix | Configure Dispenser ==" << endl;
		for (unsigned int i = 0; i < cocktailSimulator->getDispensers().size(); i++)
		{
			cout << cocktailSimulator->getDispensers()[i]->getNumber() << " - " << cocktailSimulator->getDispensers()[i]->getIngredient()->getName() << endl;
		}
		cout << "0 - Back" << endl;

		check_input(choice);

		system("clear");

		if (choice == 0)
			return;

		if (choice > 0)
		{
			if (choice <= cocktailSimulator->getDispensers().size())
			{
				submenu_select_ingredient(choice);
			}
			else
			{
				cout << "- Wrong input -" << endl;
			}
		}
	}
}

void Menue::submenu_select_ingredient(int nr)   //submenu 2.1.1
{
		unsigned int number = nr - 1;
		unsigned int choice = 0;
		cout << "== CocktailMix | Select Ingredient ==" << endl;
		for (unsigned int i = 2; i <= cocktailSimulator->getIngredients().size(); i++)   // i=2, because first field is "Free"
		{
			cout << i - 1  << " - " << cocktailSimulator->getIngredients()[i - 1]->getName() << endl;
		}
		cout << "0 - Free / Back" << endl;

		check_input(choice);

		system("clear");
		
			if (choice >= 0)
			{
				if (choice < cocktailSimulator->getIngredients().size())
				{
					// write new configuration in vector "dispensers"
					delete cocktailSimulator->getDispensers()[number]->getIngredient();
					cocktailSimulator->getDispensers()[number]->setIngredient(new Ingredient(cocktailSimulator->getIngredients()[choice]->getName()));
				}
				else
				{
					cout << "- No ingredient with this ID! -" << endl;
					cout << "- Enter to continue... -";
					cin.ignore();
					cin.ignore();
					system("clear");
				}
			}
}

int Menue::main_menue()
{
	while(true)   // menu
	{
		unsigned int choice = 0;
		cout << "== CocktailMix | V1.0 ==" << endl;
		cout << "1 - Make Cocktails" << endl;
		cout << "2 - Configure CocktailMix" << endl;
		cout << "0 - Exit" << endl;

		check_input(choice);

		system("clear");

		switch (choice)
		{
			case 0:
				cout << "Shut down..." << endl;
				return 0;
			case 1:
				submenu_mix_it();
				break;
			case 2:
				submenu_configure();
				break;
			default:
				cout << "- Wrong input -" << endl;
				break;
		}
	}
}

void Menue::check_input(unsigned int &choice)
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

unsigned int Menue::search_cocktail()
{
	unsigned int choice = 0;
	cout << "Which cocktail? " << endl;
	for (unsigned int i = 0; i < cocktailSimulator->getCocktails().size(); i++)
	{
		cout << i + 1 << " - " << cocktailSimulator->getCocktails()[i]->getName() << endl;
	}
	cout << "0 - Back" << endl;

	check_input(choice);

	system("clear");
	if (choice == 0)
		return -1;

	if (choice > 0)
	{
		if (choice <= cocktailSimulator->getCocktails().size())
		{
			return choice-1;
		}
		else
		{
			cout << "- No cocktail with this ID! -" << endl;
		}

		cout << "- Enter to continue... -";
		cin.ignore();
		cin.ignore();
	}
}

void Menue::setCocktailSimulator(CocktailMachine *cocktailSimulator)
{
	this->cocktailSimulator = cocktailSimulator;
}

CocktailMachine * Menue::getCocktailSimulator() const
{
	return this->cocktailSimulator;
}
