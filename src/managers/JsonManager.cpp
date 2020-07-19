#include "managers/JsonManager.h"
#include "utils/log/loguru.hpp"

#include <fstream>
#include <algorithm>
#include <random>


// YM: This needs to be more abstract later due to design
// There should not be functions that reflect the data structure in the json
std::vector<WarriorDummy> JsonManager::ParseAttacker(json jsonData)
{
    json attackers = jsonData["v_battles"]["attackers"];
    std::vector<WarriorDummy> attackersList;

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

    return attackersList;
}

std::vector<WarriorDummy> JsonManager::ParseDefender(json jsonData)
{
    json defenders = jsonData["v_battles"]["defenders"];
    std::vector<WarriorDummy> defendersList;

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

    return defendersList;
}


void JsonManager::ShuffleData(std::vector<WarriorDummy> attacker, std::vector<WarriorDummy> defender)
{
    auto rnd = std::random_device();
    std::shuffle(std::begin(attacker), std::end(attacker), rnd);
    std::shuffle(std::begin(defender), std::end(defender), rnd);

    assert(attacker.size() == defender.size() && "Attackers and Defender list must be the same.");
    const size_t length = defender.size();

    for (int i = 0; i < length; i++)
    {
        WarriorDummy att_random = remove_at_return(attacker, attacker.size() - 1 );
        WarriorDummy def_random = remove_at_return(defender, defender.size() - 1 );

        FightersPair_t pair = FightersPair_t(att_random, def_random);

        mp_parsedData.get()->push_back(pair);
    }
}

void JsonManager::Init(const char* path)
{
    std::ifstream stream(path);
    // checking if file is not empty
    bool isEmpty = stream.peek() == std::ifstream::traits_type::eof();
    if( !isEmpty )
    {
        json main_json = json::parse(stream);

        std::string version = main_json["v_simulate.io"];

        auto data = main_json["v_battles"]["attackers"];
        LOG_F(INFO,"Version: %s" , version.data());

        auto attackersList = ParseAttacker(main_json);
        auto defendersList = ParseDefender(main_json);

        ShuffleData(attackersList, defendersList);
        LOG_F(INFO, "JSON data is parsed.");
    } else {
        LOG_F(ERROR, "JSON file at %s is empty", path );
        assert(isEmpty);
    }
}

Battles_vec_ptr JsonManager::Get()
{
    if(mp_parsedData.get() != nullptr)
    {
        return mp_parsedData;
    }
    return nullptr;
}
