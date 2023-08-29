#include "pch.h"
#include "UI.h"
#include <utils.h>
#include <iostream>

UI::UI(Player* player):
	m_pScoreTexture{new Texture{"SCORE-0000", "Fonts/RetroGaming.ttf", 100, Color4f(1, 1, 1, 1)}},
	m_pPlayerTexture{new Texture{"PLAYER", "Fonts/RetroGaming.ttf", 500, Color4f(1, 1, 1, 1)}},
	m_pEnemyTexture{new Texture{"ENEMY", "Fonts/RetroGaming.ttf", 500, Color4f(1, 1, 1, 1)}},
	m_pTimerTexture{new Texture{"TIME 0000", "Fonts/RetroGaming.ttf", 500, Color4f(1, 1, 1, 1)}},
	m_pStageTexture{new Texture{"STAGE 01", "Fonts/RetroGaming.ttf", 500, Color4f(1, 1, 1, 1)}},
	m_pHartsCounter{new Texture{"- 05", "Fonts/RetroGaming.ttf", 500, Color4f(1, 1, 1, 1)}},
	m_plivesCounter{new Texture{"P- 03", "Fonts/RetroGaming.ttf", 500, Color4f(1, 1, 1, 1)}},
	m_pHartTexture{new Texture{"Images/PickUps.png"}},


	m_player{player},
	m_LiveCounter{0},
	m_BoxItemType{}

{
	m_Timer = 300.001;
	m_OldScore = 0000;
	m_NewScore = 0000;
	m_LiveCounter = 05;
	m_playerHealt = m_player->m_playerHealth;
	m_HartsCounter = m_player->m_playerHarts;
	m_LiveCounter = m_player->m_playerLives;
	m_HealthBarWidth = 10;
	m_HealthBarHeight = 20;
	m_RectSpacing = 5;
	m_PlayerBarRectX = 40;
	m_PlayerBarRectY = 425;
	m_EnemyHealt = 10;
	m_EnemyBarRectY = 395;
}

UI::~UI()
{
	delete m_pScoreTexture;
	delete m_pPlayerTexture;
	delete m_pEnemyTexture;
	delete m_pTimerTexture;
	delete m_pStageTexture;
	delete m_pHartsCounter;
	delete m_plivesCounter;
	delete m_pHartTexture;
}
void UI::Update(float elapsedSec)
{
	m_playerHealt = m_player->m_playerHealth;

	m_Timer -= elapsedSec;

	const std::string TimerText("TIME " + std::to_string(int(std::round(m_Timer))));

	delete m_pTimerTexture;
	m_pTimerTexture = new Texture{ TimerText,"Fonts/RetroGaming.ttf",500,Color4f(1,1,1,1) };


	if (m_HartsCounter < m_player->m_playerHarts)
	{
		const std::string hartText("- 0" + std::to_string(m_player->m_playerHarts));


		delete m_pHartsCounter;
		m_pHartsCounter = new Texture{ hartText,"Fonts/RetroGaming.ttf",100,Color4f(1,1,1,1) };

		m_HartsCounter = m_player->m_playerHarts;
	}

	if (m_LiveCounter > m_player->m_playerLives)
	{
		const std::string livesText("P- 0" + std::to_string(m_player->m_playerLives));

		delete m_plivesCounter;
		m_plivesCounter = new Texture{ livesText,"Fonts/RetroGaming.ttf",100,Color4f(1,1,1,1) };

		m_LiveCounter = m_player->m_playerLives;
	}

	if (m_OldScore < m_NewScore)
	{
		m_pScoreTexture->~Texture();

		const std::string ScoreText("Score-" + std::to_string(m_NewScore));

		delete m_pScoreTexture;
		m_pScoreTexture = new Texture{ ScoreText,"Fonts/RetroGaming.ttf",100,Color4f(1,1,1,1) };

		m_OldScore = m_NewScore;
	}


}

void UI::Draw()
{

	GetValues();
	const Rectf destRectScoreTex{ 10,450,200,30 };
	m_pScoreTexture->Draw(destRectScoreTex);

	const Rectf destRectPlayerTex{ 10,425,100,30 };
	m_pPlayerTexture->Draw(destRectPlayerTex);

	const Rectf destRectEnemyTex{ 10,395,100,30 };
	m_pEnemyTexture->Draw(destRectEnemyTex);

	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::DrawRect(Point2f(300, 395), 80, 40, 5.f);

	const Rectf destRectTimerTex{ 230,450,200,30 };
	m_pTimerTexture->Draw(destRectTimerTex);

	const Rectf destRectStageTex{ 470,450,100,30 };
	m_pStageTexture->Draw(destRectStageTex);

	const Rectf destRectHartCounterTex{ 470,420,100,30 };
	m_pHartsCounter->Draw(destRectHartCounterTex);

	const Rectf destRectHartTexture{ 420,420,100,200 };
	const Rectf srcRectHartTexture{ m_pHartTexture->GetWidth() / 20, m_pHartTexture->GetHeight() / 10,m_pHartTexture->GetWidth() / 20,(m_pHartTexture->GetHeight() / 10) * 2};
	m_pHartTexture->Draw(destRectHartTexture, srcRectHartTexture);

	const Rectf destRectLivesCounterTex{ 470,390,100,30 };
	m_plivesCounter->Draw(destRectLivesCounterTex);

	m_PlayerBarRectX = 140;
	for (int i = 0; i < m_playerHealt; ++i)
	{
		utils::FillRect(float(m_PlayerBarRectX) + (m_HealthBarWidth + m_RectSpacing) * i, float(m_PlayerBarRectY), float(m_HealthBarWidth), float(m_HealthBarHeight));
	}

	for (int i = m_playerHealt; i < 10; ++i)
	{
		utils::DrawRect(float(m_PlayerBarRectX) + (m_HealthBarWidth + m_RectSpacing) * i, float(m_PlayerBarRectY), float(m_HealthBarWidth), float(m_HealthBarHeight));
	}

	utils::SetColor(Color4f(0.5f, 0, 0, 1));
	m_EnemyBarRectX = 140;
	for (int i = 0; i < m_EnemyHealt; ++i)
	{
		utils::FillRect(float(m_EnemyBarRectX) + (m_HealthBarWidth + m_RectSpacing) * i, float(m_EnemyBarRectY), float(m_HealthBarWidth), float(m_HealthBarHeight));
	}

	for (int i = m_EnemyHealt; i < 10; ++i)
	{
		utils::DrawRect(float(m_EnemyBarRectX) + (m_HealthBarWidth + m_RectSpacing) * i, float(m_EnemyBarRectY), float(m_HealthBarWidth), float(m_HealthBarHeight));
	}

	
	//std::cout << m_player->m_playerHealt << std::endl;

}

void UI::GetValues()
{
	/*switch (m_boxItemType)
	{
	case UI::Boxitem::Dagger:
		m_StartFrame = 4;
		break;
	case UI::Boxitem::FireBottle:
		m_StartFrame = 2;
		break;
	default:
		m_StartFrame = 6;
		break;
	}*/
}
