#pragma once

#include "stdafx.h"
#include <ctime>
#include <random>

using namespace std;

class Enemy {
public:
	Enemy(string name, char tile, int level, int attack, int defence, int health, int xp, int attackRange);
	~Enemy();

	int attack();
	int takeDamage(int attack);

	//get AI move command
	char getMove(int playerX, int playerY);

	//setters
	void setPosition(int x, int y);

	//getters
	void getPosition(int &x, int &y);
	string getName() { return _name; }
	char getTile() { return _tile; }

private:
	//properties;
	string _name;
	char _tile;

	int _attack;
	int _defence;
	int _health;
	int _experienceValue;
	int _level;
	int _attackRange;

	//position

	int _x;
	int _y;

};

