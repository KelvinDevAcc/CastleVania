#pragma once
#include "Statue.h"
#include <vector>
#include <SoundEffect.h>
#include "SoundManager.h"
#include "structs.h"


class StatueManager final
{
public:
	StatueManager(SoundManager* soundManager);
	~StatueManager();
	StatueManager(const StatueManager&) = delete;
	StatueManager& operator=(const StatueManager&) = delete;
	StatueManager(StatueManager&&) = delete;
	StatueManager& operator=(StatueManager&&) = delete;

	void AddItem(int rows, int column, float frameSec, float scale, int startRow, Point2f bottomLeft, Statue::DropType type, PowerUpManager* PowerUpManager);
	void Update(float elapsedSec) const;
	void Draw() const;
	void ClearStatueVec();
	size_t Size() const;
	bool HitItem(const Rectf& rect);

private:
	std::vector<Statue*> m_pItems;
	SoundManager* m_SoundManager;
	SoundEffect* m_pDestroySoundEffect;
};

