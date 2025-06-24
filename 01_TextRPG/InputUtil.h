#pragma once
#include <iostream>
#include <algorithm>

// 사용법: int randInt = RandomUtil::getInt(1, 10);		// 1~10 사이의 난수 
namespace InputUtil{
	inline std::string getStr(const std::string& prompt = "문자열을 입력해주세요: ")
	{
		std::string input;
		while(true)
		{
			std::cout << prompt;
			std::getline(std::cin, input);

			if (input.empty())	// 빈 입력 방지
			{
				std::cout << "입력이 비었습니다. 다시 입력하세요.\n";
				continue;
			}
			break;
		}
		return input;
	}

	inline int getInt(const std::string& prompt = "숫자를 입력해주세요: ")
	{

		// std::cout << "[FOR DEBUG : InputUtil > getInt ]\n";
		int choice;
		std::string input;
		while(true)
		{
			std::cout << prompt;
			std::getline(std::cin, input);

			if (input.empty())		// 빈 입력 방지 
			{
				std::cout << "입력이 비었습니다. 다시 입력하세요\n";
				continue;
			}

			// 공백제거
			input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

			try {
				size_t idx;
				choice = std::stoi(input, &idx);
				if (idx != input.size())
					throw std::invalid_argument("Not a number");
				break;
			}
			catch (...) {
				std::cout << "잘못된 입력입니다. 숫자만 입력하세요\n";
			}
		}
		return choice;
	}

	inline char getYorN(const std::string& prompt = "Y 또는 N을 입력해주세요: ")
	{
		// std::cout << "[FOR DEBUG : InputUtil > getYorN ]\n";
		std::string answer;
		while (true)
		{
			std::cout << prompt;
			if (!std::getline(std::cin, answer))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "입력 오류가 발생했습니다. 다시 시도해주세요\n";
				continue;
			}

			answer.erase(remove_if(answer.begin(), answer.end(), ::isspace), answer.end());
			std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

			if (answer == "Y" || answer == "YES")		return 'Y';
			else if (answer == "N" || answer == "NO")	return 'N';
			else std::cout << "잘못된 입력입니다. Y 또는 N만 입력해주세요.\n";
		}
	}
}