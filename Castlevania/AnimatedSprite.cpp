#include "pch.h"
#include "AnimatedSprite.h"
#include <utils.h>


AnimatedSprite::AnimatedSprite(int rows, int coloms, float framesec, float scale, int startrow) :
	m_Desrect{},
	m_pTexture{nullptr},
	m_StartRow{startrow},
	m_colomsIdx{coloms},
	m_RowIdx{rows},
	m_spriteHeight{0},
	m_spriteWidth{0},
	m_FrameSec{framesec},
	m_Scale{scale},
	m_CurrentFrame{0},
	m_AccuSec{0},
	m_StartFrame{0},
	m_startpos{0, 0}
{
}

AnimatedSprite::~AnimatedSprite()
{
	delete m_pTexture;
}

void AnimatedSprite::Draw() 
{
	m_destRect.left = m_Shape.left;
	m_destRect.bottom = m_Shape.bottom;
	m_destRect.width = m_Shape.width * m_Scale;
	m_destRect.height = m_Shape.height * m_Scale;
	m_Desrect = m_destRect;

	m_pTexture->Draw(m_destRect, GetShape());
}

void AnimatedSprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec)
	{
		++m_CurrentFrame %= m_colomsIdx;
		m_AccuSec -= m_FrameSec;
	}
}

Rectf AnimatedSprite::GetShape() const 
{
	Rectf srcRect{};
	srcRect.width = m_spriteWidth;
	srcRect.height = m_spriteHeight;
	srcRect.left = m_spriteWidth * ((m_StartFrame + m_CurrentFrame) % m_colomsIdx);
	srcRect.bottom = m_spriteHeight * (m_StartRow + ((m_StartFrame + m_CurrentFrame) / m_colomsIdx));
	return srcRect;
}