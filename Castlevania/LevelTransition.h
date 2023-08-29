#pragma once
#include <SoundEffect.h>
#include "Level.h"
#include "Player.h"
#include "StatueManager.h"
#include "PowerUpManager.h"
#include "SoundManager.h"
#include "EnemyManager.h"
#include "Camera.h"

class Game;

class LevelTransition final
{
public:

	LevelTransition(Level* Level, Player* player , StatueManager* statueManager, PowerUpManager* powerUpManager , Camera* camera, SoundManager* soundMAnager,EnemyManager* enemyManager,Game* game);
	~LevelTransition() = default;

	void Draw() const;
	void Update(float elapsedSec);
	void SwitchOnLevel() const;

	static bool IsOverlapping(Rectf Player, Rectf hittableObject);

	void AddLevelPart2() const;


	float m_TransitionFadeOutTime{2.0f};
	float m_TransitionPauseTime{0.5f};
	float m_TransitionFadeInTime{1.0f};
	float m_TransitionTimer{};
	int m_TransitionState;


private: 
	Level* m_plevel;
	Player* m_pPlayer;
	Game* m_pGame;
	std::vector<Rectf> m_LevelTransitionColliders;
	StatueManager* m_pStatueManager;
	PowerUpManager* m_pPowerUpManager;
	Camera* m_pCamera;
	SoundEffect* m_pSoundStream;
	SoundManager* m_SoundManager;
	EnemyManager* m_pEnemyManager;
};

