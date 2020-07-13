#include "game/ICharacter.h"
#include "game/WarriorDummy.h"
#include "game/MeleeBattle.h"
#include "game/BattleProducer.h"
#include "game/BattleConsumer.h"
#include "game/GameManager.h"
#include "utils/OsUtils.h"

#include "utils/json.hpp"
#define JSONPATH "./assets/main.json"
#include "utils/string-utils.hpp"
#include "utils/log/loguru.cpp"
#include "utils/filesystem.hpp"
#include "utils/pch.h"

#include <vector>

// namespaces
using json = nlohmann::json;
namespace fs = ghc::filesystem;

int main(int argc, char* argv[])
{
	// YM: Initializing log library
	loguru::init(argc, argv);
	loguru::add_file("simulate.io.txt", loguru::Append, loguru::Verbosity_MAX);
	LOG_F(INFO, "Starting simulate.io");

	// KE: construct all elements here
    BattleProducer producer = BattleProducer();
    BattleConsumer consumer = BattleConsumer();
    GameManager gameManager = GameManager(consumer, producer);

    // TODO: move as a part of SimulationManager
    OsUtils osUtils = OsUtils();

    // TODO: Job this job should done by Json Parser Class
    WarriorDummy attacker;
    WarriorDummy defender;
    FightersPair_t fighterPair(attacker, defender);
    std::vector<FightersPair_t> fighterPairsVect;
    fighterPairsVect.push_back(fighterPair);

    // KE: Initialize elements here
    gameManager.Init(std::make_shared<std::vector<FightersPair_t>>(fighterPairsVect));
    producer.Init(gameManager.GetFighters(), gameManager.GetBattleFunc());
    consumer.Init(std::make_shared<BattlePackageTaskVector>(producer.GetBattleQueue()), osUtils.GetAvailableThreads());

	// KE: Create consumer and run all the battles
    consumer.RunBattles();

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
