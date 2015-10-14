#include "stdafx.h"
#include "Level.h"
#include "GameSystem.h"
#include <fstream>
#include <sstream>
#include <mmsystem.h>

Level::Level() {
}


void Level::load(string fileName, Player &player) {

	_fileName = fileName;

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
				_enemies.push_back(Enemy("Goblin", tile, 1, 3, 1, 100, 10, 5));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //ogre
				_enemies.push_back(Enemy("Ogre", tile, 5, 20, 50, 50, 100, 10));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': //dragon
				_enemies.push_back(Enemy("Dragon", tile, 100, 500, 1000, 1000, 1000, 20));
				_enemies.back().setPosition(j, i);
				break;
			}

		}
	}

}


void Level::print() {
	
	cls();

	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {

			switch (_levelData[i][j]) {
			case '&': //flame
				setColor(consoleColor(0, 6));
				break;
			case '0': //door
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				setColor(consoleColor(0, 3));
				break;
			case '@': //player
				setColor(consoleColor(0, 9));
				break;
			case 'g': //goblin
				setColor(consoleColor(0, 12));
				break;
			case 'O': //ogre
				setColor(consoleColor(0, 14));
				break;
			case 'D': //dragon
				setColor(consoleColor(0, 4));
				break;
			default:
				setColor(consoleColor(0, 7));
				break;
			}
			printf("%c", _levelData[i][j]);

		}
		
		printf("\n");

	}

	printf("\n");

	//cls();


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

void Level::updateEnemies(Player & player) {

	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;
	player.getPosition(playerX, playerY);
	

	for (int i = 0; i < _enemies.size(); i++) {
		char aiMove = _enemies[i].getMove(playerX, playerY);

		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove) {

		case 'w': //up
		
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's': //down
		
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a': //left
		
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd': //right
		
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		
		}
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
	case '&':
	case '|':
	case '+':
	case '-':
	case '#':
		break;
	case '0': //door
	case '1':
	case '2':
	case '3':
	case '4': {
	//case '5':
	//case '6':
	//case '7':
	//case '8':
	//case '9': {
		
		_levelData.clear();
		_enemies.clear();
		stringstream ss;
		ss << "level" << moveTile << ".map";
		

		load(ss.str(), player);
		break;
	}
	default:
		battleEnemy(player, targetX, targetY);
		break;
	}

}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {

	int playerX, playerY;
	int enemyX, enemyY;
	player.getPosition(playerX, playerY);
	_enemies[enemyIndex].getPosition(enemyX, enemyY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case ' ':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, ' ');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '&':
	case '|':
	case '+':
	case '-':
	case '#':
		break;
	case '0': //door
	case '1':
	case '2':
	case '3':
	case '4':
	//case '5':
	//case '6':
	//case '7':
	//case '8':
	//case '9': 
		break;
	case '@':
		battleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}

}

void Level::battleEnemy(Player & player, int targetX, int targetY) {

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
			//printf("\nPlayer attacked %s with a roll of %d\n", _enemies[i].getName().c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0) {

				setTile(targetX, targetY, ' ');
				print();
				PlaySound(TEXT("beep.wav"), NULL, SND_FILENAME);
				//printf("\n%s died\n", _enemies[i].getName().c_str());

				//remove enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				player.addExperience(attackResult);
				system("pause");

				return;
			}
			
			attackRoll = _enemies[i].attack();
			//printf("\n%s attacked player with a roll of %d\n", _enemies[i].getName().c_str(), attackRoll);
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
