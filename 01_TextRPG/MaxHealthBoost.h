#pragma once

#include"IItem.h"

class MaxHealthBoost : public IItem
{
public:
	MaxHealthBoost(const std::string& name = "하급 체력 영약", int boostAmount = 5,int price=1);

	virtual void use(Character* character) override;

	virtual std::string getName() const override;
	virtual int getPrice() const override;
	virtual std::unique_ptr<IItem> clone() const override;

	int getBoostAmount() const;

private:
	std::string name;
	int price;
	int boostAmount;

};

