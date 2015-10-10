#include "stdafx.h"
#include "GameSystem.h"
#include <iostream>
#include <conio.h>

//constructor, that sets up the game
GameSystem::GameSystem(string levelFileName) {

	_player.init(1, 100, 10, 10, 0);
	_level.load(levelFileName, _player);

	system("pause");

}

void GameSystem::playGame() {

	bool isDone = false;

	while (!isDone) {

		_level.print();
		playerMove();

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
