#include "pch.h"
#include "Statue.h"
#include "texture.h"
#include <utils.h>
#include <iostream>

Statue::Statue(int rows, int columns, float frameSec, float scale, int startRow, Point2f bottomLeft, DropType type, PowerUpManager* powerUpManager) :
	AnimatedSprite{ rows, columns, frameSec, scale, startRow },
	m_Type{type},
	m_pPowerUpManager{powerUpManager}
{
	m_pTexture = new Texture("Images/PickUps.png");
	m_spriteWidth = m_pTexture->GetWidth() / float(m_ColomsIdx);
	m_spriteHeight = m_pTexture->GetHeight() / float(m_RowIdx);
	m_PlayerRect = GetShape();
	m_PlayerRect.left = bottomLeft.x;
	m_PlayerRect.bottom = bottomLeft.y;
	m_ColomsIdx = 2;
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

void Statue::DropItem() const
{
	switch (m_Type)
	{
	case Statue::DropType::health:
		m_pPowerUpManager->AddItem(10, 20, 2.f, 1, Point2f{m_desrect.left, m_desrect.bottom + 50}, PowerUp::Type::Health);
		break;
	case Statue::DropType::wip:
		m_pPowerUpManager->AddItem(10, 20, 2.f, 1, Point2f{ m_desrect.left, m_desrect.bottom + 50 }, PowerUp::Type::Wip);
		break;
	case Statue::DropType::throwingKnives:
		m_pPowerUpManager->AddItem(10, 20, 2.f, 1, Point2f{ m_desrect.left, m_desrect.bottom + 50 }, PowerUp::Type::Trowingknife);
		break;
	}
}
