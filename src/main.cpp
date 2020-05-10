#include <fstream>
#include <iostream>

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

// namespaces
using json 	 = nlohmann::json;
namespace fs = ghc::filesystem;

int main(int argc, char* argv[]) {

	// YM: Initializing log library
	loguru::init(argc, argv);
	loguru::add_file("simulate.io.txt", loguru::Append, loguru::Verbosity_MAX);
	LOG_F(INFO, "Starting simulate.io");

	WarriorDummy attacker;
	WarriorDummy defender;
	MeleeBattle battle(std::move(attacker), std::move(defender));

	battle.BeginFight();
	battle.LogResults();

	// YM: Importing main.json
	std::error_code error;
	bool bExists = fs::exists(JSONPATH, error);

	assert( bExists && "./assets/main.json not found!");

	std::ifstream stream(JSONPATH);
	json main_json = json::parse(stream);

    std::string version = main_json["v_simulate.io"];

	LOG_F(INFO,"Version:%s" , version.data());

	return 0;
}
