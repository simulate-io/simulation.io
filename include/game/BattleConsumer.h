#pragma once

#include "BattleTypes.h"

class BattleConsumer
{
public:

    BattleConsumer() {};

    // @brief Initialize Consumer
    // @param BattlePackageTaskVectorPtr
    // @params number of threads to run battles
    void Init(std::shared_ptr<BattlePackageTaskVector> battlesToRun, unsigned const threadNum);

    // @brief start running battles
    void RunBattles() const;

private:
    std::shared_ptr<BattlePackageTaskVector> m_pBattlesToRun;
    unsigned int m_threads;
};