#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(string name, char tile, int level, int attack, int defence, int health, int xp, int attackRange) {

	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defence = defence;
	_health = health;
	_experienceValue = xp;
	_attackRange = attackRange;
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

char Enemy::getMove(int playerX, int playerY) {

	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, _attackRange);

	int distance;

	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);

	distance = adx + ady;

	if (distance <= _attackRange) {
		if (adx > ady) {
			//move along x axis
			if (dx > 0) {
				return 'a';
			} else {
				return 'd';
			}
		}
		else {
			//move along y axis
			if (dy > 0) {
				return 'w';
			} else {
				return 's';
			}
		}
	}

	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return ' ';
	}

}

Enemy::~Enemy() {
}
