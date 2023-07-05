  #include "pch.h"
#include "PowerUpManager.h"
#include <iostream>

PowerUpManager::PowerUpManager(Level* level, Player* player, SoundManager* soundManager):
	m_level{level},
	m_player{player},
	m_SoundManager{soundManager},
	m_PickUpSoundEffect{ nullptr }
{
	m_pItems = std::vector<PowerUp*>{};
	m_PickUpSoundEffect = m_SoundManager->LoadSoundEffect("Sounds/PowerupSound.wav");

}

PowerUpManager::~PowerUpManager() 
{
	for (PowerUp* pUp : m_pItems)
	{
		delete pUp;
	}
}

PowerUp* PowerUpManager::AddItem(int rows, int coloms, float scale, int startrow, Point2f bottomleft, PowerUp::Type Type)
{
	PowerUp* pPowerUp =  new PowerUp(m_level, rows, coloms, scale, startrow, bottomleft,Type );
	m_pItems.push_back(pPowerUp);
	return pPowerUp;
}

void PowerUpManager::Update(float elapsedSec) {
	for (PowerUp* pUp : m_pItems) {
		pUp->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{   
	for (PowerUp* pUp : m_pItems) {
		pUp->Draw();
	}
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	int foundIdx = -1;
	for (int idx = 0; idx < Size(); idx++)
	{
		if (m_pItems[idx]->IsOverlapping(rect))
		{
			foundIdx = idx;
			m_SoundManager->PlaySoundEffect(m_PickUpSoundEffect, false);
			if (m_pItems[idx]->GetType() == PowerUp::Type::Health)
			{
				m_player->m_playerHarts = m_player->m_playerHarts + 1;
			}
		}
	}
	if (foundIdx >= 0)
	{
		delete m_pItems[foundIdx];
		m_pItems[foundIdx] = m_pItems[Size() - 1];
		m_pItems.pop_back();
		return true;
	}
	return false;
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

void PowerUpManager::ClearStatueVec()
{
	m_pItems.clear();
}