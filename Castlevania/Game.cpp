#include "pch.h"
#include <iostream>
#include "Game.h"
#include "utils.h"

Game::Game(const Window& window)
	:BaseGame{ window },
	m_pCamera{ new Camera{  640.f , 500.f} },
	m_pPlayer{ new Player{10,10,0.15f,2.f,1, Point2f(10,90)} },
	m_pLevel{ new Level{} },
	m_pUI{ new UI{m_pPlayer} },
	m_pSoundManager{ new SoundManager{} },
	m_pStatueManager{ new StatueManager{m_pSoundManager} },
	m_pPowerUpManager{ new PowerUpManager{m_pLevel, m_pPlayer, m_pSoundManager} },
	m_pEnemyManager{new EnemyManager{}},
	m_pLevelTransition{new LevelTransition{m_pLevel, m_pPlayer, m_pStatueManager, m_pPowerUpManager, m_pCamera, m_pSoundManager, m_pEnemyManager, this}},
	m_CanPress{ true },
	m_AudioVolume{ 0 },
	m_OnStairs{false},
	m_WalkSpeed{133},
	m_AllowPlayerInput{true}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize() const
{
	m_pCamera->SetLevelBoundaries(m_pLevel->GetBoundaries());
	SoundStream* soundStream = m_pSoundManager->LoadSoundStream("Sounds/Castlevania_-_NES_-_Vampire_Killer_Background.ogg");
	m_pSoundManager->PlaySoundStream(true);
	AddLevelPart1();
}

void Game::Cleanup() const
{
	delete m_pCamera;
	delete m_pPlayer;
	delete m_pLevel;
	delete m_pLevelTransition;
	delete m_pUI;
	delete m_pSoundManager;
	delete m_pStatueManager;
	delete m_pPowerUpManager;
	delete m_pEnemyManager;
}

void Game::Update(float elapsedSec)
{
	HandleInput();

	m_pPlayer->Update(elapsedSec, m_pLevel);

	// Power ups
	m_pPowerUpManager->Update(elapsedSec);
	m_pStatueManager->Update(elapsedSec);
	m_pUI->Update(elapsedSec);
	m_pLevelTransition->Update(elapsedSec);
	m_pEnemyManager->Update(elapsedSec);

	if (m_pPlayer->m_ActionState == action_state::hitting)
	{
		m_pStatueManager->HitItem(m_pPlayer->m_AtackBox);
		m_pEnemyManager->HitEnemy(m_pPlayer->m_AtackBox);
	}
	if (m_pPowerUpManager->Size() > 0)
	{
		m_pPowerUpManager->HitItem(m_pPlayer->m_PlayerRect);
	}
	if (m_pUI->m_Timer == 0)
	{
		std::cout << "Out of time" << std::endl;
	}

	if (m_OnStairs)
	{
		m_pLevel->HandleStairCollision(m_pPlayer->m_PlayerRect, m_pPlayer->m_Velocity);

		if (m_pLevel->IsOnGround(m_pPlayer->m_PlayerRect))
			m_OnStairs = false;
	}

	m_pLevel->HandelCollision(m_pPlayer->m_PlayerRect, m_pPlayer->m_Velocity);
}

