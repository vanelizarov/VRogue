#pragma once

#include "stdafx.h"
#include <random>
#include <ctime>

using namespace std;

class Player {
public:
	Player();

	void init(int level, int health, int attack, int defence, int experience);

	int attack();
	int takeDamage(int attack);

	//setters
	void setPosition(int x, int y);
	void addExperience(int experience);

	//getters
	void getPosition(int &x, int &y);
	int getHealth(int &health) { return _health; }

	~Player();

private:

	//properties
	int _level;
	int _health;
	int _attack;
	int _defence;
	int _experience;

	//position
	int _x;
	int _y;

	
};

