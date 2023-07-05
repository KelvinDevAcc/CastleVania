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
#include <SoundStream.h>
#include "SoundManager.h"



class Game :public BaseGame
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );



private:
	// DATA MEMBERS
	
	Camera* m_pCamera;
	Player* m_pPlayer;
	Level* m_pLevel;
	UI* m_pUI;
	SoundManager* m_SoundManager;
	StatueManager* m_pStatueManager;
	PowerUpManager* m_pPowerUpManager;
	//SoundStream* m_pSoundstream;
	LevelTransition* m_pLevelTransition;
	

	bool m_CanPress;

	int m_WalkSpeed;

	int m_AudioVolume;

	// FUNCTIONS
	void Initialize( );
	void AddLevelPart1();
	void Cleanup();
	void ClearBackground( ) const;

};