// RPG GAME.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
work log:
menu - 10 hours

Work log:
combat system, 
maze movement,
11 hours

Pseudocode:

struct commonvariables: struct creating all of the variables.

rannum: random number generator.

type_text: type text medium speed.

slow_text: type text slow speed.

fast_text: type text fast speed.

setcursor: sets the cursor on a coordinate to type gcommon a controlle spot.

wait: waits for an input on the keyboard to go any furthur.

get_stats: asks for input from the user to spend the stat points.

stat_results: shows the stats you chose.

pick_stats: puts together the stat functions using an if then to creat the stats section.

choose_weapon: choose out of the three weapons.

choose_ring: choose out of the three rings.

weapon_results: shows the weapon you chose.

weapon_results: shows the ring you chose.

Pick_item: puts the item functions together to create the item section.

menu: puts together the item functions and the stat functions to create the start game, then lets you 
exit the game when you choose exit game, finally, it lets you see your highest score you got while playing.

beginning dialogue: prints all of the dialogue you see when you start the game.

perm stat clear: sets the stats of your character at the top left of the screen using setcursor.

monsterstat sets the monsters health at the top left of the screen under the character stats.

monsterascii: has all of the monster asciis that will be used throughout the game.

struct aroom: holds all of the ints used for innit rooms, like xrow and xcol which are the coordinates of where the x go cooresponding to each room.
visited keeps track of wheather you have visited a room or not. Up down left right decides which room cooresponds the the direction from the room you are in.
eap and ehp control the enemys hp and ap in each room.

innit rooms: thats where i put the information for each room like where your x should be on the map, how powerfull the enemys are etc. (basically just uses - 
sets the values of each of the integers that are in struct aroom).

maze_str: tells print_maze what to print.

print_maze: prints the maze_str down the rows x < 28 times and across the collumns x < 65 times. 
While it prints it looks for the coordinates of the x that you entered using int row and int col.

combat: combat uses a timer running in the backround using a thread. if you dont put your imput weather its attack or block before the timer runs out, 
then you take damage as penalty for missing the timing.

*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>

using namespace std;

// Variables //

struct commonvariables
{
	int response_seconds = 1;
	int hp = 0, ap = 0, aptotal = 0, hptotal = 0, dur = 0, durtotal = 0;
	int choiceweapon = 0, choicering = 0, changeitem = 0;
	int choice = 0, choicestat = 0;
	int statpoints = 0;
	int choiceitem = 0;
	int enemyap = 0, enemyhp = 0;
	int myrow{}, mycol{};
	int room = 1;
	bool block = false;
	bool attack = false;
	string Weapon, Ring;
};
commonvariables gcommon;
string gname;

// Random Number Generator //

int randnum(int max_num)
{
	int  num = rand() % max_num;
	return num;
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
	temp = _getch();
}

// Dialogue //

void Beginning_dialogue()
{
	Fast_text("You seem to have woken up in some strange dungeon, you can't remember anything, not even your name.\nOne thing you do know is you are not supposed to be here and must get out.");
	wait();
	Fast_text("\n\nWhat will you call yourself?\n\n");
	cin >> gname;
	Fast_text("\nYou decide to call yourself ");
	cout << gname;
	Fast_text(", and now you set off to try and escape this dungeon.");
	wait();
	system("cls");
}

// Permanent Stats //

