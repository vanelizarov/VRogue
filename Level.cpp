#include "stdafx.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>


Level::Level() {
}

void Level::load(string fileName, Player &player) {

	//loads the level
	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}

	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	//process the level
	char tile;

	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {

			case '@': //player
				player.setPosition(j, i);
				break;
			case 'g': //goblin
				_enemies.push_back(Enemy("Goblin", tile, 1, 3, 1, 10, 10));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //ogre
				_enemies.push_back(Enemy("Ogre", tile, 5, 20, 50, 100, 100));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': //dragon
				_enemies.push_back(Enemy("Dragon", tile, 100, 500, 1000, 1000, 1000));
				_enemies.back().setPosition(j, i);
				break;
			}

		}
	}

}

void Level::print() {

	cout << string(100, '\n');

	for (int i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());
	}

	printf("\n");

}

void Level::movePlayer(char input, Player &player) {

	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	switch (input) {

	case 'w': //up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's': //down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a': //left
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd': //right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("Invalid input.\n");
		system("pause");
		break;
	}

}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case ' ':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}

}

void Level::battleMonster(Player & player, int targetX, int targetY) {

	int enemyX;
	int enemyY; 
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		if (targetX == enemyX && targetY == enemyY) {
			//battle

			attackRoll = player.attack();
			printf("Player attacked %s with a roll of %d\n", _enemies[i].getName().c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0) {

				setTile(targetX, targetY, ' ');
				print();
				printf("%s died\n", _enemies[i].getName().c_str());
				system("pause");
				player.addExperience(attackResult);

				return;
			}
			
			attackRoll = _enemies[i].attack();
			printf("%s attacked player with a roll of %d\n", _enemies[i].getName().c_str(), attackRoll);
			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				print();
				printf("You died\n");
				system("pause");
				player.addExperience(attackResult);

				exit(0);
			}
			system("pause");
			return;
		}
	}

}

char Level::getTile(int x, int y) {

	return _levelData[y][x];

}

void Level::setTile(int x, int y, char tile) {

	_levelData[y][x] = tile;

}


Level::~Level() {
}
