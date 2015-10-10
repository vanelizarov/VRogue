// VRogue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "GameSystem.h"

using namespace std;

int main() {

	GameSystem gameSystem("level1.map");

	gameSystem.playGame();

    return 0;
}

