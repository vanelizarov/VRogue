#pragma once

#include <string>
#include <ctime>
#include <random>

using namespace std;

class Enemy {
public:
	Enemy(string name, char tile, int level, int attack, int defence, int health, int xp);
	~Enemy();

	int attack();
	int takeDamage(int attack);

	//setters
	void setPosition(int x, int y);

	//getters
	void getPosition(int &x, int &y);
	string getName();

private:
	//properties;
	string _name;
	char _tile;

	int _attack;
	int _defence;
	int _health;
	int _experienceValue;
	int _level;

	//position

	int _x;
	int _y;

};

