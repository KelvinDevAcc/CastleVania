#include "pch.h"
#include "LevelTransition.h"
#include <iostream>

LevelTransition::LevelTransition(Level* level, Player* player, StatueManager* statueManager, PowerUpManager* PowerupManager, Camera* camera):
	m_plevel{ level },
	m_pPlayer{player}, 
	m_pPowerUpManager{ PowerupManager },
	m_pStatueManager{statueManager},
	m_pCamera{camera}, 
	m_pSoundStream{ new SoundEffect{"Sounds/TrasitionSound.wav"} }

{
	m_ColiderShape = Rectf(400, 60, 20, 20);
	m_EndColiderShape = Rectf(400, 60, 20, 20);
}

LevelTransition::~LevelTransition()
{
	delete m_pSoundStream;
}
void LevelTransition::Draw()
{
	if (IsOverlapping(m_pPlayer->m_PlayerHitBox, m_ColiderShape))
	{
		Playanimation();
	}
}

void LevelTransition::Update()
{
	switch (m_plevel->m_levelPart)
	{
	case 1:
		m_ColiderShape = Rectf(1350, 60, 20, 70);
		m_EndColiderShape = Rectf(1450, 60, 20, 70);
		break;

	case 2:
		m_ColiderShape = Rectf(1350, -60, 20, 70);
		m_EndColiderShape = Rectf(1450, -60, 20, 70);

		break;
	/*case 3:
		m_ColiderShape = Rectf(1350, 40, 20, 70);
		m_EndColiderShape = Rectf(1450, 40, 20, 70);
		break;
	case 4:
		m_ColiderShape = Rectf(1350, 40, 20, 70);
		m_EndColiderShape = Rectf(1450, 40, 20, 70);
		break;*/
	default:
		break;
	}
	
	if (IsOverlapping(m_pPlayer->m_PlayerHitBox, m_EndColiderShape))
	{
		SwitchOnLevel();
	}

}

void LevelTransition::SwitchOnLevel()
{
	m_pStatueManager->ClearStatueVec();
	m_pPowerUpManager->ClearStatueVec();
	m_pPlayer->m_Shape.left = 10;
	m_pPlayer->m_Shape.bottom = 90;
	m_pPlayer->m_Velocity.x = 0;

	m_plevel->NextlevelPart(m_plevel->m_levelPart);
	switch (m_plevel->m_levelPart)
	{
	case 2:
		AddLevelPart2();
		m_pCamera->SetlevelBoundaries(m_plevel->GetBoundaries());
		break;
	default:
		break;
	}
}

void LevelTransition::Playanimation()
{
	m_pCamera->FadeOut(1.5f);
	m_pPlayer->m_Velocity.x  = 133;
	m_pSoundStream->Play(false);
	
}

bool LevelTransition::IsOverlapping(Rectf player, Rectf hittableObject)
{
	return utils::IsOverlapping(player, hittableObject);
}


void LevelTransition::AddLevelPart2()
{

	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 300, 60 }, Statue::DropType::Healt, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 500, 60 }, Statue::DropType::Wip, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 700, 60 }, Statue::DropType::Wip, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 900, 60 }, Statue::DropType::Healt, m_pPowerUpManager);
	m_pStatueManager->AddItem(10, 20, 0.2f, 2.f, 3, Point2f{ 1100, 60 }, Statue::DropType::Trowingknife, m_pPowerUpManager);

}