void perm_stats()
{
	setcursor(1, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("Attack: %i", gcommon.aptotal);
	setcursor(1, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("Health: %i", gcommon.hptotal);
	setcursor(1, 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("Durability: %i", gcommon.durtotal);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	setcursor(1, 3);
	cout << "Weapon: " << gcommon.Weapon << "";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	setcursor(1, 4);
	cout << "Ring: " << gcommon.Ring << "";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void monsterstat()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	setcursor(1, 5);
	printf("Enemy HP: %i", gcommon.enemyhp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// Stats //

void get_stats()
{
	string hp_str = "Stat points " + to_string(gcommon.statpoints) + "\n\n";
	system("cls");
	do {
		Fast_text(hp_str);
		Fast_text("Set your HP\n\n");
		cin >> gcommon.hp;
	} while (gcommon.hp > gcommon.statpoints || gcommon.hp <= 0);
	gcommon.statpoints = gcommon.statpoints - gcommon.hp;
	system("cls");
	printf("%i", gcommon.statpoints);
	Fast_text(" stat points remaining\n\n");
	Fast_text("The leftover stat points will go towards your attack power");
	gcommon.ap = gcommon.statpoints;
	wait();
	system("cls");
}

void Pick_stats()
{
	gcommon.statpoints = 50;
	get_stats();
	setcursor(1, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("Attack: %i", gcommon.ap);
	setcursor(1, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("Health: %i", gcommon.hp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	wait();
}

// Items //

void choose_weapon() 
{
	system("cls");
	printf("[ 1 Shortsword       ][ 2 Longsword        ][ 3 Greatsword       ]\n");
	printf("[10 DMG 30 Durability][20 DMG 20 Durability][30 DMG 10 Durability]\n\n");
	Fast_text("Which weapon would you like to start with?\n\n");
	cin >> gcommon.choiceweapon;
	system("cls");
}

int choose_ring()
{
	printf("[ 1 Life Ring        ][ 2 Knight's Ring    ][ 3 Wood Grain ring  ]\n");
	printf("[      +15 life      ][       +15 DMG      ][   +20 Durability   ]\n\n");
	Fast_text("Which ring would you like to start with?\n\n");
	cin >> gcommon.choicering;
	system("cls");
	return 0;
}

void Pick_items() 
{
	system("cls");
	choose_weapon();
	choose_ring();
	gcommon.aptotal = gcommon.ap;
	gcommon.hptotal = gcommon.hp;
	switch (gcommon.choiceweapon) 
		{
			case 1:
				gcommon.aptotal = gcommon.ap + 10;
				gcommon.durtotal = 30;
				gcommon.Weapon = "Shortsword";
				break;
			case 2:
				gcommon.aptotal = gcommon.ap + 20;
				gcommon.durtotal = 20;
				gcommon.Weapon = "Longsword";
				break;
			case 3:
				gcommon.aptotal = gcommon.ap + 30;
				gcommon.durtotal = 10;
				gcommon.Weapon = "Greatsword";
				break;
		}
	switch (gcommon.choicering)
		{
			case 1:
				gcommon.hptotal = gcommon.hp + 15;
				gcommon.Ring = "Life Ring";
				break;
			case 2:
				gcommon.aptotal = gcommon.aptotal + 15;
				gcommon.Ring = "Knight's Ring";
				break;
			case 3:
				gcommon.durtotal = gcommon.durtotal + 20;
				gcommon.Ring = "Wood Grain Ring";
				break;
		}
	system("cls");
	perm_stats();
	wait();
}

// Menu //

void menu ()
{
	// Menu Loop //
	do
	{
		// Main Menu //
		{
			system("cls");
			system("Color 0F");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			Fast_text("Main menu\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			Fast_text("1 Start Game\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			Fast_text("2 Highscore\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			Fast_text("3 Exit Game\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			cin >> gcommon.choice;

			system("cls");
		}


		// Highscore //
		if (gcommon.choice == 2)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			Fast_text("Highscore");
			wait();
		}

		// Exit Game //
		else if (gcommon.choice == 3)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			Fast_text("Exit game");
			exit(0);
		}
		
		// Pick Stats Pick Items then start game
		else if (gcommon.choice == 1)
		{
			Pick_stats();
			Pick_items();
		}
	} while (gcommon.choice == 2);
}

// Rooms //

struct ARoom 
{
	int xRow{}, xCol{};
	bool visited = false;
	string monster;
	int monsterascii{};
	int eap{}, ehp{};
	int up{}, down{}, left{}, right{};
};
ARoom rooms[48];

void init_rooms()
{
	rooms[1].xRow = 2;
	rooms[1].xCol = 3;
	rooms[1].monster = "Boss";
	rooms[1].monsterascii = 1;
	rooms[1].eap = 10;
	rooms[1].ehp = 1000;
	rooms[1].up = 0;
	rooms[1].down = 5;
	rooms[1].left = 0;
	rooms[1].right = 0;

	rooms[2].xRow = 2;
	rooms[2].xCol = 38;
	rooms[2].monster = "Boss";
	rooms[2].monsterascii = 1;
	rooms[2].eap = 10;
	rooms[2].ehp = 1000;
	rooms[2].up = 0;
	rooms[2].down = 8;
	rooms[2].left = 0;
	rooms[2].right = 0;

	rooms[3].xRow = 2;
	rooms[3].xCol = 52;
	rooms[3].monster = "Zombie";
	rooms[3].monsterascii = 1;
	rooms[3].eap = 5;
	rooms[3].ehp = 200;
	rooms[3].up = 0;
	rooms[3].down = 9;
	rooms[3].left = 0;
	rooms[3].right = 4;

	rooms[4].xRow = 2;
	rooms[4].xCol = 59;
	rooms[4].monster = "Boss";
	rooms[4].monsterascii = 1;
	rooms[4].eap = 10;
	rooms[4].ehp = 1000;
	rooms[4].up = 0;
	rooms[4].down = 0;
	rooms[4].left = 3;
	rooms[4].right = 0;

	rooms[5].xRow = 5;
	rooms[5].xCol = 3;
	rooms[5].monster = "Zombie";
	rooms[5].monsterascii = 1;
	rooms[5].eap = 5;
	rooms[5].ehp = 200;
	rooms[5].up = 1;
	rooms[5].down = 10;
	rooms[5].left = 0;
	rooms[5].right = 0;

	rooms[6].xRow = 5;
	rooms[6].xCol = 17;
	rooms[6].monster = "Skeleton";
	rooms[6].monsterascii = 2;
	rooms[6].eap = 5;
	rooms[6].ehp = 200;
	rooms[6].up = 0;
	rooms[6].down = 12;
	rooms[6].left = 0;
	rooms[6].right = 0;

	rooms[7].xRow = 5;
	rooms[7].xCol = 31;
	rooms[7].monster = "Zombie";
	rooms[7].monsterascii = 1;
	rooms[7].eap = 5;
	rooms[7].ehp = 200;
	rooms[7].up = 0;
	rooms[7].down = 13;
	rooms[7].left = 0;
	rooms[7].right = 8;

	rooms[8].xRow = 5;
	rooms[8].xCol = 38;
	rooms[8].monster = "Skeleton";
	rooms[8].monsterascii = 2;
	rooms[8].eap = 5;
	rooms[8].ehp = 200;
	rooms[8].up = 2;
	rooms[8].down = 0;
	rooms[8].left = 7;
	rooms[8].right = 0;

	rooms[9].xRow = 5;
	rooms[9].xCol = 52;
	rooms[9].monster = "Zombie";
	rooms[9].monsterascii = 1;
	rooms[9].eap = 5;
	rooms[9].ehp = 200;
	rooms[9].up = 3;
	rooms[9].down = 15;
	rooms[9].left = 0;
	rooms[9].right = 0;
	
	rooms[10].xRow = 8;
	rooms[10].xCol = 3;
	rooms[10].monster = "Skeleton";
	rooms[10].monsterascii = 2;
	rooms[10].eap = 5;
	rooms[10].ehp = 200;
	rooms[10].up = 5;
	rooms[10].down = 0;
	rooms[10].left = 0;
	rooms[10].right = 11;

	rooms[11].xRow = 8;
	rooms[11].xCol = 10;
	rooms[11].monster = "Zombie";
	rooms[11].monsterascii = 1;
	rooms[11].eap = 5;
	rooms[11].ehp = 200;
	rooms[11].up = 0;
	rooms[11].down = 0;
	rooms[11].left = 10;
	rooms[11].right = 12;

	rooms[12].xRow = 8;
	rooms[12].xCol = 17;
	rooms[12].monster = "Skeleton";
	rooms[12].monsterascii = 2;
	rooms[12].eap = 5;
	rooms[12].ehp = 200;
	rooms[12].up = 6;
	rooms[12].down = 17;
	rooms[12].left = 11;
	rooms[12].right = 0;

	rooms[13].xRow = 8;
	rooms[13].xCol = 31;
	rooms[13].monster = "Zombie";
	rooms[13].monsterascii = 1;
	rooms[13].eap = 5;
	rooms[13].ehp = 200;
	rooms[13].up = 7;
	rooms[13].down = 18;
	rooms[13].left = 0;
	rooms[13].right = 0;

	rooms[14].xRow = 8;
	rooms[14].xCol = 45;
	rooms[14].monster = "Skeleton";
	rooms[14].monsterascii = 2;
	rooms[14].eap = 5;
	rooms[14].ehp = 200;
	rooms[14].up = 0;
	rooms[14].down = 19;
	rooms[14].left = 0;
	rooms[14].right = 15;

	rooms[15].xRow = 8;
	rooms[15].xCol = 52;
	rooms[15].monster = "Zombie";
	rooms[15].monsterascii = 1;
	rooms[15].eap = 5;
	rooms[15].ehp = 200;
	rooms[15].up = 9;
	rooms[15].down = 0;
	rooms[15].left = 14;
	rooms[15].right = 16;

	rooms[16].xRow = 8;
	rooms[16].xCol = 59;
	rooms[16].monster = "Boss";
	rooms[16].monsterascii = 1;
	rooms[16].eap = 10;
	rooms[16].ehp = 1000;
	rooms[16].up = 0;
	rooms[16].down = 0;
	rooms[16].left = 15;
	rooms[16].right = 0;

	rooms[17].xRow = 11;
	rooms[17].xCol = 17;
	rooms[17].monster = "Skeleton";
	rooms[17].monsterascii = 2;
	rooms[17].eap = 5;
	rooms[17].ehp = 200;
	rooms[17].up = 12;
	rooms[17].down = 22;
	rooms[17].left = 0;
	rooms[17].right = 0;
	
	rooms[18].xRow = 11;
	rooms[18].xCol = 31;
	rooms[18].monster = "Zombie";
	rooms[18].monsterascii = 1;
	rooms[18].eap = 5;
	rooms[18].ehp = 200;
	rooms[18].up = 13;
	rooms[18].down = 24;
	rooms[18].left = 0;
	rooms[18].right = 0;

	rooms[19].xRow = 11;
	rooms[19].xCol = 45;
	rooms[19].monster = "Skeleton";
	rooms[19].monsterascii = 2;
	rooms[19].eap = 5;
	rooms[19].ehp = 200;
	rooms[19].up = 14;
	rooms[19].down = 26;
	rooms[19].left = 0;
	rooms[19].right = 0;

	rooms[20].xRow = 14;
	rooms[20].xCol = 3;
	rooms[20].monster = "Boss";
	rooms[20].monsterascii = 1;
	rooms[20].eap = 10;
	rooms[20].ehp = 1000;
	rooms[20].up = 0;
	rooms[20].down = 0;
	rooms[20].left = 0;
	rooms[20].right = 21;

	rooms[21].xRow = 14;
	rooms[21].xCol = 10;
	rooms[21].monster = "Zombie";
	rooms[21].monsterascii = 1;
	rooms[21].eap = 5;
	rooms[21].ehp = 200;
	rooms[21].up = 0;
	rooms[21].down = 0;
	rooms[21].left = 20;
	rooms[21].right = 22;

	rooms[22].xRow = 14;
	rooms[22].xCol = 17;
	rooms[22].monster = "Skeleton";
	rooms[22].monsterascii = 2;
	rooms[22].eap = 5;
	rooms[22].ehp = 200;
	rooms[22].up = 17;
	rooms[22].down = 29;
	rooms[22].left = 21;
	rooms[22].right = 23;

	rooms[23].xRow = 14;
	rooms[23].xCol = 24;
	rooms[23].monster = "Zombie";
	rooms[23].monsterascii = 1;
	rooms[23].eap = 5;
	rooms[23].ehp = 200;
	rooms[23].up = 0;
	rooms[23].down = 0;
	rooms[23].left = 22;
	rooms[23].right = 24;

	// starting room //
	
	rooms[24].xRow = 14;
	rooms[24].xCol = 31;
	rooms[24].monster = "Skeleton";
	rooms[24].monsterascii = 2;
	rooms[24].eap = 5;
	rooms[24].ehp = 100;
	rooms[24].up = 18;
	rooms[24].down = 30;
	rooms[24].left = 23;
	rooms[24].right = 25;

	// starting room //

	rooms[25].xRow = 14;
	rooms[25].xCol = 38;
	rooms[25].monster = "Zombie";
	rooms[25].monsterascii = 1;
	rooms[25].eap = 5;
	rooms[25].ehp = 200;
	rooms[25].up = 0;
	rooms[25].down = 0;
	rooms[25].left = 24;
	rooms[25].right = 26;

	rooms[26].xRow = 14;
	rooms[26].xCol = 45;
	rooms[26].monster = "Skeleton";
	rooms[26].monsterascii = 2;
	rooms[26].eap = 5;
	rooms[26].ehp = 200;
	rooms[26].up = 19;
	rooms[26].down = 0;
	rooms[26].left = 25;
	rooms[26].right = 27;

	rooms[27].xRow = 14;
	rooms[27].xCol = 52;
	rooms[27].monster = "Zombie";
	rooms[27].monsterascii = 1;
	rooms[27].eap = 5;
	rooms[27].ehp = 200;
	rooms[27].up = 0;
	rooms[27].down = 31;
	rooms[27].left = 26;
	rooms[27].right = 28;

	rooms[28].xRow = 14;
	rooms[28].xCol = 59;
	rooms[28].monster = "Boss";
	rooms[28].monsterascii = 1;
	rooms[28].eap = 10;
	rooms[28].ehp = 1000;
	rooms[28].up = 0;
	rooms[28].down = 0;
	rooms[28].left = 27;
	rooms[28].right = 0;

	rooms[29].xRow = 17;
	rooms[29].xCol = 17;
	rooms[29].monster = "Skeleton";
	rooms[29].monsterascii = 2;
	rooms[29].eap = 5;
	rooms[29].ehp = 200;
	rooms[29].up = 22;
	rooms[29].down = 0;
	rooms[29].left = 0;
	rooms[29].right = 0;

	rooms[30].xRow = 17;
	rooms[30].xCol = 31;
	rooms[30].monster = "Zombie";
	rooms[30].monsterascii = 1;
	rooms[30].eap = 5;
	rooms[30].ehp = 200;
	rooms[30].up = 24;
	rooms[30].down = 33;
	rooms[30].left = 0;
	rooms[30].right = 0;

	rooms[31].xRow = 17;
	rooms[31].xCol = 52;
	rooms[31].monster = "Skeleton";
	rooms[31].monsterascii = 2;
	rooms[31].eap = 5;
	rooms[31].ehp = 200;
	rooms[31].up = 27;
	rooms[31].down = 0;
	rooms[31].left = 0;
	rooms[31].right = 0;
		  
	rooms[32].xRow = 20;
	rooms[32].xCol = 3;
	rooms[32].monster = "Boss";
	rooms[32].monsterascii = 1;
	rooms[32].eap = 10;
	rooms[32].ehp = 1000;
	rooms[32].up = 0;
	rooms[32].down = 36;
	rooms[32].left = 0;
	rooms[32].right = 0;
		  
	rooms[33].xRow = 20;
	rooms[33].xCol = 31;
	rooms[33].monster = "Zombie";
	rooms[33].monsterascii = 1;
	rooms[33].eap = 5;
	rooms[33].ehp = 200;
	rooms[33].up = 30;
	rooms[33].down = 40;
	rooms[33].left = 0;
	rooms[33].right = 34;
		  
	rooms[34].xRow = 20;
	rooms[34].xCol = 38;
	rooms[34].monster = "Skeleton";
	rooms[34].monsterascii = 2;
	rooms[34].eap = 5;
	rooms[34].ehp = 200;
	rooms[34].up = 0;
	rooms[34].down = 0;
	rooms[34].left = 33;
	rooms[34].right = 35;
		  
	rooms[35].xRow = 20;
	rooms[35].xCol = 45;
	rooms[35].monster = "Zombie";
	rooms[35].monsterascii = 1;
	rooms[35].eap = 5;
	rooms[35].ehp = 200;
	rooms[35].up = 0;
	rooms[35].down = 41;
	rooms[35].left = 34;
	rooms[35].right = 0;
		  
	rooms[36].xRow = 23;
	rooms[36].xCol = 3;
	rooms[36].monster = "Skeleton";
	rooms[36].monsterascii = 2;
	rooms[36].eap = 5;
	rooms[36].ehp = 200;
	rooms[36].up = 32;
	rooms[36].down = 44;
	rooms[36].left = 0;
	rooms[36].right = 37;
		  
	rooms[37].xRow = 23;
	rooms[37].xCol = 10;
	rooms[37].monster = "Zombie";
	rooms[37].monsterascii = 1;
	rooms[37].eap = 5;
	rooms[37].ehp = 200;
	rooms[37].up = 0;
	rooms[37].down = 0;
	rooms[37].left = 36;
	rooms[37].right = 38;
		  
	rooms[38].xRow = 23;
	rooms[38].xCol = 17;
	rooms[38].monster = "Skeleton";
	rooms[38].monsterascii = 2;
	rooms[38].eap = 5;
	rooms[38].ehp = 200;
	rooms[38].up = 0;
	rooms[38].down = 0;
	rooms[38].left = 37;
	rooms[38].right = 39;
		  
	rooms[39].xRow = 23;
	rooms[39].xCol = 24;
	rooms[39].monster = "Zombie";
	rooms[39].monsterascii = 1;
	rooms[39].eap = 5;
	rooms[39].ehp = 200;
	rooms[39].up = 0;
	rooms[39].down = 45;
	rooms[39].left = 38;
	rooms[39].right = 40;

	rooms[40].xRow = 23;
	rooms[40].xCol = 31;
	rooms[40].monster = "Skeleton";
	rooms[40].monsterascii = 2;
	rooms[40].eap = 5;
	rooms[40].ehp = 200;
	rooms[40].up = 33;
	rooms[40].down = 0;
	rooms[40].left = 39;
	rooms[40].right = 0;

	rooms[41].xRow = 23;
	rooms[41].xCol = 45;
	rooms[41].monster = "Zombie";
	rooms[41].monsterascii = 1;
	rooms[41].eap = 5;
	rooms[41].ehp = 200;
	rooms[41].up = 35;
	rooms[41].down = 46;
	rooms[41].left = 0;
	rooms[41].right = 42;

	rooms[42].xRow = 23;
	rooms[42].xCol = 52;
	rooms[42].monster = "Skeleton";
	rooms[42].monsterascii = 2;
	rooms[42].eap = 5;
	rooms[42].ehp = 200;
	rooms[42].up = 0;
	rooms[42].down = 0;
	rooms[42].left = 41;
	rooms[42].right = 43;

	rooms[43].xRow = 23;
	rooms[43].xCol = 59;
	rooms[43].monster = "Zombie";
	rooms[43].monsterascii = 1;
	rooms[43].eap = 5;
	rooms[43].ehp = 200;
	rooms[43].up = 0;
	rooms[43].down = 47;
	rooms[43].left = 42;
	rooms[43].right = 0;

	rooms[44].xRow = 26;
	rooms[44].xCol = 3;
	rooms[44].monster = "Boss";
	rooms[44].monsterascii = 1;
	rooms[44].eap = 10;
	rooms[44].ehp = 1000;
	rooms[44].up = 36;
	rooms[44].down = 0;
	rooms[44].left = 0;
	rooms[44].right = 0;

	rooms[45].xRow = 26;
	rooms[45].xCol = 24;
	rooms[45].monster = "Boss";
	rooms[45].monsterascii = 1;
	rooms[45].eap = 10;
	rooms[45].ehp = 1000;
	rooms[45].up = 39;
	rooms[45].down = 0;
	rooms[45].left = 0;
	rooms[45].right = 0;

	rooms[46].xRow = 26;
	rooms[46].xCol = 45;
	rooms[46].monster = "Boss";
	rooms[46].monsterascii = 1;
	rooms[46].eap = 10;
	rooms[46].ehp = 1000;
	rooms[46].up = 41;
	rooms[46].down = 0;
	rooms[46].left = 0;
	rooms[46].right = 0;

	rooms[47].xRow = 26;
	rooms[47].xCol = 59;
	rooms[47].monster = "Boss";
	rooms[47].monsterascii = 1;
	rooms[47].eap = 10;
	rooms[47].ehp = 1000;
	rooms[47].up = 43;
	rooms[47].down = 0;
	rooms[47].left = 0;
	rooms[47].right = 0;
}


// Maze //

string maze_str[28] =
{
//             111111111122222222223333333333444444444455555555556666
//   0123456789012345678901234567890123456789012345678901234567890123 
	" ______                             ______        ______ ______ \n", //  0
	"|      |                           |      |      |      |      |\n", //  1
	"|      |                           |      |      |      |      |\n", //  2
	"|______|       ______        ______|______|      |______|______|\n", //  3
	"|      |      |      |      |      |      |      |      |       \n", //  4
	"|      |      |      |      |      |      |      |      |       \n", //  5
	"|______|______|______|      |______|______|______|______|______ \n", //  6
	"|      |      |      |      |      |      |      |      |      |\n", //  7
	"|      |      |      |      |      |      |      |      |      |\n", //  8
	"|______|______|______|      |______|      |______|______|______|\n", //  9
	"              |      |      |      |      |      |              \n", // 10
	"              |      |      |      |      |      |              \n", // 11
	" ______ ______|______|______|______|______|______|______ ______ \n", // 12
	"|      |      |      |      |      |      |      |      |      |\n", // 13
	"|      |      |      |      |      |      |      |      |      |\n", // 14
	"|______|______|______|______|______|______|______|______|______|\n", // 15
	"              |      |      |      |             |      |       \n", // 16
	"              |      |      |      |             |      |       \n", // 17
	" ______       |______|      |______|______ ______|______|       \n", // 18
	"|      |                    |      |      |      |              \n", // 19
	"|      |                    |      |      |      |              \n", // 20
	"|______|______ ______ ______|______|______|______|______ ______ \n", // 21
	"|      |      |      |      |      |      |      |      |      |\n", // 22
	"|      |      |      |      |      |      |      |      |      |\n", // 23
	"|______|______|______|______|______|      |______|______|______|\n", // 24
	"|      |             |      |             |      |      |      |\n", // 25
	"|      |             |      |             |      |      |      |\n", // 26
	"|______|             |______|             |______|      |______|\n"  // 27
};

void print_maze(int row, int col)
{
	setcursor(0, 20);
	for (int irow = 0; irow < 28; irow++)
	{
		if (irow == row)
		{
			for (int icol = 0; icol < 65; icol++)
			{
				if (icol == col)
				{
					cout << "X";
				}
				else
				{
					cout << maze_str[irow].substr(icol,1);	
				}
			}
		}
		else
		{
			cout << maze_str[irow];
		}
	}
}

// combat //

void monsterascii1(int image)
{
	if (image == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		setcursor(1, 6);
		printf("    _____         ");
		setcursor(1, 7);
		printf("   /     \\        ");
		setcursor(1, 8);
		printf("   |   O |       ");
		setcursor(1, 9);
		printf("   |     |       ");
		setcursor(1, 10);
		printf("   \\_____/        ");
		setcursor(1, 11);
		printf("    _||___        ");
		setcursor(1, 12);
		printf("   |______]----,  ");
		setcursor(1, 13);
		printf("   |     |-----'  ");
		setcursor(1, 14);
		printf("   |     |        ");
		setcursor(1, 15);
		printf("   |     |        ");
		setcursor(1, 16);
		printf("   |     |        ");
		setcursor(1, 17);
		printf("   |   | |        ");
		setcursor(1, 18);
		printf("   |   | |        ");
		setcursor(1, 19);
		printf("   |___|_|        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (image == 2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		setcursor(1, 6);
		printf("    _______     ");
		setcursor(1, 7);
		printf("   /       \\   ");
		setcursor(1, 8);
		printf("   | 0   0 |   ");
		setcursor(1, 9);
		printf("   \\   ^   /   ");
		setcursor(1, 10);
		printf("    \\_III_/    ");
		setcursor(1, 11);
		printf("    -__i__-    ");
		setcursor(1, 12);
		printf("   i __i__ i   ");
		setcursor(1, 13);
		printf("   i __i__ i   ");
		setcursor(1, 14);
		printf("   i   ^   i   ");
		setcursor(1, 15);
		printf("     i   i     ");
		setcursor(1, 16);
		printf("     i   i     ");
		setcursor(1, 17);
		printf("     i   i     ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void block_response()
{
	gcommon.block = false;
	int response;
	setcursor(25, 1);
	Fast_text("1 Block!\n");
	setcursor(25, 2);
	cin >> response;
	if (response != 2)
	{
		gcommon.attack = false;
	}
	gcommon.block = (response == 1);
}

void attack_response()
{
	gcommon.attack = false;
	int response;
	setcursor(25, 1);
	Fast_text("2 Attack!\n");
	setcursor(25, 2);
	cin >> response;
	if (response != 2)
	{
		gcommon.attack = false;
	}
	gcommon.attack = (response == 2);
}

int sleep_for_seconds(int seconds_in)
{
	this_thread::sleep_for(chrono::seconds(seconds_in));
	return 0;
}

void block_phase()
{
	bool block_success = false;
	thread threadObj(block_response);
	thread threadObjsleep(sleep_for_seconds, gcommon.response_seconds);
	threadObjsleep.join();
	block_success = gcommon.block;
	threadObj.join();
	if (block_success)
	{
		setcursor(25, 3);
		Fast_text("Block Successful");
	}
	else
	{
		setcursor(25, 3);
		Fast_text("Block too late");
		gcommon.hptotal = gcommon.hptotal - gcommon.enemyap;
		setcursor(25, 4);
		Fast_text("-HP");
	}
}

void attack_phase()
{
	bool attack_success = false;
	thread threadObj(attack_response);
	thread threadObjsleep(sleep_for_seconds, gcommon.response_seconds);
	threadObjsleep.join();
	attack_success = gcommon.attack;
	threadObj.join();
	if (attack_success)
	{
		setcursor(25, 3);
		Fast_text("Attack Successful");
		gcommon.enemyhp = gcommon.enemyhp - gcommon.aptotal;
		gcommon.durtotal = gcommon.durtotal - 1;

	}
	else
	{
		setcursor(25, 3);
		Fast_text("Attack too late");
		gcommon.hptotal = gcommon.hptotal - gcommon.enemyap;
		setcursor(25, 4);
		Fast_text("REPOST! -HP");
	}

}

void Monster(int ap, int hp, string name, int image) 
{
	gcommon.enemyap = ap;
	gcommon.enemyhp = hp;
	int rnum;
	system("cls");
	monsterascii1(image);
	print_maze(gcommon.myrow, gcommon.mycol);
	perm_stats();
	monsterstat();
	setcursor(25, 1);
	Fast_text("You have come across a ");
	cout << name;
	Fast_text("! it does not look very friendly...");
	setcursor(25, 2);
	Fast_text("Be prepared for an attack!");
	wait();
	system("cls");
	monsterascii1(image);
	print_maze(gcommon.myrow, gcommon.mycol);
	perm_stats();
	monsterstat();
	do
	{
		rnum = randnum(2);
		if (rnum > 0)
		{
			block_phase();
			system("cls");
			monsterascii1(image);
			print_maze(gcommon.myrow, gcommon.mycol);
			perm_stats();
			monsterstat();
		}
		else (rnum == 0);
		{
			attack_phase();
			system("cls");
			monsterascii1(image);
			print_maze(gcommon.myrow, gcommon.mycol);
			perm_stats();
			monsterstat();
		}
		if (gcommon.durtotal <= 0)
		{
			setcursor(1, 6);
			Fast_text("Your weapon broke you are defenseless!");
			wait();
			gcommon.hptotal = 0;
			system("cls");
		}
	} 
	while(gcommon.hptotal > 0 && gcommon.enemyhp > 0);
	if (gcommon.hptotal <= 0)
	{
		setcursor(25, 1);
		Fast_text("YOU DIED");
		wait();
		exit(0);
	}
	else if (gcommon.enemyhp <= 0)
	{
		setcursor(25, 1);
		Fast_text("Enemy killed");
		wait();
	}
}

// Gameplay //

bool gameplay() 
{
	int direction;
	int current_room_num = 24;
	int decidefinish{}, finish;
	int itemchance, yesnoitem, Aitem;
	string str_room_selection;
	ARoom current_room;
	init_rooms();
	system("cls");
	Beginning_dialogue();
	decidefinish = randnum(9);
	switch (decidefinish)
	{
	case 0:
		finish = 1;
		break;
	case 1:
		finish = 2;
		break;
	case 2:
		finish = 4;
		break;	
	case 3:
		finish = 16;
		break;	
	case 4:
		finish = 20;
		break;	
	case 5:
		finish = 28;
		break;	
	case 6:
		finish = 32;
		break;	
	case 7:
		finish = 44;
		break;	
	case 8:
		finish = 45;
		break;	
	case 9:
		finish = 46;
		break;	
	case 10:
		finish = 47;
		break;	
	}

	do
	{
		current_room = rooms[current_room_num];
		gcommon.mycol = current_room.xCol;
		gcommon.myrow = current_room.xRow;
		print_maze(gcommon.myrow, gcommon.mycol);
		
		// If not visited monsters appear //

		if (rooms[current_room_num].visited == false)
		{
			Monster(current_room.eap, current_room.ehp, current_room.monster, current_room.monsterascii);
			system("cls");
			perm_stats();
			print_maze(gcommon.myrow, gcommon.mycol);
			itemchance = randnum(3);
			Aitem = randnum(2);
			if (itemchance == 0)
			{
				setcursor(25, 1);
				Fast_text("You found a weapon! Would you like to swap your weapon with this one?");
				setcursor(25, 2);
				Fast_text("1 yes");
				setcursor(25, 3);
				Fast_text("2 no\n");
				setcursor(25, 4);
				cin >> yesnoitem;
				system("cls");
				if (yesnoitem == 1) 
				{
					if (Aitem == 0)
					{
						gcommon.aptotal = gcommon.ap + 10;
						gcommon.durtotal = 30;
						if (gcommon.Ring == "Wood Grain Ring")
						{
							gcommon.durtotal = 50;
						}
						gcommon.Weapon = "Shortsword";
						setcursor(25, 1);
						Fast_text("You picked up a Shortsword!");
					}
					else if (Aitem == 1) 
					{
						gcommon.aptotal = gcommon.ap + 20;
						gcommon.durtotal = 20;
						if (gcommon.Ring == "Wood Grain Ring")
						{
							gcommon.durtotal = 40;
						}
						gcommon.Weapon = "Longsword";
						setcursor(25, 1);
						Fast_text("You picked up a Longsword!");
					}
					else if (Aitem == 2)
					{
						gcommon.aptotal = gcommon.ap + 30;
						gcommon.durtotal = 10;
						if (gcommon.Ring == "Wood Grain Ring")
						{
							gcommon.durtotal = 30;
						}
						gcommon.Weapon = "Greatsword";
						setcursor(25, 1);
						Fast_text("You picked up a Greatsword!");
					}
					wait();
				}
			}

		}
		rooms[current_room_num].visited = true;

		system("cls");
		perm_stats();
		print_maze(gcommon.myrow, gcommon.mycol);

		// Decides if they can or can not go in a direction, then changes them to the room they picked //

		str_room_selection = "Where would you like to go?\n\n";

		if (current_room.up != 0)
		{
			str_room_selection += " 1 Up\n";
		}
		if (current_room.down != 0)
		{
			str_room_selection += " 2 Down\n";
		}
		if (current_room.left != 0)
		{
			str_room_selection += " 3 Left\n";
		}
		if (current_room.right != 0)
		{
			str_room_selection += " 4 Right\n";
		}

		setcursor(1, 6);
		Fast_text(str_room_selection);

		do
		{
			setcursor(1, 12);
			cin >> direction;

			if (direction == 1 && current_room.up == 0)
			{
				Fast_text("You can't go that way!");
				system("cls");
			}
			else if (direction == 2 && current_room.down == 0)
			{
				Fast_text("You can't go that way!");
				system("cls");
			}
			else if (direction == 3 && current_room.left == 0)
			{
				Fast_text("You can't go that way!");
				system("cls");
			}
			else if (direction == 4 && current_room.right == 0)
			{
				Fast_text("You can't go that way!");
				system("cls");
			}

		} while (direction == 1 && current_room.up == 0 || direction == 2 && current_room.down == 0 || direction == 3 && current_room.left == 0 || direction == 4 && current_room.right == 0);
		
		if (direction == 1)
		{
			current_room_num = current_room.up;
		}
		else if (direction == 2)
		{
			current_room_num = current_room.down;
		}
		else if (direction == 3)
		{
			current_room_num = current_room.left;
		}
		else if (direction == 4)
		{
			current_room_num = current_room.right;
		}

	} 
	while (current_room_num != finish);
	
	system("cls");

	current_room_num = finish;
	
	Monster(current_room.eap, current_room.ehp, "FINALBOSS", 2);
	
	printf("YOU WON!!!!!");

	return 0;
}

int main()
{
	int seed;
	seed = (int)time(NULL);
	srand(seed);

	commonvariables gcommon = commonvariables();
	printf("TURN TO FULL SCREEN BEFORE MOVING ON");
	wait();
	system("cls");
	menu();		
	gameplay();
}


