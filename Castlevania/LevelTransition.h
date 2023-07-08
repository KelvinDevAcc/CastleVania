#pragma once
#include "Level.h"
#include "Player.h"
#include "StatueManager.h"
#include "PowerUpManager.h"
#include <SoundEffect.h>
#include "SoundManager.h"
#include "Camera.h"
#include <utils.h>

class LevelTransition
{
public: 
	LevelTransition(Level* Level, Player* player , StatueManager* statueManager, PowerUpManager* PowerupManager , Camera* camera, SoundManager* soundMAnager);
	~LevelTransition();
	void Draw();
	void Update();
	void SwitchOnLevel();
	void Playanimation();
	bool IsOverlapping(Rectf Player, Rectf hittableObject);

	void AddLevelPart2();



private: 
	Level* m_plevel;
	Player* m_pPlayer;
	Rectf m_ColiderShape;
	Rectf m_EndColiderShape;
	StatueManager* m_pStatueManager;
	PowerUpManager* m_pPowerUpManager;
	Camera* m_pCamera;
	SoundEffect* m_pSoundStream;
	SoundManager* m_SoundManager;
};

