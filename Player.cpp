#include "stdafx.h"
#include "Player.h"

//constructor, that initializes position to zero
Player::Player() {
	
	_x = 0;
	_y = 0;

}

//initialize player with properties
void Player::init(int level, int health, int attack, int defence, int experience) {
	
	_level = level;
	_health = health;
	_attack = attack;
	_defence = defence;
	_experience = experience;

}

int Player::attack() {

	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Player::takeDamage(int attack) {

	attack -= _defence;

	if (attack > 0) {
		_health -= attack;

		if (_health <= 0) {
			return 1;
		}
	}

	return 0;
}


//sets the player position
void Player::setPosition(int x, int y) {
	
	_x = x;
	_y = y;

}

void Player::addExperience(int experience) {

	_experience += experience;
	while (_experience > 50) {
		printf("Leveled up!\n");
		_experience -= 50;
		_attack += 10;
		_defence == 5;
		_health += 10;
		_level++;
		system("pause");
	}

}

//gets player position
void Player::getPosition(int & x, int & y) {

	x = _x;
	y = _y;

}


Player::~Player() {
}
