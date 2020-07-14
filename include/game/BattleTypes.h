#pragma once

#include "ICharacter.h"
#include "IBattle.h"

#include <future>
#include <memory>
#include <vector>

typedef std::packaged_task<void(std::shared_ptr<IBattle>)> BattleTask;

struct BattlePackageTask_t
{
    BattleTask& battleTask;
    std::shared_ptr<IBattle> pBattle;

    BattlePackageTask_t(BattleTask& tsk, std::shared_ptr<IBattle> btl)
            : battleTask(tsk)
            , pBattle(btl) {};
};

typedef std::vector<BattlePackageTask_t> BattlePackageTaskVector;

typedef void (*BattleFuncPtr)(std::shared_ptr<IBattle>);
