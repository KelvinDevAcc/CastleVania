#include "pch.h"
#include "Zombie.h"
#include <iostream>

Zombie::Zombie(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, bool moveright,Player* player) :
	BasicEnemy(rows, coloms, framesec, scale, startrow, bottomleft),
	m_AttackSpeed{2},
	m_AttackDelayTime{ 0 },
	m_MovingRight{moveright},
	m_player{ player },
	m_Speed{ 100.0f }
{
	m_pTexture = new Texture("Images/Enemy's.png");
	m_spriteWidth = m_pTexture->GetWidth() / m_colomsIdx;
	m_spriteHeight = m_pTexture->GetHeight() / m_RowIdx;
	m_PlayerRect = GetShape();
	m_PlayerRect.left = bottomleft.x;
	m_PlayerRect.bottom = bottomleft.y;
	m_colomsIdx = 2;
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

			std::cout << "Player hit by enemy\n";
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
	// Implement additional drawing behavior for the Zombie enemy
}

void Zombie::Attack()
{
	BasicEnemy::Attack();
	// Implement attack behavior specific to the Zombie enemy
	// For example, you can add code to control the Zombie's attack animation or logic
}