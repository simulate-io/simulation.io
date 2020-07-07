#include <fstream>
#include <iostream>
#include <thread>

// defines
#define JSONPATH "./assets/main.json"

#include "simulate.io/pch.h"
#include "utils/json.hpp"
#include "utils/string-utils.hpp"
#include "utils/log/loguru.cpp"
#include "utils/filesystem.hpp"

#include "simulate.io/game/ICharacter.h"
#include "simulate.io/game/WarriorDummy.h"
#include "simulate.io/game/MeleeBattle.h"

#include "simulate.io/game/BattleProducer.h"

// namespaces
using json = nlohmann::json;

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

using json 	 = nlohmann::json;
namespace fs = ghc::filesystem;

int main(int argc, char* argv[])
{
	// YM: Initializing log library
	loguru::init(argc, argv);
	loguru::add_file("simulate.io.txt", loguru::Append, loguru::Verbosity_MAX);
	LOG_F(INFO, "Starting simulate.io");

    // TODO: move as a part of GameManager class that will decide on which characters to send
    WarriorDummy attacker;
    WarriorDummy defender;
    MeleeBattle battle(std::move(attacker), std::move(defender));
    FightersPair_t fighterPair(attacker, defender);
    std::vector<FightersPair_t> fighterPairsVect;
    fighterPairsVect.emplace_back(fighterPair);

    // Tasks Producer to work on the characters battles to be run
	BattleProducer producer(fighterPairsVect, &BattleStarter);
    producer.CreateWork();
	BattlePackageTaskVector battlesToRun = producer.GetBattleQueue();

	//TODO: move as a part of Battle consumer to run in multiple threads
    std::thread th(std::move(battlesToRun[0].battleTask), battlesToRun[0].pbattle);
	th.join();

	// YM: Importing main.json
    std::error_code error;
    bool bExists = fs::exists(JSONPATH, error);
	assert( bExists && "./assets/main.json not found!");

	std::ifstream stream(JSONPATH);
	json main_json = json::parse(stream);

    std::string version = main_json["v_simulate.io"];

	LOG_F(INFO,"Version: %s" , version.data());

	return 0;
}
