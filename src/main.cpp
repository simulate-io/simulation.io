#include <fstream>
#include <iostream>
#include <filesystem>

// defines
#define JSONPATH "assets\\main.json"

#include "simulate.io/pch.h"
#include "utils/json.hpp"
#include "utils/string-utils.hpp"

#include "simulate.io/game/ICharacter.h"
#include "simulate.io/game/IBattle.h"
#include "simulate.io/game/WarriorDummy.h"
#include "simulate.io/game/MeleeBattle.h"

// namespaces
using json = nlohmann::json;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

	WarriorDummy atacker;
	WarriorDummy defender;
	MeleeBattle battle(std::move(atacker), std::move(defender));

	battle.BeginFight();
	battle.LogResults();

	// YM: Importing main.json
	std::error_code error;
	bool bExists = fs::exists(JSONPATH, error);

	assert(bExists == true && "assets\\main.json not found!");

	std::ifstream stream(JSONPATH);
	json main_json = json::parse(stream);
	std::cout << "Version: " << main_json["v_simulate.io"] << std::endl;

	return 0;
}
