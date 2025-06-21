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