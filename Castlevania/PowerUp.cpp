#include "pch.h"
#include "PowerUp.h"
#include "texture.h"
#include "utils.h"


PowerUp::PowerUp(Level* level, int rows, int coloms, float scale, int startrow, Point2f bottomleft, Type type):
	BasicSprite{ rows, coloms, scale, startrow },
	m_Type{ type },
	m_Velocity{},
	m_GravityAccelaration{ 0,-981 },
	m_pLevel{level}
{
	m_pTexture = new Texture("Images/PickUps.png");

	m_spriteWidth = m_pTexture->GetWidth() / m_colomsIdx;
	m_spriteHeight = m_pTexture->GetHeight() / m_RowIdx;
	m_Shape = GetShape();
	m_Shape.left = bottomleft.x;
	m_Shape.bottom = bottomleft.y;
	
	switch (m_Type)
	{
	case PowerUp::Type::Health:
		m_StartFrame = 1;
		break;
	case PowerUp::Type::Wip:
		m_StartFrame = 0;
		break;
	case PowerUp::Type::Trowingknife:
		m_StartFrame = 2;
		break;
	}

}


void PowerUp::Update(float elapsedSec) 
{
	m_Velocity += m_GravityAccelaration * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	LevelColision();
}

void PowerUp::Draw() const
{
	BasicSprite::Draw();
}

bool PowerUp::IsOverlapping(const Rectf rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

void PowerUp::LevelColision()
{
	m_pLevel->HandelCollision(m_Shape, m_Velocity);
}

PowerUp::Type PowerUp::GetType()
{
	return m_Type;
}