#pragma once
#include <iostream>

// 사용법: PrintUtil::clearScreen();
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
		std::cout << "| 1. 구매하기                    |\n";
		std::cout << "| 2. 판매하기                    |\n";
		std::cout << "| 3. 상태조회                    |\n";
		std::cout << "| 0. 뒤로가기                    |\n";
		std::cout << "|                                |\n";
		std::cout << "===================================\n";
	}

	inline void clearScreen()
	{
		for (int i = 0; i < 40; ++i) 
		{
			std::cout << "\n";
		}
	}
}