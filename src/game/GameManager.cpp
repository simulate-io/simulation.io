#include "game/ICharacter.h"
#include "game/MeleeBattle.h"
#include "game/GameManager.h"
#include "game/BattleTypes.h"

#include "utils/log/loguru.hpp"

#include <memory>
#include <vector>

// EK: function to execute a simple battle
// TODO: move as a part of GameManager class that will decide on which function to run

void BattleStarter(std::shared_ptr<IBattle> pBattle)
{
    if(pBattle.get())
    {
        pBattle->BeginFight();
        pBattle->LogResults();
    }
    else
    {
        LOG_F(ERROR, "Error incorrect battle pointer has passed.");
    }
}

void GameManager::Init(std::shared_ptr<std::vector<FightersPair_t>> pFighterPairsVect)
{
    m_pFighterPairsVect = pFighterPairsVect;
}

std::shared_ptr<std::vector<FightersPair_t>> GameManager::GetFighters()
{
    return m_pFighterPairsVect;
}

BattleFuncPtr GameManager::GetBattleFunc()
{
    return &BattleStarter;
}

void GameManager::RunBattles()
{
    m_battleConsumer.RunBattles();
}