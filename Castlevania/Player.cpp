#include "pch.h"
#include "Player.h"
#include "texture.h"
#include <utils.h>
#include <iostream>

Player::Player(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft)
	: AnimatedSprite{ rows, coloms, framesec, scale, startrow },
	  m_Velocity{},
	  m_playerHealth{10},
	  m_playerLives{3},
	  m_playerHarts{5},
	  m_WalkSpeed{133},
	  m_OnGroundColor{1.0f, 0, 0, 1.0f},
	  m_InAirColor{0, 1.0f, 0, 1.0f},
	  m_GravityAcceleration{-1400}
{
	m_pTexture = new Texture("Images/Playerpart1.png"); 
	m_spriteWidth = m_pTexture->GetWidth() / m_colomsIdx;
	m_spriteHeight = m_pTexture->GetHeight() / m_RowIdx;

	//m_PlayerRect = GetShape();

	m_PlayerRect.height = 70;
	m_PlayerRect.width = 40;
	m_PlayerRect.left = bottomleft.x;
	m_PlayerRect.bottom = bottomleft.y;
}

void Player::Update(float elapsed, Level* level)
{
	if (m_PlayerRect.bottom < 0.0f)
		m_PlayerRect.bottom = 50.0f;

	if(m_PlayerRect.left < 0.0f)
		m_PlayerRect.left = 0.0f;

	if (m_PlayerRect.left + m_PlayerRect.width > level->GetBoundaries().left + level->GetBoundaries().width)
		m_PlayerRect.left = level->GetBoundaries().left + level->GetBoundaries().width - m_PlayerRect.width;

	// Add gravity
	m_Velocity.y += m_GravityAcceleration * elapsed;

	// Apply velocity
	m_PlayerRect.left += m_Velocity.x * elapsed;
	m_PlayerRect.bottom += m_Velocity.y * elapsed;

	animation();
	AnimatedSprite::Update(elapsed); 	

	if (m_playerHealth <= 0 && m_playerLives > 0 )
	{
		m_playerLives = m_playerLives - 1;
		m_playerHealth = 10;
	}
	else if (m_playerLives == 0) {
		std::cout << "GAME OVER" << std::endl;
	}
}

void Player::Draw()
{
	AnimatedSprite::Draw(Point2f{ m_PlayerRect.left,m_PlayerRect.bottom }, m_Velocity.x < 0 ? 1 : -1);

	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawRect(m_PlayerRect, true);
	
	//utils::SetColor(Color4f{ 0,1,0,1 });
	//utils::DrawRect(m_PlayerHitBox, true);

	//utils::SetColor(Color4f{ 0,0,1,1 });
	//utils::DrawRect(m_Desrect, true);
}

void Player::Damage(int amount)
{
	m_playerHealth = m_playerHealth != 0 ? m_playerHealth - amount : m_playerHealth;
}

//void Player::Move(int direction)
//{
//	m_ActionState = ActionState::moving;
//	m_Velocity.x = -m_WalkSpeed;
//	m_CanPress = false;
//}

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
	case ActionState::crouching:
		m_StartRow = 3;
		m_colomsIdx = 1;
		break;
	case ActionState::hitting:
		m_StartRow = 4;
		m_colomsIdx = 5;
		break;
	}
}

  