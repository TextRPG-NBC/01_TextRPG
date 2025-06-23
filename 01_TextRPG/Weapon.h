#pragma once

#include"IItem.h"
#include<memory>


class Weapon : public IItem
{
public:
	Weapon(const std::string& name = "나뭇가지", int attackBonus = 5,int criticalBonus=2,int price = 1);

	virtual void use(Character* character) override;

	virtual std::string getName() const override;
	virtual int getPrice() const override;
	virtual std::unique_ptr<IItem> clone() const override;

	int getAttackBonus() const;
	int getCriticalBonus() const;

private:
	std::string name;
	int price;
	int attackBonus;
	int criticalBonus;

};

