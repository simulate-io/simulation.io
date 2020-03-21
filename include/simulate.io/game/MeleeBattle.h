#pragma once

#include "IBattle.h"
#include "ICharacter.h"

class MeleeBattle : public IBattle
{
public:

	MeleeBattle() = delete;

	MeleeBattle(ICharacter&& h1, ICharacter&& h2)
	: m_HeroAtacker(h1),
	m_HeroDefender(h2) {}

	/* @brief: Starts the fight with given heroes */
	void BeginFight() override;

	/* @brief: Logs results of the battle to console */
	void LogResults();

	~MeleeBattle() override {}

private:
	ICharacter& m_HeroAtacker;
	ICharacter& m_HeroDefender;
};
