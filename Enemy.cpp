#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(string name, char tile, int level, int attack, int defence, int health, int xp) {

	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defence = defence;
	_health = health;
	_experienceValue = xp;

}

//sets the enemy position
void Enemy::setPosition(int x, int y) {

	_x = x;
	_y = y;

}

//gets enemy position
void Enemy::getPosition(int & x, int & y) {

	x = _x;
	y = _y;

}

string Enemy::getName() {
	return _name;
}

int Enemy::attack() {

	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack) {

	attack -= _defence;

	if (attack > 0) {
		_health -= attack;

		if (_health <= 0) {
			return _experienceValue;
		}
	}

	return 0;
}

Enemy::~Enemy() {
}
