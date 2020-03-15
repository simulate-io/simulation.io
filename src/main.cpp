#include <string>
#include <vector>

#include "utils/string-utils.hpp"
#include "simulate.io/pch.h"
#include "simulate.io/game/ICharacter.h"
#include "simulate.io/game/IBattle.h"
#include "simulate.io/game/WarriorDummy.h"
#include "simulate.io/game/MeleeBattle.h"

int main(int argc, char* argv[]) {

	WarriorDummy atacker;
	WarriorDummy defender;
	MeleeBattle battle(std::move(atacker), std::move(defender));

	battle.BeginFight();
	battle.LogResults();

	return 0;
}
