#include "game/BattleProducer.h"
#include "game/BattleConsumer.h"

class GameManager
{
public:
    GameManager(BattleConsumer const& battleConsumer,
                BattleProducer const& battleProducer)
    : m_battleConsumer(battleConsumer)
    , m_battleProducer(battleProducer)
    {}

private:
    BattleConsumer const& m_battleConsumer;
    BattleProducer const& m_battleProducer;
};