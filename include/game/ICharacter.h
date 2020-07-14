#pragma once

#include <string>
#include <utility>


class ICharacter
{
public:

	virtual std::string GetName() const = 0;

	virtual int GetHealth() const = 0;

	virtual void GetDamaged(int const InitialDamage) = 0;

	virtual int DealDamage() const = 0;

	virtual ~ICharacter() = default;
};

typedef std::pair<ICharacter&, ICharacter&> FightersPair_t;