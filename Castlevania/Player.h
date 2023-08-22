#pragma once
#include "Level.h"
#include "AnimatedSprite.h"

enum class ActionState
{
	Idle,
	moving,
	jumping,
	crouching,
	hitting

};
class Player final : public AnimatedSprite
{
public:

	Player(int rows, int coloms, float framesec, float scale,int startrow, Point2f bottomleft);
	~Player() override = default;

	void Update(float elapsed, Level* level);
	void Draw() override;
	void animation();
	void Damage(int amount);
	//void Move(int direction);


	Vector2f m_Velocity{ 0.0f,0.0f };
	ActionState m_ActionState{ ActionState::Idle };

	int m_playerHealth;
	int m_playerLives;
	int m_playerHarts;
	float m_WalkSpeed{};


private:
	const Color4f m_OnGroundColor;
	const Color4f m_InAirColor;

	const float m_GravityAcceleration;
};

