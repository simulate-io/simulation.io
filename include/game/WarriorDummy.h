#pragma once

#include "ICharacter.h"

#include <string>


class WarriorDummy : public ICharacter
{
public:

	WarriorDummy() {
		//KE: for now 100 is max later it will be dynamic param
		m_maxHealth = 100;
		m_currentHealth = 100;
	};

	std::string GetName() const override {return m_name;}

	int GetHealth() const override { return m_currentHealth; }

	void GetDamaged(int const damage) override {m_currentHealth -= damage;}

	int DealDamage() const override { return 25; }

	~WarriorDummy() override {};

private:
	int m_maxHealth;
	int m_currentHealth;
	std::string m_name;
};
