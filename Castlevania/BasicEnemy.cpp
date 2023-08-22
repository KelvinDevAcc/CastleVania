#include "pch.h"
#include "BasicEnemy.h"
#include <utils.h>
#include <iostream>

BasicEnemy::BasicEnemy(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft) :
	AnimatedSprite(rows, coloms, framesec, scale, startrow)
{
	m_PlayerRect.left = bottomleft.x;
	m_PlayerRect.bottom = bottomleft.y;
}


void BasicEnemy::Update(float elapsed)
{
	AnimatedSprite::Update(elapsed);
	// Implement additional update behavior for the enemy
}

void BasicEnemy::Draw()
{
	AnimatedSprite::Draw();
	// Implement additional drawing behavior for the enemy
}

bool BasicEnemy::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_PlayerRect);
	// Implement additional overlapping check for the enemy
}

void BasicEnemy::Attack()
{
	// Implement attack behavior for the enemy
}