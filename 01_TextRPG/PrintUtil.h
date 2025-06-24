#pragma once
#include <iostream>
#include "Constants.h"

// 사용법: PrintUtil::printTitle();
namespace PrintUtil {
	inline void printTitle()
	{
		std::cout << "==========[ Text R.P.G ]===========\n";
		std::cout << "|                                 |\n";
		std::cout << "|           모험의 시작           |\n";
		std::cout << "|                                 |\n";
		std::cout << "===================================\n";
	}

	inline void printGameOver()
	{
		std::cout << "==========[  Game Over  ]==========\n";
	}

	inline void printShopMenu()
	{
		std::cout << "\n===========[ 상점 메뉴] ==========\n";
		std::cout << "|                                |\n";
		std::cout << "| " << Constants::BUY << ". 구매하기                    |\n";
		std::cout << "| " << Constants::SELL << ". 판매하기                    | \n";
		std::cout << "| " << Constants::STATUS << ". 상태조회                    |\n";
		std::cout << "| " << Constants::EXIT << ". 뒤로가기                    |\n";
		std::cout << "|                                |\n";
		std::cout << "===================================\n";
	}
}