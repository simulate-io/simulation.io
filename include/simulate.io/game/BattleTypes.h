#pragma once

#include "simulate.io/game/ICharacter.h"
#include "simulate.io/game/IBattle.h"

#include <future>
#include <vector>

typedef std::packaged_task<void(std::shared_ptr<IBattle>)> BattleTask;

struct BattlePackageTask_t
{
    BattleTask& battleTask;
    std::shared_ptr<IBattle> pbattle;

    BattlePackageTask_t(BattleTask& tsk, std::shared_ptr<IBattle> btl)
            : battleTask(tsk)
            , pbattle(btl) {};
};

typedef std::vector<BattlePackageTask_t> BattlePackageTaskVector;
