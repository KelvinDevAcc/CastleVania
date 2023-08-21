#pragma once

#include "BaseGame.h"
#include "Vector2f.h"
#include "Player.h"
#include "Camera.h"
#include "StatueManager.h"
#include "PowerUpManager.h"
#include "UI.h"
#include "Level.h"
#include "LevelTransition.h"
#include "SoundStream.h"
#include "SoundManager.h"
#include "EnemyManager.h"

class Game : public BaseGame
{
public:
	explicit Game(const Window& window);
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// Data members
	Camera* m_pCamera;
	Player* m_pPlayer;
	Level* m_pLevel;
	UI* m_pUI;
	SoundManager* m_pSoundManager;
	StatueManager* m_pStatueManager;
	PowerUpManager* m_pPowerUpManager;
	EnemyManager* m_pEnemyManager;
	LevelTransition* m_pLevelTransition;

	bool m_CanPress;
	int m_WalkSpeed;
	int m_AudioVolume;

	// Private functions
	void Initialize() const;
	void AddLevelPart1() const;
	void Cleanup() const;
	static void ClearBackground();

	// Input handling functions
	void HandleInput();
	void IncreaseVolume();
	void DecreaseVolume();
	void MuteVolume();
	void MovePlayerLeft();
	void MovePlayerRight();
	void CrouchPlayer() const;
	void JumpPlayer();
	void DamagePlayer() const;
	void AttackPlayer();
	void StopPlayer();
	static void DisplayInstructions();
};