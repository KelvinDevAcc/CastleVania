#include "pch.h"
#include "BasicSprite.h"
#include "utils.h"
#include <iostream>


BasicSprite::BasicSprite(int rows, int coloms, float scale, int startrow) :
	m_RowIdx{ rows },
	m_colomsIdx{ coloms },
	m_Scale{ scale },
	m_StartRow{ startrow },
	m_StartFrame{ 0 },
	m_spriteWidth{ 0 },
	m_spriteHeight{ 0 },
	m_startpos{ 0,0 },
	m_pTexture{ nullptr }
{
	

}

BasicSprite::BasicSprite(Texture* texture,int rows, int coloms, float scale, int startrow) :
	m_RowIdx{ rows },
	m_colomsIdx{ coloms },
	m_Scale{ scale },
	m_StartRow{ startrow },
	m_StartFrame{ 0 },
	m_spriteWidth{ 0 },
	m_spriteHeight{ 0 },
	m_startpos{ 0,0 },
	m_pTexture{ texture }
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
	srcRect.left = m_spriteWidth * m_StartFrame;
	srcRect.bottom = m_spriteHeight * m_StartRow;
	return srcRect;
}