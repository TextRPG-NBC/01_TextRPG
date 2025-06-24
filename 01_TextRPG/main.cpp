#include <iostream>
#include "GameManager.h"
#include "PrintUtil.h"

int main() {
	std::wcout.imbue(std::locale("ko_KR.UTF-8"));	// 한글 입력 예외처리(한국어 UTF-8 로케일 적용)

	PrintUtil::printTitle();
	GameManager gameManager;
	gameManager.run();
	PrintUtil::printGameOver();
	return 0;
}