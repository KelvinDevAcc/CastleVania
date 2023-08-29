#include "pch.h"
#include "AnimatedSprite.h"
#include <utils.h>


AnimatedSprite::AnimatedSprite(int rows, const int columns, const float frameRec, float scale, const int startRow) :
	m_desrect{},
	m_pTexture{nullptr},
	m_StartRow{startRow},
	m_ColomsIdx{columns},
	m_RowIdx{rows},
	m_spriteHeight{0},
	m_spriteWidth{0},
	m_FrameSec{frameRec},
	m_Scale{scale},
	m_CurrentFrame{0},
	m_AccuSec{0},
	m_StartFrame{0},
	m_StartPos{0, 0}
{
}

AnimatedSprite::~AnimatedSprite()
{
	delete m_pTexture;
}

void AnimatedSprite::Draw() 
{
	m_DestRect.left = m_PlayerRect.left;
	m_DestRect.bottom = m_PlayerRect.bottom;
	m_DestRect.width = m_PlayerRect.width * m_Scale;
	m_DestRect.height = m_PlayerRect.height * m_Scale;
	m_desrect = m_DestRect;

	m_pTexture->Draw(m_DestRect, GetShape());

}

void AnimatedSprite::Draw(Point2f drawPosition, int flip)
{
	const Rectf drawRect
	{
		m_PlayerRect.left - 67,
		m_PlayerRect.bottom,
		160,
		69
	};



	glPushMatrix();
	{
		const int offset{95};

		glTranslatef(drawRect.left + offset , drawRect.bottom, 0);
		glScalef(static_cast<float>(flip), 1, 1);
		glTranslatef(-drawRect.left - offset, -drawRect.bottom, 0);
		m_pTexture->Draw(drawRect,GetShape());

	}
	glPopMatrix();

	m_AtackBox = drawRect;

}

void AnimatedSprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec)
	{
		++m_CurrentFrame %= m_ColomsIdx;
		m_AccuSec -= m_FrameSec;
	}
}

Rectf AnimatedSprite::GetShape() const 
{
	Rectf srcRect{};
	srcRect.width = m_spriteWidth;
	srcRect.height = m_spriteHeight;
	srcRect.left = m_spriteWidth * ((m_StartFrame + m_CurrentFrame) % m_ColomsIdx);
	srcRect.bottom = m_spriteHeight * (m_StartRow + ((m_StartFrame + m_CurrentFrame) / m_ColomsIdx));
	return srcRect;
}