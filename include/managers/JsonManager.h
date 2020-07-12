#include "game/MeleeBattle.h"
#include "game/ICharacter.h"

#include "utils/noncopyable.h"
#include <vector>

using Battles_vec_ptr = std::shared_ptr<std::vector<FightersPair_t>>;

class JsonManager: public Noncopyable {

public:
    JsonManager();

    Battles_vec_ptr Init(const char* path);
private:
    ~JsonManager() {};

    // @brief Getting a random element from a vector and removing it.
    // @param std::vector<templated> and size_type
    template<typename T>
    T remove_at_return(std::vector<T> &v, typename std::vector<T>::size_type n);
};

template<typename T>
inline T JsonManager::remove_at_return(std::vector<T>& v, typename std::vector<T>::size_type n)
{
    T item = std::move_if_noexcept(v[n]);
    v[n] = std::move_if_noexcept(v.back());
    v.pop_back();
    return item;
}
