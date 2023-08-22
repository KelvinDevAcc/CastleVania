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
	m_destRect.left = m_PlayerRect.left;
	m_destRect.bottom = m_PlayerRect.bottom;
	m_destRect.width = m_PlayerRect.width * m_Scale;
	m_destRect.height = m_PlayerRect.height * m_Scale;
	m_Desrect = m_destRect;

	m_pTexture->Draw(m_destRect, GetShape());
}

void AnimatedSprite::Draw(Point2f drawPosition, int flip)
{

	Rectf drawRect
	{
		m_PlayerRect.left - 85,
		m_PlayerRect.bottom,
		180,
		73
	};



	glPushMatrix();
	{
		const int offset{104};

		glTranslatef(drawRect.left + offset , drawRect.bottom, 0);
		glScalef(float(flip), 1, 1);
		glTranslatef(-drawRect.left - offset, -drawRect.bottom, 0);
		m_pTexture->Draw(drawRect,GetShape());

		//utils::SetColor(Color4f{ 0,0,1,1 });
		//utils::DrawRect(drawRect);
	}
	glPopMatrix();

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