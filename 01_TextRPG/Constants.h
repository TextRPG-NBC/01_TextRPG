#pragma once
#include <string>

namespace Constants {
	// 정수형 상수
	constexpr int MIN_LEVEL = 1;
	constexpr int MAX_LEVEL = 10;
	constexpr int NORMAL_MONSTER_TYPE = 3;

	// 문자열 상수
	extern const char* GAME_TITLE;	// C++14는 inline 지원 X, cpp 파일에서 정의 필요
	extern const char* VERSION;


	// --- enum 정의 ---
	enum MonsterType {
		GOBLIN = 1,
		ORC = 2,
		TROLL = 3,
	};

	enum class ItemType {
		HEALTH_POTION,
		ATTACK_BOOST,
		CRITICAL_BOOST,
	};

	enum class CharacterState {
		DEAD,
		ALIVE,
	};
}
// Constants::ItemType::HEALTH_POTION
// Constants::GOBLIN 처럼 사용 가능