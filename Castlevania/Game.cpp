#include "pch.h"
#include <iostream>
#include "Game.h"
#include "utils.h"

Game::Game(const Window& window)
	:BaseGame{ window },
	m_pCamera{ new Camera{  640.f , 500.f} },
	m_pPlayer{ new Player{10,10,0.1f,2.f,1, Point2f(10,90)} },
	m_pLevel{ new Level{} },
	m_pUI{ new UI{m_pPlayer} },
	m_SoundManager{ new SoundManager{} },
	m_pPowerUpManager{ new PowerUpManager{m_pLevel, m_pPlayer, m_SoundManager} },
	m_pStatueManager{ new StatueManager{} },
	//m_pSoundstream{ new SoundStream{"Sounds/Castlevania_-_NES_-_Vampire_Killer_Background.ogg"} },
	m_pLevelTransition{ new LevelTransition{m_pLevel,m_pPlayer, m_pStatueManager, m_pPowerUpManager, m_pCamera} },
	

	m_CanPress{ true },
	m_WalkSpeed{ 133 },
	m_AudioVolume{100}
	
{	 

	Initialize( );
}

Game::~Game( )
{
	Cleanup();
}

void Game::Initialize( )
{
	m_pCamera->SetlevelBoundaries(m_pLevel->GetBoundaries());
	SoundStream* soundStream = m_SoundManager->LoadSoundStream("Sounds/Castlevania_-_NES_-_Vampire_Killer_Background.ogg");
	m_SoundManager->PlaySoundStream(true);
	//m_pSoundstream->Play(true);
	AddLevelPart1();
}

void Game::Cleanup()
{
	delete m_pCamera;
	delete m_pPlayer;
	delete m_pLevel;
	delete m_pLevelTransition;
	//delete m_pSoundstream;
	delete m_pUI;
	delete m_SoundManager;
	delete m_pStatueManager;
	delete m_pPowerUpManager;
}

void Game::Update( float elapsedSec )
{
	m_pPlayer->Update(elapsedSec, m_pLevel);
	
	// Power ups
	m_pPowerUpManager->Update(elapsedSec);
	m_pStatueManager->Update(elapsedSec);
	m_pUI->Update(elapsedSec);
	m_pLevelTransition->Update();

	if(m_pPlayer->m_ActionState == ActionState::hitting)
	{
		m_pStatueManager->HitItem(m_pPlayer->m_Desrect);
	}
	if (m_pPowerUpManager->Size() > 0)
	{
		m_pPowerUpManager->HitItem(m_pPlayer->m_PlayerHitBox);
	}
	if (m_pUI->m_Timer == 0)
	{
		std::cout << "out of time";
	}

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_UP] && m_pLevel->IsonStairs(m_pPlayer->m_Shape))
	{
		m_pLevel->HandelUpCollision(m_pPlayer->m_Shape, m_pPlayer->m_Velocity);

	}
	else
	{
		m_pLevel->HandelCollision(m_pPlayer->m_Shape, m_pPlayer->m_Velocity);
	}
	
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	{
		m_pCamera->Transform(m_pPlayer->m_PlayerHitBox);
		m_pLevel->DrawBackground();
		m_pStatueManager->Draw();
		m_pPowerUpManager->Draw();
		m_pPlayer->Draw();
		m_pUI->Draw(m_pCamera->m_bottomleft);
		m_pLevelTransition->Draw();
	}
	glPopMatrix();

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (m_CanPress)
	{
		switch (e.keysym.sym)
		{
		case SDLK_EQUALS:
			m_AudioVolume = (m_AudioVolume != 100) ? m_AudioVolume + 10 : m_AudioVolume;
			//m_pSoundstream->SetVolume(m_AudioVolume);
			m_SoundManager->SetSoundVolume(m_AudioVolume);
			std::cout << "Volume: " << m_AudioVolume << std::endl;
			break;
		case SDLK_MINUS:
			m_AudioVolume = (m_AudioVolume != 0) ? m_AudioVolume - 10 : m_AudioVolume;
			//m_pSoundstream->SetVolume(m_AudioVolume);
			m_SoundManager->SetSoundVolume(m_AudioVolume);
			std::cout << "Volume: " <<m_AudioVolume << std::endl;
			break;
		case SDLK_m:
			m_AudioVolume = 0;
			//m_pSoundstream->SetVolume(m_AudioVolume);
			m_SoundManager->SetSoundVolume(m_AudioVolume);
			std::cout << "audio muted";
			break;
		
		case SDLK_LEFT:
			m_pPlayer->m_ActionState = ActionState::moving;
			m_pPlayer->m_Velocity.x = -m_WalkSpeed;
			m_CanPress = false;

			break;
		case SDLK_RIGHT:
			m_pPlayer->m_ActionState = ActionState::moving;
			m_pPlayer->m_Velocity.x = m_WalkSpeed;
			m_CanPress = false;
			break;
		case SDLK_DOWN:
			m_pPlayer->m_ActionState = ActionState::chrouching;
			break;
		case SDLK_x:
			if (m_pLevel->IsOnGround(m_pPlayer->m_PlayerHitBox))
			{
				m_pPlayer->m_ActionState = ActionState::jumping;
				m_pPlayer->m_Velocity.y = 500;
				m_CanPress = false;
			}
			break;
		case SDLK_l:
			m_pPlayer->Damage(1);
			break;
	
		case SDLK_z:
			m_pPlayer->m_ActionState = ActionState::hitting;
			m_pPlayer->m_Velocity.x = 0;
			m_CanPress = false;
			break;

		case SDLK_i:
			std::cout << "PLAY INFO:\n" << "\n" << "WALKING:      AROW KEYS\n" << "JUMP:      X\n" <<"ATACK:      Z\n" << "-Volume:      -\n" << "+Volume:      =\n" <<"MUTE VOLUME:      M\n" <<"DAMAGE PLAYER     L" << std::endl;
			break;
		default:
			m_pPlayer->m_ActionState = ActionState::Idle;
			m_pPlayer->m_Velocity.x = 0;
			m_CanPress = false;
			break;
		}
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->m_ActionState = ActionState::Idle;
	m_pPlayer->m_Velocity.x = 0;
	m_CanPress = true;
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}


void Game::AddLevelPart1()
{

	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 300, 60 }, Statue::DropType::Healt, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 500, 60 }, Statue::DropType::Wip, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 700, 60 }, Statue::DropType::Wip, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 900, 60 }, Statue::DropType::Healt, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 2, Point2f{ 1100, 60 }, Statue::DropType::Trowingknife, m_pPowerUpManager);

}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}





