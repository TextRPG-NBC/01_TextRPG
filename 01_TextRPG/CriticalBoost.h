#pragma once

#include<string>
#include"IItem.h"

class Character;
class CriticalBoost : public IItem
{
public:
	CriticalBoost(const std::string& name = "하급 치명타 영약", int boostAmount = 5, int price = 1);

	virtual void use(Character* character) override;

	virtual std::string getName() const override;
	virtual int getPrice() const override;
	virtual std::unique_ptr<IItem> clone() const override;

	int getBoostAmount()const;

private:
	std::string name;
	int price;
	int boostAmount;
};

