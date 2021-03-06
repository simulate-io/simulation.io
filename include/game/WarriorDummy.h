#pragma once

#include <string>

#include "ICharacter.h"

class WarriorDummy : public ICharacter
{
public:

    WarriorDummy() {
		//KE: for now 100 is max later it will be dynamic param
		m_maxHealth = 100;
		m_currentHealth = 100;
	};

	WarriorDummy(std::string name, int maxHealth, int damage)
        :m_maxHealth(maxHealth),
         m_currentHealth(m_maxHealth),
         m_name(name),
         m_dealDamage(damage)
    {};

	std::string GetName() const override { return m_name; }

	int GetHealth() const override { return m_currentHealth; }

	void GetDamaged(int const damage) override { m_currentHealth -= damage; }

	int DealDamage() const override { return m_dealDamage; }

	~WarriorDummy() override {};

private:
	int m_maxHealth;
	int m_currentHealth;
    int m_dealDamage;
	std::string m_name;
};
