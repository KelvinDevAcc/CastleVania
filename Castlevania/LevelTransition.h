#pragma once
#include "Level.h"
#include "Player.h"
#include "StatueManager.h"
#include "PowerUpManager.h"
#include <SoundEffect.h>
#include "SoundManager.h"
#include "EnemyManager.h"
#include "Zombie.h"
#include "Camera.h"
#include <utils.h>

class LevelTransition 
{
public: 
	LevelTransition(Level* Level, Player* player , StatueManager* statueManager, PowerUpManager* PowerupManager , Camera* camera, SoundManager* soundMAnager,EnemyManager* enemymanager );
	~LevelTransition() = default;
	void Update();
	void SwitchOnLevel() const;
	void PlayAnimation() const;
	static bool IsOverlapping(Rectf Player, Rectf hittableObject);

	void AddLevelPart2() const;



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
	EnemyManager* m_pEnemyManager;
};

