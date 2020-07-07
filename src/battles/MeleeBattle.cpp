#include <iostream>

#include "utils/log/loguru.hpp"
#include "simulate.io/game/MeleeBattle.h"
#include "simulate.io/game/ICharacter.h"

void MeleeBattle::BeginFight()
{
	int damageAttacker, damageDefender;

	// KE: Simple battle loop until winner is determine
	while (m_HeroAttacker.GetHealth() > 0
		&& m_HeroDefender.GetHealth() > 0)
	{
		if (m_HeroAttacker.GetHealth() > 0)
		{
			damageAttacker = m_HeroAttacker.DealDamage();
			m_HeroDefender.GetDamaged(damageAttacker);
		}
		if (m_HeroDefender.GetHealth() > 0)
		{
			damageDefender = m_HeroDefender.DealDamage();
			m_HeroAttacker.GetDamaged(damageDefender);
		}
	}
}

// KE: log results of the battle to std
void MeleeBattle::LogResults() const
{
	if(m_HeroAttacker.GetHealth() > 0)
	{
		LOG_F(INFO, "Attacker Won");
	}
	else
	{
		LOG_F(INFO, "Attacker Lost");
	}

	if(m_HeroDefender.GetHealth() > 0)
	{
		LOG_F(INFO, "Defender Won");
	}
	else
	{
		LOG_F(INFO, "Defender Lost");
	}
}
