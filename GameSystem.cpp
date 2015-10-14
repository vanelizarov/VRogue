#include "stdafx.h"
#include "GameSystem.h"

#include <conio.h>
#include "Utilities.h"
#include "Strings.h"


using namespace std;

//constructor, that sets up the game
GameSystem::GameSystem(string levelFileName) {

	_player.init(1, 100, 10, 10, 0);
	_level.load(levelFileName, _player);

	char start;
	cls();
	center("VROGUE\n", 11);
	center("", 12);
	center("Press any key to start", 13);
	start = _getch();
	if (start != '\0') {
		cls();
	}

}

void GameSystem::playGame() {

	bool isDone = false;

	while (!isDone) {

		_level.print();
		playerMove();
		_level.updateEnemies(_player);
		
	}

}

void GameSystem::playerMove() {

	char input;
	printf("Enter a move command w/s/a/d:");
	input = _getch();

	_level.movePlayer(input, _player);

}


GameSystem::~GameSystem() {
}
