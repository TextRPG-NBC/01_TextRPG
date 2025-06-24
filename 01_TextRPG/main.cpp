#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "GameManager.h"
#include "PrintUtil.h"
#include "Monster.h"


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// 메모리 누수 확인
	std::wcout.imbue(std::locale("ko_KR.UTF-8"));	// 한글 입력 예외처리(한국어 UTF-8 로케일 적용)

	/* 메모리 누수 확인용 코드 : delete 하지 않기*/
	//Monster* monster = new Goblin(3);

	PrintUtil::printTitle();
	GameManager gameManager;
	gameManager.run();
	PrintUtil::printGameOver();

	return 0;
}