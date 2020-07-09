#pragma once

#include "BattleTypes.h"

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
    void RunBattles(unsigned const threadNum);

private:
    BattlePackageTaskVector const& m_battlesToRun;
};