void Game::Draw() const
{
	ClearBackground();
	glPushMatrix();
	{
		m_pCamera->Transform(m_pPlayer->m_PlayerRect);

		m_pLevel->DrawBackground();
		m_pStatueManager->Draw();
		m_pPowerUpManager->Draw();
		m_pEnemyManager->Draw();
		m_pPlayer->Draw();
	}
	glPopMatrix();

	m_pUI->Draw();
	m_pLevelTransition->Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (m_CanPress)
	{
		switch (e.keysym.sym)
		{
		case SDLK_EQUALS:
			IncreaseVolume();
			break;
		case SDLK_MINUS:
			DecreaseVolume();
			break;
		case SDLK_m:
			MuteVolume();
			break;
		case SDLK_LEFT:
			if(m_AllowPlayerInput)
				MovePlayerLeft();
			break;
		case SDLK_RIGHT:
			if (m_AllowPlayerInput)
				MovePlayerRight();
			break;
		case SDLK_UP:
			MoveToStair();
			break;
		case SDLK_DOWN:
			if (m_AllowPlayerInput)
				CrouchPlayer();
			break;
		case SDLK_x:
			if (m_AllowPlayerInput)
				JumpPlayer();
			break;
		case SDLK_l:
			DamagePlayer();
			break;
		case SDLK_z:
			AttackPlayer();
			break;
		case SDLK_i:
			DisplayInstructions();
			break;
		default:
			StopPlayer();
			break;
		}
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	StopPlayer();
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	// Process mouse motion event if needed
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	// Process mouse down event if needed
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	// Process mouse up event if needed
}

void Game::SetAllowPlayerInput(bool allow)
{
	m_AllowPlayerInput = allow;
}

void Game::HandleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			ProcessKeyDownEvent(e.key);
			break;
		case SDL_KEYUP:
			ProcessKeyUpEvent(e.key);
			break;
		case SDL_MOUSEMOTION:
			ProcessMouseMotionEvent(e.motion);
			break;
		case SDL_MOUSEBUTTONDOWN:
			ProcessMouseDownEvent(e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			ProcessMouseUpEvent(e.button);
			break;
		default:
			break;
		}
	}
}

void Game::IncreaseVolume()
{
	m_AudioVolume = (m_AudioVolume != 100) ? m_AudioVolume + 10 : m_AudioVolume;
	m_pSoundManager->SetSoundVolume(m_AudioVolume);
	std::cout << "Volume: " << m_AudioVolume << std::endl;
}

void Game::DecreaseVolume()
{
	m_AudioVolume = (m_AudioVolume != 0) ? m_AudioVolume - 10 : m_AudioVolume;
	m_pSoundManager->SetSoundVolume(m_AudioVolume);
	std::cout << "Volume: " << m_AudioVolume << std::endl;
}

void Game::MuteVolume()
{
	m_AudioVolume = 0;
	m_pSoundManager->SetSoundVolume(m_AudioVolume);
	std::cout << "Audio muted" << std::endl;
}

void Game::MovePlayerLeft()
{
	m_pPlayer->m_ActionState = action_state::moving;
	m_pPlayer->m_Velocity.x = -m_WalkSpeed;
	m_CanPress = false;
}

void Game::MovePlayerRight()
{
	m_pPlayer->m_ActionState = action_state::moving;
	m_pPlayer->m_Velocity.x = m_WalkSpeed;
	m_CanPress = false;
}

void Game::CrouchPlayer() const
{
	m_pPlayer->m_ActionState = action_state::crouching;
}

void Game::JumpPlayer() const
{
	if (m_pLevel->IsOnGround(m_pPlayer->m_PlayerRect))
	{
		m_pPlayer->m_ActionState = action_state::jumping;
		m_pPlayer->m_Velocity.y = 500;
	}
}

void Game::DamagePlayer() const
{
	m_pPlayer->Damage(1);
}

void Game::AttackPlayer()
{
	m_pPlayer->m_ActionState = action_state::hitting;
	m_pPlayer->m_Velocity.x = 0;
	m_CanPress = false;
}

void Game::StopPlayer()
{
	m_pPlayer->m_ActionState = action_state::Idle;
	m_pPlayer->m_Velocity.x = 0;
	m_CanPress = true;
}

void Game::MoveToStair()
{
	if (m_pLevel->IsCollidingWithStair(m_pPlayer->m_PlayerRect))
		m_OnStairs = true;
}

void Game::DisplayInstructions()
{
	std::cout << "PLAY INFO:\n"
		<< "\n"
		<< "WALKING:			ARROW KEYS\n"
		<< "JUMP:				X\n"
		<< "ATTACK:				Z\n"
		<< "-Volume:			-\n"
		<< "+Volume:			=\n"
		<< "MUTE VOLUME:		M\n"
		<< "DAMAGE PLAYER		L\n"
		<< std::endl;
}

void Game::AddLevelPart1() const
{

	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 300, 60 }, Statue::DropType::health, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 500, 60 }, Statue::DropType::wip, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 700, 60 }, Statue::DropType::wip, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 900, 60 }, Statue::DropType::health, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 1100, 60 }, Statue::DropType::throwingKnives, m_pPowerUpManager);

}

void Game::ClearBackground()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}