#pragma once

#include "ICharacter.h"
#include "IBattle.h"
#include "BattleTypes.h"

#include <vector>

class BattleProducer
{
public:
    BattleProducer() = delete;

    //@param vector of pair of characters
    //@param function pointer to battle to run
    //TODO: create a proper function pointer type for battleTask
	BattleProducer(std::vector<FightersPair_t> fighterPairs, void (*battleTask)(std::shared_ptr<IBattle>))
	: m_fighterPairs(fighterPairs)
    {
        m_battleTask = BattleTask(battleTask);
    }

	// signal to create work
	void CreateWork();

	// returns queue with battles to be run
	BattlePackageTaskVector GetBattleQueue() const;
private:

    std::vector<FightersPair_t> m_fighterPairs;
    BattleTask m_battleTask;

    // KE: cache all created battles
    std::vector<std::shared_ptr<IBattle>> m_savedBattles;
    // KE: battle tasks ready to be run
	BattlePackageTaskVector m_battles;
};
