#pragma once
#include <string>

class Player;

class Item
{
protected:
	int id;
	std::string name;
	std::string description;
	int price;

public:
	/* Constructor */
	Item(int id, const std::string& name, const std::string& description, int price)
		: id(id), name(name), description(description), price(price) {}
	
	/* Destructor */
	virtual ~Item() = default;

	/* Member methods */
	virtual void use(Player& player) = 0;
	virtual bool isConsumable() const = 0;
	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	int getPrice() const { return price; }
	int getId() const { return id; }
};

/* Derived Classes */
class HP_Potion : public Item 
{
public:
	HP_Potion() : Item(1, "HP포션", "체력을 10 회복시키는 포션", 15) {}	// TODO: Constants
	void use(Player& player) override;
	bool isConsumable() const override { return true; }
};

class AttackBoost : public Item
{
public:
	AttackBoost() : Item(2, "힘의 영약", "공격력을 10 증가시킵니다", 25) {}	// TODO: Constants
	void use(Player& player) override;	
	bool isConsumable() const override { return true; }
};

class CriticalBoost : public Item
{
public:
	CriticalBoost() : Item(3, "치명타 확률 영약", "치명타확률을 10 증가시킵니다", 30) {}	// TODO: Constants
	void use(Player& player) override;
	bool isConsumable() const override { return true; }
};

// TODO: 무기/ 방어구 아이템 구현 + 장착 + player 멤버변수 추가