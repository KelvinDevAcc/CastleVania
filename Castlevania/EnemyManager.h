#pragma once
#include "BasicEnemy.h" // Include the base enemy class header
#include "Zombie.h"    // Include the Zombie class header (and any other enemy classes you have)

class EnemyManager {
public:
    EnemyManager();
    ~EnemyManager();

    void AddEnemy(BasicEnemy* enemy);
    void Update(float elapsedSec);
    void Draw() const;
    bool HitEnemy(const Rectf& rect);
    size_t Size() const;
    void ClearEnemies();

private:
    std::vector<BasicEnemy*> m_pEnemies;
};
