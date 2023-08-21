#pragma once

#include "BasicEnemy.h"
#include "Player.h"

class Zombie final : public BasicEnemy
{
public:
	Zombie(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, bool moveright,Player* player);
	~Zombie() = default;
	virtual void Update(float elapsed) override;
	virtual void Draw() override;
	virtual void Attack() override;

private:

	float m_AttackSpeed;
	float m_AttackDelayTime;

	bool m_MovingRight;
	Player* m_player;
	float m_Speed;

};
