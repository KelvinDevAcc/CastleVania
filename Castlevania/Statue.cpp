#include "pch.h"
#include "Statue.h"
#include "texture.h"
#include <utils.h>
#include <iostream>

Statue::Statue(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, DropType type, PowerUpManager* powerUpManager) :
	AnimatedSprite{ rows, coloms, framesec, scale, startrow },
	m_Type{type},
	m_pPowerUpManager{powerUpManager}
{
	m_pTexture = new Texture("Images/PickUps.png");
	m_spriteWidth = m_pTexture->GetWidth() / m_colomsIdx;
	m_spriteHeight = m_pTexture->GetHeight() / m_RowIdx;
	m_PlayerRect = GetShape();
	m_PlayerRect.left = bottomleft.x;
	m_PlayerRect.bottom = bottomleft.y;
	m_colomsIdx = 2;
}


void Statue::Update(float elapsed)
{
	AnimatedSprite::Update(elapsed);
}

void Statue::Draw() 
{
	AnimatedSprite::Draw();
}
 
bool Statue::IsOverlapping(const Rectf rect) const
{
	return utils::IsOverlapping(rect, m_PlayerRect);
}

void Statue::DropItem()
{
	switch (m_Type)
	{
	case Statue::DropType::Healt:
		m_pPowerUpManager->AddItem(10, 20, 2.f, 1, Point2f{m_Desrect.left, m_Desrect.bottom + 50}, PowerUp::Type::Health);
		break;
	case Statue::DropType::Wip:
		m_pPowerUpManager->AddItem(10, 20, 2.f, 1, Point2f{ m_Desrect.left, m_Desrect.bottom + 50 }, PowerUp::Type::Wip);
		break;
	case Statue::DropType::Trowingknife:
		m_pPowerUpManager->AddItem(10, 20, 2.f, 1, Point2f{ m_Desrect.left, m_Desrect.bottom + 50 }, PowerUp::Type::Trowingknife);
		break;
	default:
		break;
	}
}