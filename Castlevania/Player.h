#pragma once
#include "Level.h"
#include "AnimatedSprite.h"

enum class ActionState
{
	Idle,
	moving,
	jumping,
	chrouching,
	hitting

};
class Player final : public AnimatedSprite
{
public:
	Player(int rows, int coloms, float framesec, float scale,int startrow, Point2f bottomleft);
	~Player() = default;
	void Update(float elapsed, Level* level);
	void Draw();
	void animation();
	void Damage(int amount);

	Vector2f m_Velocity{ 0.0f,0.0f };
	ActionState m_ActionState{ ActionState::Idle };
	Rectf m_PlayerHitBox;

	int m_playerHealt;
	int m_playerLives;
	int m_playerHarts;

private:
	const Color4f m_OnGroundColor;
	const Color4f m_InAirColor;

	const Vector2f m_GravityAccelaration;
	bool m_IsOnGround;

	bool m_GoingLeft;



};

