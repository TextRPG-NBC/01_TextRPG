#include "GameManager.h"
#include <iostream>

int main() {
	std::cout << "==========[ Text R.P.G ]==========\n";
	GameManager gameManager;
	gameManager.run();
	std::cout << "==========[  Game Over  ]==========\n";
	return 0;
}