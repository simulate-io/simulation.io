#include <iostream>

#include "simulate.io/game/MeleeBattle.h"
#include "simulate.io/game/ICharacter.h"

void MeleeBattle::BeginFight()
{
	int damageAtacker, damageDefender;

	// KE: Simple battle loop untill winner is determine
	while (m_HeroAtacker.GetHealth() > 0 
		&& m_HeroDefender.GetHealth() > 0)
	{
		if (m_HeroAtacker.GetHealth() > 0)
		{
			damageAtacker = m_HeroAtacker.DealDamage();
			m_HeroDefender.GetDamaged(damageAtacker);
		}
		if (m_HeroDefender.GetHealth() > 0)
		{
			damageDefender = m_HeroDefender.DealDamage();
			m_HeroAtacker.GetDamaged(damageDefender);
		}
	}
}

// KE: log results of the battle to std
void MeleeBattle::LogResults()
{
	if(m_HeroAtacker.GetHealth() > 0)
	{
		std::cout << "Atacker Won" << std::endl;
	}
	else
	{
		std::cout << "Atacker Lost" << std::endl;
	}

	if(m_HeroDefender.GetHealth() > 0)
	{
	std::cout << "Defender Won" << std::endl;
	}
	else
	{
		std::cout << "Defender Lost" << std::endl;
	}
}
