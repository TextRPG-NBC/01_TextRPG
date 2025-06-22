
// *** 아이템 사용안내 ***
// 아이템은 기본적으로는 std::make_unqiue<IItem 상속클래스> 로 생성해서 추가함.
// 너무 길어서 Items.h 에서 makeWeapon, makeHealthPotion 등등 제공.
// 현재 생성 가능한 아이템은 Weapon, Armor, HealthPotion, AttackBoost, CriticalBoost, HealthBoost 이며 
// IItem은 인터페이스 클래스이므로 생성할 수 없음.

// 아이템 생성 예시.
// std::make_unique<Weapon>("나뭇가지",5,2,5) 
// 웨폰의 경우 이름, 공격력, 치명타율, 가격 순. 웨폰을 제외한 모든 아이템은 이름, 효과량, 가격 순서의 3개의 파라미터.
// #include "SItem.h" 를 했을 경우
// makeArmor("누더기 옷",20,5); 처럼 숏컷.



#pragma once

#include <string>

class Character;
class IItem
{
public:
	virtual void use(Character* character) = 0;

	virtual std::string getName() const = 0;
	virtual int getPrice() const = 0;

	virtual ~IItem() = default;
};