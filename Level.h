#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level {
public:
	Level();

	void load(string fileName, Player &player);
	void print();

	void movePlayer(char input, Player &player);


	~Level();

private:
	vector <string> _levelData;
	vector <Enemy> _enemies;

	void processPlayerMove(Player &player, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);

	//getters
	char getTile(int x, int y);
	//setters
	void setTile(int x, int y, char tile);
};

