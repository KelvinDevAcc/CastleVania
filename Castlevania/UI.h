#pragma once
#include <Texture.h>
#include "Player.h"


class UI
{
public:
	enum class Boxitem
	{
		Dagger,
		FireBottle
	};
	UI(Player* player);
	~UI();
	void Draw(Point2f ActorPosition);
	void GetValues();
	void Update(float elapsedSec);
	double m_Timer;


protected:
	Texture* m_pScoreTexture;
	Texture* m_pPlayerTexture;
	Texture* m_pEnemyTexture;


	Texture* m_pTimerTexture;
	Texture* m_pStageTexture;

	Texture* m_pHartsCounter;
	Texture* m_plivesCounter;

	Player* m_player;


	int m_LiveCounter;

	int m_OldScore;
	int m_NewScore;

	int m_HartsCounter;
	int m_playerHealt;
	int m_HealthBarWidth;
	int m_HealthBarHeight;
	int m_RectSpacing;
	int m_PlayerBarRectX;
	int m_PlayerBarRectY;

	int m_EnemyHealt;
	int m_EnemyBarRectX;
	int m_EnemyBarRectY;

	Boxitem m_BoxItemType;

};

