#include "pch.h"
#include "Player.h"
#include "texture.h"
#include <utils.h>
#include <iostream>

Player::Player(int rows, int coloms, float framesec, float scale,int startrow, Point2f bottomleft) :
	AnimatedSprite{ rows, coloms, framesec, scale, startrow},
	m_OnGroundColor{ 1.0f, 0, 0, 1.0f },
	m_InAirColor{ 0, 1.0f, 0, 1.0f },
	m_Velocity {},
	m_GravityAccelaration{ 0,-981 },
	m_IsOnGround{ false },
	m_GoingLeft{ false }
{
	m_pTexture = new Texture("Images/Playerpart1.png");
	m_spriteWidth = m_pTexture->GetWidth() / m_colomsIdx;
	m_spriteHeight = m_pTexture->GetHeight() / m_RowIdx;
	m_Shape = GetShape();
	m_Shape.left = bottomleft.x;
	m_Shape.bottom = bottomleft.y;
	m_playerHealt = 10;
	m_playerLives = 3;
	m_playerHarts = 5;
}

void Player::Update(float elapsed, Level* level)
{ 
	if (m_Shape.left <= level->GetBoundaries().left && m_Velocity.x > 0)
	{
		m_Shape.left += m_Velocity.x * elapsed;
	}
	if (m_Shape.left >= level->GetBoundaries().left)
	{
		m_Shape.left += m_Velocity.x * elapsed;
	}
	if (m_Shape.left + m_Shape.width == level->GetBoundaries().left + level->GetBoundaries().width - 10)
	{
		m_Shape.left += m_Velocity.x = 0;
	}
	m_Velocity += m_GravityAccelaration * elapsed;
	m_Shape.bottom += m_Velocity.y * elapsed;
	
	
	animation();
	AnimatedSprite::Update(elapsed);

	m_PlayerHitBox = Rectf(m_Shape.left+ 55, m_Shape.bottom, m_Shape.width/2 + 5, m_Shape.height + 30);
	utils::DrawRect(m_PlayerHitBox);

	if (m_playerHealt <= 0 && m_playerLives > 0 )
	{
		m_playerLives = m_playerLives - 1;
		m_playerHealt = 10;
	}
	else if (m_playerLives == 0) {
		std::cout << "GAME OVER" << std::endl;
	}
}

void Player::Draw()
{
	glPushMatrix();
	glTranslatef(m_Shape.left + 73, m_Shape.bottom, 0);
	glScalef(m_Velocity.x < 0 ? 1 : -1, 1, 1);
	glTranslatef(-m_Shape.left - 73, -m_Shape.bottom, 0);
	AnimatedSprite::Draw();
	glPopMatrix();
}

void Player::Damage(int amount)
{
	m_playerHealt = m_playerHealt != 0 ? m_playerHealt - amount : m_playerHealt;
}

void Player::animation() {
	switch (m_ActionState)
	{
	case ActionState::Idle:
		m_StartRow = 1;
		m_colomsIdx = 1;
		break;
	case ActionState::moving:
		m_StartRow = 2;
		m_colomsIdx = 3;
		break;
	case ActionState::jumping:
		m_StartRow = 3;
		m_colomsIdx = 1;
		break;
	case ActionState::chrouching:
		m_StartRow = 3;
		m_colomsIdx = 1;
		break;
	case ActionState::hitting:
		m_StartRow = 4;
		m_colomsIdx = 5;
		break;
	default:
		break;
	}
}

  