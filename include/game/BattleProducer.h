#pragma once

#include "ICharacter.h"
#include "IBattle.h"
#include "BattleTypes.h"

#include <vector>

class BattleProducer
{
public:
	BattleProducer() {}

    //@param vector of pair of characters
    //@param function pointer to battle to run
    //TODO: create a proper function pointer type for battleTask
    void Init(std::shared_ptr<std::vector<FightersPair_t>> fighterPairs, BattleFuncPtr battleTask);

	// @brief signal to create work
	void CreateWork_();

	// returns queue with battles to be run
	BattlePackageTaskVector const& GetBattleQueue() const;
private:

    std::shared_ptr<std::vector<FightersPair_t>> m_pFighterPairs;
    BattleTask m_battleTask;

    // KE: cache all created battles
    std::vector<std::shared_ptr<IBattle>> m_savedBattles;
    // KE: battle tasks ready to be run
	BattlePackageTaskVector m_battles;
};