#include <iostream>
#include <ctime>
#include "monster.h"
using namespace std;

bool captureAttempt(Monster monster)
{
	int chance = 0;
	//Determine the chances to catch the pokemon based on their combat power
	//Less power gives higher chance to catch, more power low chance
	if (monster.combatPower < 100)      { chance = rand() % 2; }
	else if (monster.combatPower > 99)  { chance = rand() % 4; }
	else if (monster.combatPower > 200) { chance = rand() % 8; }
	if (chance == 0)
		return true;
	else
		return false;
}

string randomNameGenerator()
{
	//Create a string array of all the names 
	string names[] = { "Charmander", "Bulbasor", "Squrtile", "Pidgey", "Pikachu",
		"Sandshrew", "Zubat", "Mankey", "Abra", "Magikarp",
		"Eevee", "Rattata", "Vulpix", "Scyther", "Jigglypuff",
		"Geodude", "Onix", "Staryu", "Snorlax", "Mewtwo",
		"Oddish", "Caterpie", "Spearow", "Charizard", "Zapdos" };
	return names[rand() % 24]; //return a random name from the array
}

Monster setMonster(Monster monster)
{
	//Pick a random monster rame and assign a random power to them
	monster.name = randomNameGenerator();
	monster.combatPower = rand() % 450 + 1;
	return monster;
}

int main()
{
	srand(time(NULL));
	Monster monster;
	int pokeBalls = 5;
	bool didCatch = false;
	char inp;

	while (pokeBalls >= 1 && didCatch == false)
	{
		monster = setMonster(monster);
		didCatch = captureAttempt(monster);
		cout << "A wild " << monster.name << " appeared!" << endl;
		cout << monster.name <<": " << monster.combatPower << endl;
		cout << "You have " << pokeBalls << " pokeballs left" << endl;
		cout << "Attempt to capture? <Y/N>" << " ";
		cin >> inp;
		//Set conditions to capture pokemon, if user puts 'y' then one pokeball is taken away each time
		if ((inp == 'y' || inp == 'Y'))
		{
			pokeBalls--;
			if (didCatch == true)
			{
				cout << "Gotcha! You caught " << monster.name << endl;
				didCatch = false;
			}
			else
			{
				while ((inp == 'y' || inp == 'Y') && didCatch == false && pokeBalls >= 1)
				{
					cout << monster.name << " broke free! Attempt to catch again? <Y/N>" << endl;
					cout << "You have " << pokeBalls << " pokeballs left" << endl;
					cin >> inp;
					pokeBalls--;
					didCatch = captureAttempt(monster);
				}
				if (didCatch == true)
				{
					cout << "Gotcha! You caught " << monster.name << endl;
					didCatch = false;
				}
				else if (inp == 'n' || inp == 'N')
				{
					cout << "You got awaya safely!" << "\n" << endl;
				}
			}
		}
		else
		{
			cout << "You got away safely" << "\n" << endl;
		}

	}
	//Not enough pokeballs so terminate the program
	if (pokeBalls == 0)
	{
		cout << "You do not have anymore pokeballs so you ran and got away safely," << endl;
	}
	return 0;
}
