#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "simulate.io/pch.h"
#include "utils/json.hpp"
#include "utils/string-utils.hpp"

// defines
#define JSONPATH "assets\\main.json"

// namespaces
using json = nlohmann::json;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    // YM: Importing main.json
    std::error_code error;
    bool bExists = fs::exists(JSONPATH, error);

    assert(bExists == true && "assets\\main.json not found!");

    std::ifstream stream(JSONPATH);
    json main_json = json::parse(stream);
    std::cout << "Version: " << main_json["v_simulate.io"] << std::endl;
    
    return 0;
}
