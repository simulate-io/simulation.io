#pragma once

#include "BattleTypes.h"

class BattleConsumer
{
public:

    BattleConsumer() {};

    // @brief Assign the ptr
    // @param BattlePackageTaskVectorPtr
    void Init(std::shared_ptr<BattlePackageTaskVector> battlesToRun);

    // @brief start running battles
    // @params number of threads to run battles
    void RunBattles(unsigned const threadNum);

private:
    std::shared_ptr<BattlePackageTaskVector> m_pBattlesToRun;
};