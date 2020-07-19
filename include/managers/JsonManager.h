#include "game/MeleeBattle.h"
#include "game/ICharacter.h"
#include "game/WarriorDummy.h"

#include "utils/json.hpp"
#include "utils/noncopyable.h"

#include <vector>
#include <memory>

using json = nlohmann::json;
using Battles_vec_ptr = std::shared_ptr<std::vector<FightersPair_t>>;

class JsonManager: public Noncopyable {

public:
    JsonManager() {};
    
    ~JsonManager() {};
    
    void Init(const char* path);
    
    Battles_vec_ptr Get();
private:
    
    // @brief Getting a random element from a vector and removing it.
    // @param std::vector<templated> and size_type
    template<typename T>
    T remove_at_return(std::vector<T> &v, typename std::vector<T>::size_type n);

    std::vector<WarriorDummy> ParseAttacker(json jsonData);
    std::vector<WarriorDummy> ParseDefender(json jsonData);
    void ShuffleData(std::vector<WarriorDummy> attacker, std::vector<WarriorDummy> defender);

private:
    Battles_vec_ptr mp_parsedData = std::make_shared<std::vector<FightersPair_t>>();
};

template<typename T>
inline T JsonManager::remove_at_return(std::vector<T>& v, typename std::vector<T>::size_type n)
{
    T item = std::move_if_noexcept(v[n]);
    v[n] = std::move_if_noexcept(v.back());
    v.pop_back();
    return item;
}
