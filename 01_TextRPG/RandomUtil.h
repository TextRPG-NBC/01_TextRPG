#pragma once

#include <random>
#include <limits>

// 사용법: int randInt = RandomUtil::getInt(1, 10);		// 1~10 사이의 난수 
namespace RandomUtil {
	// 전역 static random 엔진
	inline std::mt19937& engine()
	{
		static std::mt19937 eng{ std::random_device{}() }; // 최초 1회 시드
		return eng;
	}

	// 정수형 범위 난수 (a~b)
	inline int getInt(int a, int b)
	{
		std::uniform_int_distribution<int> dist(a, b);
		return dist(engine());
	}
}