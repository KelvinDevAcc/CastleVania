#include "pch.h"
#include "StatueManager.h"
#include <iostream>

StatueManager::StatueManager(SoundManager* soundmanager):
	m_SoundManager{soundmanager}
{
	m_pItems = std::vector<Statue*>{};
	m_pDestroySoundEffect = m_SoundManager->LoadSoundEffect("Sounds/DestroyStatic.wav");

}

StatueManager::~StatueManager()
{
	for (Statue* pUp : m_pItems)
	{
		delete pUp;
	}
}

Statue* StatueManager::AddItem(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, Statue::DropType type, PowerUpManager* PowerUpManager)
{
	Statue* pStatue = new Statue(rows, coloms, framesec, scale, startrow, bottomleft, type, PowerUpManager);
	m_pItems.push_back(pStatue);
	return pStatue;
}

void StatueManager::Update(float elapsedSec) {
	for (Statue* pUp : m_pItems) {
		pUp->Update(elapsedSec);
	}
}

void StatueManager::Draw() const
{
	for (Statue* pUp : m_pItems) {
		pUp->Draw();
	}
}
void StatueManager::ClearStatueVec()
{
	m_pItems.clear();
}

bool StatueManager::HitItem(const Rectf& rect)
{
	int foundIdx = -1;
	for (int idx = 0; idx < Size(); idx++)
	{
		if (m_pItems[idx]->IsOverlapping(rect))
		{
			foundIdx = idx;
			m_pItems[idx]->DropItem();
			m_SoundManager->PlaySoundEffect(m_pDestroySoundEffect, false);
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

size_t StatueManager::Size() const
{
	return m_pItems.size();
}