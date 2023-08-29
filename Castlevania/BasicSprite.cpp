#include "pch.h"
#include "BasicSprite.h"
#include "utils.h"
#include <iostream>


BasicSprite::BasicSprite(int rows, int columns, float scale, int startrRow) :
	m_pTexture{nullptr},
	m_StartRow{startrRow},
	m_StartFrame{0},
	m_colIndex{columns},
	m_rowIndex{rows},
	m_spriteHeight{0},
	m_spriteWidth{0},
	m_Scale{scale},
	m_startpos{0, 0}
{
	

}

BasicSprite::BasicSprite(Texture* texture,int rows, int columns, float scale, int startRow) :
	m_pTexture{texture},
	m_StartRow{startRow},
	m_StartFrame{0},
	m_colIndex{columns},
	m_rowIndex{rows},
	m_spriteHeight{0},
	m_spriteWidth{0},
	m_Scale{scale},
	m_startpos{0, 0}
{


}

BasicSprite::~BasicSprite()
{
	delete m_pTexture;
}

void BasicSprite::Draw() const
{
	Rectf destRect{};
	destRect.left = m_Shape.left;
	destRect.bottom = m_Shape.bottom;
	destRect.width = m_Shape.width * m_Scale;
	destRect.height = m_Shape.height * m_Scale;

	m_pTexture->Draw(destRect, GetShape());
}

Rectf BasicSprite::GetShape() const
{
	Rectf srcRect{};
	srcRect.width = m_spriteWidth;
	srcRect.height = m_spriteHeight;
	srcRect.left = m_spriteWidth * static_cast<float>(m_StartFrame);
	srcRect.bottom = m_spriteHeight * static_cast<float>(m_StartRow);
	return srcRect;
}