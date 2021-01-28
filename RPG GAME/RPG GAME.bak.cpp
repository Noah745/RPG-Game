// RPG GAME.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
work log:
menu - 10 hours

Pseudocode:

struct commonvariables: struct creating all of the variables

void rannum: random number generator

void type_text: type text medium speed

void slow_text: type text slow speed

void fast_text: type text fast speed

bool setcursor: sets the cursor on a coordinate to type in a controlle spot

void wait: waits for an input on the keyboard to go any furthur

void get_stats: asks for input from the user to spend the stat points 

void stat_results: shows the stats you chose

void pick_stats: puts together the stat functions using an if then to creat the stats section

void choose_weapon: choose out of the three weapons 

void choose_ring: choose out of the three rings

void weapon_results: shows the weapon you chose

void weapon_results: shows the ring you chose

void Pick_item: puts the item functions together to create the item section

menu: puts together the item functions and the stat functions to create the start game, then lets you 
exit the game when you choose exit game, finally, it lets you see your highest score you got while playing.




















































*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Variables //

struct commonvariables
{
	int hp, ap, aptotal, hptotal, dur, durtotal;
	int choiceweapon{}, choicering{}, changeitem{};
	int choice, choicestat{};
	int statpoints;
	int choiceitem;
};

// Random Number Generator //

void rannum()
{
	int seed;
	string name, con;
	seed = (int)time(NULL);
	srand(seed);
}

// Text //

void type_text(const std::string& text)
{
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		std::cout << text[i] << std::flush;
		Sleep(20);
	}
}

void Slow_text(const std::string& text)
{
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		std::cout << text[i] << std::flush;
		Sleep(150);
	}
}

void Fast_text(const std::string& text)
{
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		std::cout << text[i] << std::flush;
		Sleep(25);
	}
}

BOOL setcursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void wait()
{
	string temp;
	Fast_text("\n\nPress any key");
	temp = _getch();
}

// Stats //

void get_stats(commonvariables & in) 
{
	string hp_str = "Stat points " + to_string(in.statpoints) + "\n\n";
	system("cls");
	do {
		Fast_text(hp_str);
		Fast_text("Set your HP\n\n");
		cin >> in.hp;
	} while (in.hp > in.statpoints || in.hp <= 0);
	in.statpoints = in.statpoints - in.hp;
	system("cls");
	printf("%i", in.statpoints);
	Fast_text(" stat points remaining\n\n");
	Fast_text("The leftover stat points will go towards your attack power");
	in.ap = in.statpoints;
	wait();
}

void stat_results(commonvariables & in)
{
	system("cls");
	Fast_text("Health: ");
	printf("%i", in.hp);
	Fast_text("\nAttack: ");
	printf("%i", in.ap);
	printf("\n");
	wait();
}

void Pick_stats(commonvariables & in)
{
	in.statpoints = 50;
	get_stats(in);
	stat_results(in);
}

// Items //


int choose_weapon(commonvariables & in) 
{
	system("cls");
	printf("[ 1 Shortsword       ][ 2 Longsword        ][ 3 Greatsword       ]\n");
	printf("[10 DMG 30 Durability][20 DMG 20 Durability][30 DMG 10 Durability]\n\n");
	Fast_text("Which weapon would you like to start with?\n\n");
	cin >> in.choiceweapon;
	system("cls");
	return 0;
}

int choose_ring(commonvariables & in)
{
	printf("[ 1 Life Ring        ][ 2 Knight's Ring    ][ 3 Wood Grain ring  ]\n");
	printf("[      +15 life      ][       +15 DMG      ][   +20 Durability   ]\n\n");
	Fast_text("Which ring would you like to start with?\n\n");
	cin >> in.choicering;
	system("cls");
	return 0;
}

void weapon_results(commonvariables & in)
{
	switch (in.choiceweapon)
	{
	case 1:
		Fast_text("Weapon: Shortsword");
		break;
	case 2:
		Fast_text("Weapon: Longsword");
		break;
	case 3:
		Fast_text("Weapon: Greatsword\n\n");
		break;
	}
}

void ring_results(commonvariables & in)
{
	switch (in.choicering)
	{
	case 1:
		Fast_text("Ring: Life Ring");
		break;
	case 2:
		Fast_text("Ring: Knight's Ring");
		break;
	case 3:
		Fast_text("Ring: Wood Grain Ring");
		break;
	}
	wait();
}

void Pick_items(commonvariables & in) 
{
	system("cls");
	choose_weapon(in);
	choose_ring(in);
	switch (in.choiceweapon) 
		{
			case 1:
				in.aptotal = in.ap + 10;
				in.dur = 30;
				break;
			case 2:
				in.aptotal = in.ap + 20;
				in.dur = 20;
				break;
			case 3:
				in.aptotal = in.ap + 30;
				in.dur = 10;
				break;
		}
	switch (in.choicering)
		{
			case 1:
				in.hptotal = in.hp + 15;
				break;
			case 2:
				in.aptotal = in.aptotal + 15;
				break;
			case 3:
				in.durtotal = in.dur + 20;
				break;
		}
	weapon_results(in);
	ring_results(in);
}

// Menu //

void menu (commonvariables & in)
{
	// Menu Loop //
	do
	{
		// Main Menu //
		{
			system("cls");
			system("Color 0F");
			Fast_text("Main menu\n\n");
			Fast_text("1 Start Game\n");
			Fast_text("2 Highscore\n");
			Fast_text("3 Exit Game\n\n");

			cin >> in.choice;

			system("cls");
		}


		// Highscore //
		if (in.choice == 2)
		{
			Fast_text("Highscore");
			wait();
		}

		// Exit Game //
		else if (in.choice == 3)
		{
			Fast_text("Exit game");
			return;
		}
		
		// Pick Stats Pick Items then start game
		else if (in.choice == 1)
		{
			Pick_stats(in);
			Pick_items(in);
		}
	} while (in.choice == 2);
}

// Combat //

bool combat() {
	return 0;
}

// Gameplay //

bool gameplay(commonvariables & in) 
	{
		Fast_text("\n\nStarted Game!");
		wait();
		Fast_text("\n\nPlaying Game!");
		return 0;
	}

int main()
{
	commonvariables in = commonvariables();
	menu(in);
	gameplay(in);
}

