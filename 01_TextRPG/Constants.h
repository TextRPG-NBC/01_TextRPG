#pragma once
#include <string>

// Constants::ItemType::HEALTH_POTION
// Constants::GOBLIN 처럼 사용 가능
namespace Constants {
	// 정수형 상수(P : 확률)
	constexpr int MIN_DROP_GOLD = 10;
	constexpr int MAX_DROP_GOLD = 20;
	constexpr int DROP_EXP = 50;
	constexpr int MAX_LEVEL = 10;
	constexpr float SELL_RATE = 0.6f;



	constexpr int MIN_LEVEL = 1;
	

	// 문자열 상수(쓰지말자)
	extern const char* GAME_TITLE;	// C++14는 inline 지원 X, cpp 파일에서 정의 필요
	extern const char* VERSION;


	// --- enum 정의 ---
	enum Probability {			// 확률(P_)
		P_USE_ITEM = 20,
		P_DROP_ITEM = 30,
	};

	enum ShopMenu {				// 상점 메뉴
		EXIT = 0,
		BUY = 1,
		SELL = 2,
		STATUS = 3,
	};
	
	enum NormalMonsterType {	// 보통 몬스터 타입
		GOBLIN = 1,
		ORC = 2,
		TROLL = 3,
		NORMAL_MONSTER_TYPE = 3,
	};

	//TODO: 보스 몬스터 타입

	enum ItemType {
		HP_POTION = 1,
		ATTACK_BOOST = 2,
		CRITICAL_BOOST = 3,
	};

}
