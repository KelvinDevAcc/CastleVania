#include "pch.h"
#include "PowerUp.h"
#include "texture.h"
#include "utils.h"


PowerUp::PowerUp(Level* level, int rows, int columns, float scale, int startRow, Point2f bottomLeft, Type type):
	BasicSprite{ rows, columns, scale, startRow },
	m_Type{ type },
	m_pLevel{level},
	m_Velocity{},
	m_GravityAccelaration{0, -981}
{
	m_pTexture = new Texture("Images/PickUps.png");

	m_spriteWidth = m_pTexture->GetWidth() / float(m_colIndex);
	m_spriteHeight = m_pTexture->GetHeight() / float(m_rowIndex);
	m_Shape = GetShape();
	m_Shape.left = bottomLeft.x;
	m_Shape.bottom = bottomLeft.y;
	
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
	LevelCollision();
}

void PowerUp::Draw() const
{
	BasicSprite::Draw();
}

bool PowerUp::IsOverlapping(const Rectf rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

void PowerUp::LevelCollision()
{
	m_pLevel->HandelCollision(m_Shape, m_Velocity);
}

PowerUp::Type PowerUp::GetType() const
{
	return m_Type;
}
