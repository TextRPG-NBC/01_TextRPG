#pragma once
#include <string>

// Constants::ItemType::HEALTH_POTION
// Constants::GOBLIN 처럼 사용 가능
namespace Constants {
	// 정수형 상수(P : 확률)
	constexpr int MIN_DROP_GOLD = 10;
	constexpr int MAX_DROP_GOLD = 20;
	constexpr int DROP_EXP = 50;
	constexpr float SELL_RATE = 0.6f;

	// 문자열 상수 : C++14는 inline 지원 X, cpp 파일에서 정의 필요


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

	enum MonsterStatus {
		NM_MIN_HP_RATE = 20,
		NM_MAX_HP_RATE = 30,
		BS_MIN_HP_RATE = 30,
		BS_MAX_HP_RATE = 45,
		NM_MIN_ATK_RATE = 5,
		NM_MAX_ATK_RATE = 10,
		BS_MIN_ATK_RATE = 8,
		BS_MAX_ATK_RATE = 15,
	};

	enum PlayerStatus {
		DEFAULT_LEVEL = 1,
		DEFAULT_HP = 200,
		DEFAULT_ATK = 30,
		DEFAULT_EXP = 0,
		DEFAULT_GOLD = 0,
		DEFAULT_CRITICAL_DAMAGE = 2,
		MAX_EXP = 100,
		MAX_LEVEL = 10,
		LEVEL_HP_RATE = 20,
		LEVEL_ATK_RATE = 5,
	};

	enum ItemType {
		HP_POTION = 1,
		ATTACK_BOOST = 2,
		CRITICAL_BOOST = 3,
		TREE_BRANCH = 4,
		LEATHER_ARMOR = 5,
	};

	enum ItemPrice {
		PRICE_HP_POTION = 10,
		PRICE_ATTACK_BOOST = 15,
		PRICE_CRITICAL_BOOST = 15,
		PRICE_TREE_BRANCH = 15,
		PRICE_LEATHER_ARMOR = 15,
	};

	enum ItemAbility {
		AB_HP_POTION = 50,
		AB_ATTACK_BOOST = 10,
		AB_CRITICAL_BOOST = 10,
		AB_TREE_BRANCH_ATK = 10,
		AB_TREE_BRANCH_CRI = 5,
		AB_LEATHER_ARMOR = 15,
	};
}
