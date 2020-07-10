#include "game/ICharacter.h"
#include "game/BattleProducer.h"
#include "game/IBattle.h"
#include "game/MeleeBattle.h"
#include "game/BattleTypes.h"

void BattleProducer::CreateWork()
{
    for (auto const& fighterPair : m_fighterPairs)
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

void BattleProducer::Init(std::vector<FightersPair_t>&& fighterPairs, void (*battleTask)(std::shared_ptr<IBattle>))
{
    m_fighterPairs = fighterPairs;
    m_battleTask = BattleTask(battleTask);
}

BattlePackageTaskVector const& BattleProducer::GetBattleQueue() const
{
	return m_battles;
}