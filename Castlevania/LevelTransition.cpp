#include "pch.h"
#include "LevelTransition.h"
#include <utils.h>
#include <iostream>
#include "Game.h"

LevelTransition::LevelTransition(Level* level, Player* player, StatueManager* statueManager,
                                 PowerUpManager* powerUpManager, Camera* camera, SoundManager* soundManager,
                                 EnemyManager* enemyManager, Game* game) :
	m_TransitionState(false),
	m_plevel{level},
	m_pPlayer{player},
	m_pGame{game},
	m_pStatueManager{statueManager},
	m_pPowerUpManager{powerUpManager},
	m_pCamera{camera},
	m_SoundManager{soundManager},
	m_pEnemyManager{enemyManager}
{
	m_LevelTransitionColliders.emplace_back(1350, 60, 20, 70);
	m_LevelTransitionColliders.emplace_back(2952, 223, 20, 70);
	m_LevelTransitionColliders.emplace_back(87, 60, 20, 70);
	m_LevelTransitionColliders.emplace_back(975, 300, 20, 70);


	m_LevelTransitionColliders.emplace_back(2972, 223, 20, 70);
	m_LevelTransitionColliders.emplace_back(2972, 223, 20, 70);


	m_pSoundStream = m_SoundManager->LoadSoundEffect("Sounds/DestroyStatic.wav");
}


void LevelTransition::Draw() const
{
	if (m_LevelTransitionColliders.size() - 1 < m_plevel->m_CurrentLevelPart)
	{
		std::cout << "Level Collider Not Setup" << std::endl;
		return;
	}

	/*utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawRect(m_LevelTransitionColliders[m_plevel->m_CurrentLevelPart]);*/

	utils::SetColor(Color4f{ 0,0,1,1 });

	if (m_TransitionState == 0)
		utils::SetColor(Color4f{ 0, 0, 0, 0});
	else if(m_TransitionState == 1)
		utils::SetColor(Color4f{ 0, 0, 0, m_TransitionTimer / m_TransitionFadeOutTime });
	else if (m_TransitionState == 2)
		utils::SetColor(Color4f{ 0, 0, 0, 1});
	if (m_TransitionState == 3)
		utils::SetColor(Color4f{ 0, 0, 0, 1.0f - (m_TransitionTimer / m_TransitionFadeInTime) });


	utils::FillRect(0, 0, m_pGame->GetViewPort().width, m_pGame->GetViewPort().height);

}

void LevelTransition::Update(float elapsedSec)
{
	if (m_LevelTransitionColliders.size() - 1 < m_plevel->m_CurrentLevelPart)
	{
		std::cout << "Level Collider Not Setup" << std::endl;
		return;
	}

	if (m_TransitionState == 0)
	{
		// Check for level switch trigger
		if (IsOverlapping(m_pPlayer->m_PlayerRect, m_LevelTransitionColliders[m_plevel->m_CurrentLevelPart]))
		{
			m_TransitionTimer = 0.0f;
			m_TransitionState = 1;
			m_pGame->SetAllowPlayerInput(false);
		}
	}
	else if(m_TransitionState == 1)
	{
		// Move player and dip to black

		m_TransitionTimer += elapsedSec;

		m_pPlayer->m_Velocity.x = 80;
		m_pPlayer->m_ActionState = action_state::moving;

		if(m_TransitionTimer > m_TransitionFadeOutTime)
		{
			SwitchOnLevel();
			m_TransitionState = 2;
			m_TransitionTimer = 0.0f;
			m_pPlayer->m_ActionState = action_state::Idle;
		}
	}
	else if (m_TransitionState == 2)
	{
		// Wait for player to settle
		m_TransitionTimer += elapsedSec;

		if (m_TransitionTimer > m_TransitionPauseTime)
		{
			m_pGame->SetAllowPlayerInput(true);
			m_TransitionTimer = 0.0f;
			m_TransitionState = 3;
		}
	}
	else if (m_TransitionState == 3)
	{
		// Fade in

		m_TransitionTimer += elapsedSec;

		if (m_TransitionTimer > m_TransitionFadeInTime)
			m_TransitionState = 0;
	}


}

void LevelTransition::SwitchOnLevel() const
{
	m_pStatueManager->ClearStatueVec();
	m_pPowerUpManager->ClearStatueVec();

	m_plevel->LoadLevel(m_plevel->m_CurrentLevelPart + 1);

	switch (m_plevel->m_CurrentLevelPart)
	{
	case 1:
		AddLevelPart2();
		m_pCamera->SetLevelBoundaries(m_plevel->GetBoundaries());
		m_SoundManager->PlaySoundEffect(m_pSoundStream, false);
		m_pPlayer->m_PlayerRect.left = 10;
		m_pPlayer->m_PlayerRect.bottom = 90;
		m_pPlayer->m_Velocity.x = 0;
		break;
	case 2:
		//AddLevelPart3();
		m_pCamera->SetLevelBoundaries(m_plevel->GetBoundaries());
		m_SoundManager->PlaySoundEffect(m_pSoundStream, false);
		m_pPlayer->m_PlayerRect.left = 20;
		m_pPlayer->m_PlayerRect.bottom = 300;
		m_pPlayer->m_Velocity.x = 0;
		break;
	default:
		break;
	}
}



bool LevelTransition::IsOverlapping(Rectf player, Rectf hittableObject)
{
	return utils::IsOverlapping(player, hittableObject);
}


void LevelTransition::AddLevelPart2() const
{
	m_pEnemyManager->AddEnemy(new Zombie(10, 20, 0.5f, 2.f, 1, Point2f(170, 30), false, m_pPlayer));
	m_pEnemyManager->AddEnemy(new Zombie(10, 20, 0.5f, 2.f, 1, Point2f(200, 30), false, m_pPlayer));
	m_pEnemyManager->AddEnemy(new Zombie(10, 20, 0.5f, 2.f, 1, Point2f(230, 30), false, m_pPlayer));

	m_pEnemyManager->AddEnemy(new Zombie(10, 20, 0.5f, 2.f, 1, Point2f(900, 30), false, m_pPlayer));
	m_pEnemyManager->AddEnemy(new Zombie(10, 20, 0.5f, 2.f, 1, Point2f(930, 30), false, m_pPlayer));
	m_pEnemyManager->AddEnemy(new Zombie(10, 20, 0.5f, 2.f, 1, Point2f(960, 30), false, m_pPlayer));



	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 300, 60 }, Statue::DropType::health, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 500, 60 }, Statue::DropType::throwingKnives, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 700, 60 }, Statue::DropType::health, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 900, 60 }, Statue::DropType::health, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 1100, 60 }, Statue::DropType::throwingKnives, m_pPowerUpManager);
}
