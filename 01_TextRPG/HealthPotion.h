#pragma once

#include"IItem.h"

class HealthPotion : public IItem
{
public:
	HealthPotion(const std::string& name = "소량의 회복 물약", int healAmount = 10,int price=1);

	virtual void use(Character* character) override;

	virtual std::string getName() const override;
	virtual int getPrice()const override;
	virtual std::unique_ptr<IItem> clone() const override;

	int getHealAmount()const;

private:
	std::string name;
	int price;
	int healAmount;

};

