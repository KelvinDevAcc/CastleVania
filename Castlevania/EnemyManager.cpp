#include "pch.h"
#include "EnemyManager.h"



EnemyManager::~EnemyManager() {
    for (const BasicEnemy* enemy : m_pEnemies) {
        delete enemy;
    }
}

void EnemyManager::AddEnemy(BasicEnemy* enemy) {
    m_pEnemies.push_back(enemy);
}

void EnemyManager::Update(float elapsedSec) const
{
    for (BasicEnemy* enemy : m_pEnemies) {
        enemy->Update(elapsedSec);
    }
}

void EnemyManager::Draw() const {
    for (BasicEnemy* enemy : m_pEnemies) {
        enemy->Draw();
    }
}

bool EnemyManager::HitEnemy(const Rectf& rect) {
    for (size_t idx = 0; idx < m_pEnemies.size(); ++idx) {
        if (m_pEnemies[idx]->IsOverlapping(rect)) {
            delete m_pEnemies[idx];
            m_pEnemies[idx] = m_pEnemies.back();
            m_pEnemies.pop_back();
            return true;
        }
    }
    return false;
}

size_t EnemyManager::Size() const {
    return m_pEnemies.size();
}

void EnemyManager::ClearEnemies() {
   
    m_pEnemies.clear();
}
