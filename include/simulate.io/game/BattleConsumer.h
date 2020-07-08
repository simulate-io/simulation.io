#pragma once

#include "simulate.io/game/BattleTypes.h"

class BattleConsumer
{
public:
    BattleConsumer() = delete;

    //@param BattlePackageTaskVector
    BattleConsumer(BattlePackageTaskVector const& battlesToRun)
    : m_battlesToRun(battlesToRun)
    {}

    // @brief start running battles
    // @params number of threads to run battles
    void RunBattles(int const threadNum);

private:

    // In future we need to ask independently of GameManager how many threads we can run
    // KE: Hard coding to one threads for now
    // TODO: Acquire more threads + mutex protecting
    int m_maxThreadNumber = 1;
    BattlePackageTaskVector const& m_battlesToRun;
};