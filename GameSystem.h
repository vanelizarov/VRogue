#pragma once

#include "stdafx.h"
#include "Player.h"
#include "Level.h"


using namespace std;

class GameSystem {
public:
	GameSystem(string levelFileName);

	void playGame();
	void playerMove();

	~GameSystem();

private:
	Level _level;
	Player _player;
	
	
};

