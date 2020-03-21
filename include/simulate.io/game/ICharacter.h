#pragma once

#include <string>


class ICharacter
{
public:

	virtual std::string Getname() const = 0;

	virtual int GetHealth() const = 0;

	virtual void GetDamaged(int const InitialDamage) = 0;

	virtual int DealDamage() const = 0;

	virtual ~ICharacter() = default;
};