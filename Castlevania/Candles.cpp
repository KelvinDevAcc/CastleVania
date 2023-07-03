#include "pch.h"
#include "Candles.h"
#include "texture.h"
#include <utils.h>
#include <iostream>

Candles::Candles(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, DropType type) :
	AnimatedSprite{ rows, coloms, framesec, scale, startrow },
	m_Type{ type }
{
	m_pTexture = new Texture("Images/PickUps.png");
	m_spriteWidth = m_pTexture->GetWidth() / m_colomsIdx;
	m_spriteHeight = m_pTexture->GetHeight() / m_RowIdx;
	m_Shape = GetShape();
	m_Shape.left = bottomleft.x;
	m_Shape.bottom = bottomleft.y;
	m_colomsIdx = 2;
}

Candles::~Candles()
{
	DropItem();
}

void Candles::Update(float elapsed)
{
	AnimatedSprite::Update(elapsed);
}

void Candles::Draw() 
{
	AnimatedSprite::Draw();
}

bool Candles::IsOverlapping(const Rectf rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

void Candles::DropItem()
{
	switch (m_Type)
	{
	case Candles::DropType::Healt:
		std::cout << "drop Healt";
		break;
	case Candles::DropType::wip:
		std::cout << "drop Wip";
		break;
	case Candles::DropType::trowingknife:
		std::cout << "drop Wip";
		break;
	default:
		break;
	}
}