#include "pch.h"
#include "Zombie.h"
#include <iostream>

Zombie::Zombie(const int rows, const int columns, const float frameSec, float scale, const int startRow, const Point2f bottomLeft, const bool moveRight,Player* player) :
	BasicEnemy(rows, columns, frameSec, scale, startRow, bottomLeft),
	m_AttackSpeed{1.f},
	m_AttackDelayTime{ 0 },
	m_MovingRight{moveRight},
	m_player{ player },
	m_Speed{ 100.0f }
{
	m_pTexture = new Texture("Images/Enemy's.png");
	m_spriteWidth = m_pTexture->GetWidth() / float(m_ColomsIdx);
	m_spriteHeight = m_pTexture->GetHeight() / float(m_RowIdx);
	m_PlayerRect = GetShape();
	m_PlayerRect.left = bottomLeft.x;
	m_PlayerRect.bottom = bottomLeft.y;
	m_ColomsIdx = 2;
}



void Zombie::Update(float elapsed)
{
	BasicEnemy::Update(elapsed);

	// Implement additional update behavior for the Zombie enemy
	if (m_MovingRight)
	{

		m_PlayerRect.left += m_Speed * elapsed;
		if (m_PlayerRect.left + m_PlayerRect.width >= 600) // Change direction when reaching the right side
		{
			//m_MovingRight = false;
		}
	}
	else
	{
		m_PlayerRect.left -= m_Speed * elapsed;
		if (m_PlayerRect.left <= 0) // Change direction when reaching the left side
		{
			
		}
	}

	m_AttackDelayTime += elapsed;

	if (BasicEnemy::IsOverlapping(m_player->m_PlayerRect))
	{
		if (m_AttackDelayTime > m_AttackSpeed)
		{

			m_player->Damage(1);
			m_AttackDelayTime = 0;
		}
	}
	
	//// Gradually destroy the Zombie over time
	//m_Shape.width -= 10.0f * elapsed;
	//if (m_Shape.width <= 0)
	//{
	//	m_Shape.width = 0.0f;
	//	// Implement any additional logic when the Zombie is fully destroyed
	//}
}

void Zombie::Draw()
{
	BasicEnemy::Draw();
}

void Zombie::Attack()
{
	BasicEnemy::Attack();
	
}