#include "game/BattleProducer.h"
#include "game/BattleConsumer.h"

#include "utils/log/loguru.hpp"

class GameManager
{
public:
    GameManager(BattleConsumer const& battleConsumer,
                BattleProducer const& battleProducer)
    : m_battleConsumer(battleConsumer)
    , m_battleProducer(battleProducer)
    {}

    void Init(std::shared_ptr<std::vector<FightersPair_t>> pFighterPairsVect);

    std::shared_ptr<std::vector<FightersPair_t>> GetFighters();

    BattleFuncPtr GetBattleFunc();

    void RunBattles();

private:
    BattleConsumer const& m_battleConsumer;
    BattleProducer const& m_battleProducer;

    std::shared_ptr<std::vector<FightersPair_t>> m_pFighterPairsVect;
};