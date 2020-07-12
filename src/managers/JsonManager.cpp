#include "managers/JsonManager.h"
#include "utils/json.hpp"
#include "utils/log/loguru.hpp"
#include "game/WarriorDummy.h"
#include <fstream>
#include <algorithm>
#include <random>
using json = nlohmann::json;

JsonManager::JsonManager()
{
}

auto p_Battles = std::make_shared<std::vector<FightersPair_t> >();

Battles_vec_ptr JsonManager::Init(const char* path)
{    std::ifstream stream(path);
     json main_json = json::parse(stream);

    std::string version = main_json["v_simulate.io"];
    LOG_F(INFO,"Version: %s" , version.data());

    auto attackers = main_json["v_battles"]["attacker"];
    auto defenders = main_json["v_battles"]["attacker"];

    std::vector<WarriorDummy> attackersList;
    std::vector<WarriorDummy> defendersList;

    for(const auto& character: attackers)
    {
        attackersList.emplace_back(
            WarriorDummy(
                character["name"],
                character["maxHealth"].get<int>(),
                character["damage"].get<int>()
            )
        );
    }

    for(const auto& character: defenders)
    {
        defendersList.emplace_back(
            WarriorDummy(
                character["name"],
                character["maxHealth"].get<int>(),
                character["damage"].get<int>()
            )
        );
    }

    auto rnd = std::random_device();
    std::shuffle(std::begin(attackersList), std::end(attackersList), rnd);
    std::shuffle(std::begin(defendersList), std::end(defendersList), rnd);

    assert(attackersList.size() == defendersList.size() && "Attackers and Defender list must be the same.");
    const size_t length = attackersList.size();
    for (int i = 0; i < length; i++)
    {
        WarriorDummy att_random = remove_at_return(attackersList, attackersList.size() - 1 );
        WarriorDummy def_random = remove_at_return(defendersList, defendersList.size() - 1 );

        FightersPair_t pair = FightersPair_t(att_random, def_random);

        p_Battles.get()->push_back(pair);
    }

    return p_Battles;
}
