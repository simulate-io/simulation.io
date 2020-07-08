#include "simulate.io/game/BattleConsumer.h"

#include "utils/log/loguru.hpp"

#include <thread>

void BattleConsumer::RunBattles(int const threadNum)
{
    // KE: Do not allow more threads that Consumer has committed for
    const int k_threadCounter = (threadNum > m_maxThreadNumber) ? m_maxThreadNumber : threadNum;
    LOG_F(INFO, "Running battles in %d Threads", k_threadCounter);

    int availableThreadCounter = k_threadCounter;

    for(auto const& battle : m_battlesToRun)
    {
        if(availableThreadCounter)
        {
            LOG_F(INFO, "Starting a new Battle Task");
            //TODO: that will work for now since it is only 1 thread but
            // we must do proper protection first to run multiple battles concurrently
            // optimize to not create thread every time but reuse that already waiting
            availableThreadCounter--;
            std::thread th(std::move(battle.battleTask), battle.pbattle);
            th.join();
            availableThreadCounter++;
            LOG_F(INFO, "Finished battle task");
        }
    }
    LOG_F(INFO, "Done running all battles");
}