#include <fstream>
#include <iostream>
//#include <filesystem>
#include <thread>

// defines
#define JSONPATH "assets\\main.json"

#include "simulate.io/pch.h"
#include "utils/json.hpp"
#include "utils/string-utils.hpp"

#include "simulate.io/game/ICharacter.h"
#include "simulate.io/game/IBattle.h"
#include "simulate.io/game/WarriorDummy.h"
#include "simulate.io/game/MeleeBattle.h"

#include "simulate.io/game/BattleProducer.h"

// namespaces
using json = nlohmann::json;
//namespace fs = std::filesystem;

// EK: function to execute a simple battle
// TODO: move as a part of GameManager class that will decide on which function to run
void BattleStarter(std::shared_ptr<IBattle> pBattle)
{
    if(pBattle.get())
    {
        pBattle->BeginFight();
        pBattle->LogResults();
    } else {
        printf("Error incorrect battle pointer has passed.");
    }
}

int main(int argc, char* argv[])
{
    //TODO: move as a part of GameManager class that will decide on which characters to send
    WarriorDummy attacker = WarriorDummy();
    WarriorDummy defender = WarriorDummy();
    FightersPair_t fighterPair(attacker, defender);
    std::vector<FightersPair_t> fighterPairsVect;
    fighterPairsVect.emplace_back(fighterPair);

    //Tasks Producer to work on the characters battles to be run
	BattleProducer producer(fighterPairsVect, &BattleStarter);
    producer.CreateWork();
	BattlePackageTaskVector battlesToRun = producer.GetBattleQueue();

	//TODO: move as a part of Battle consumer to run in multiple threads
    std::thread th(std::move(battlesToRun[0].battleTask), battlesToRun[0].pbattle);
	th.join();

	// YM: Importing main.json
	std::error_code error;
	//bool bExists = fs::exists(JSONPATH, error);

	//assert(bExists == true && "assets\\main.json not found!");

	//std::ifstream stream(JSONPATH);
	//json main_json = json::parse(stream);
	//std::cout << "Version: " << main_json["v_simulate.io"] << std::endl;

	return 0;
}
