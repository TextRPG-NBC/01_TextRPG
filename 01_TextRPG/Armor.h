#pragma once

#include "IItem.h"
#include<memory>

class Armor : public IItem
{
public:
	Armor(const std::string& name = "누더기 천 조각", int maxHealthBonus=10,int price = 1);

	virtual void use(Character* character) override;
	
	virtual std::string getName() const override;
	virtual int getPrice() const override;
	
	int getMaxHealthBonus() const;
private:
	std::string name;
	int price;
	int maxHealthBonus;
};

