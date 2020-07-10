#include "game/BattleConsumer.h"

#include "utils/log/loguru.hpp"

#include <thread>


void BattleConsumer::Init(std::shared_ptr<BattlePackageTaskVector> battlesToRun)
{
    // KE: if we did not pass any battles then we wasting time
    assert(battlesToRun.get());

    if(m_pBattlesToRun.get())
    {
        LOG_F(ERROR, "BattleConsumer already initialized!");
    }
    else
    {
        m_pBattlesToRun = battlesToRun;
    }
}

void BattleConsumer::RunBattles(unsigned const threadNum)
{
    // KE: Do not allow more threads that Consumer has committed for
    const int k_threadCounter = (threadNum > 0) ? threadNum : 1;
    LOG_F(INFO, "Running battles in %d Threads", k_threadCounter);

    int availableThreadCounter = k_threadCounter;

    // KE: if battle to run has not been assigned
    assert(m_pBattlesToRun.get());
    for(auto const& battle : *m_pBattlesToRun.get())
    {
        if(availableThreadCounter)
        {
            LOG_F(INFO, "Starting a new Battle Task");
            //TODO: that will work for now since it is only 1 thread but
            // we must do proper protection first to run multiple battles concurrently
            // optimize to not create thread every time but reuse that already waiting
            availableThreadCounter--;
            std::thread th(std::move(battle.battleTask), battle.pBattle);
            th.join();
            availableThreadCounter++;
            LOG_F(INFO, "Finished battle task");
        }
    }
    LOG_F(INFO, "Done running all battles");
}