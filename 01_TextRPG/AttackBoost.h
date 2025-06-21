#pragma once

#include "IItem.h"

class AttackBoost : public IItem
{
public:
	AttackBoost(const std::string& name = "하급 공격력 영약", int boostAmount = 5,int price = 1);

	virtual void use(Character* character) override;

	virtual std::string getName() const override;
	virtual int getPrice() const override;

	int getBoostAmount() const;

private:
	std::string name;
	int price;
	int boostAmount;
};

