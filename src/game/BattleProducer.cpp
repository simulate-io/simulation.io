#include "game/ICharacter.h"
#include "game/BattleProducer.h"
#include "game/IBattle.h"
#include "game/MeleeBattle.h"
#include "game/BattleTypes.h"

#include "utils/log/loguru.hpp"

void BattleProducer::Init(std::shared_ptr<std::vector<FightersPair_t>> pFighterPairs, BattleFuncPtr battleTask)
{
    m_pFighterPairs = pFighterPairs;
    m_battleTask = BattleTask(battleTask);
    CreateWork_();
}

void BattleProducer::CreateWork_()
{
    if(!m_pFighterPairs.get())
    {
        LOG_F(ERROR, "Error could not create work, no data provided.");
        return;
    }

    for (auto const& fighterPair : *m_pFighterPairs)
    {
        // construct a battle object
        MeleeBattle battle(std::move(fighterPair.first), std::move(fighterPair.second));

        // create and cache existing battle within Producer
        std::shared_ptr<IBattle> pBattle = std::make_shared<MeleeBattle>(battle);
        m_savedBattles.push_back(pBattle);

        // bundle task and package together and cache it
        BattlePackageTask_t package(m_battleTask, pBattle);
        m_battles.push_back(package);
    }
}

BattlePackageTaskVector const& BattleProducer::GetBattleQueue() const
{
	return m_battles;
}