#include <iostream>
#include "GameManager.h"

int main() {
	std::wcout.imbue(std::locale("ko_KR.UTF-8"));	// 한글 입력 예외처리(한국어 UTF-8 로케일 적용)

	std::cout << "==========[ Text R.P.G ]==========\n";
	GameManager gameManager;
	gameManager.run();
	std::cout << "==========[  Game Over  ]==========\n";
	return 0;
}