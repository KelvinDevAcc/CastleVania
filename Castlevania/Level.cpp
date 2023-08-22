#include "pch.h"
#include "Level.h"
#include "texture.h"
#include <utils.h>
#include <SVGParser.h>
#include <iostream>


Level::Level() : BasicSprite{1,1,2.f,1}
{
	m_pTexture = new Texture("Images/levelPart1.png");
	SVGParser::GetVerticesFromSvgFile("Images/Level/levelPart1.svg", m_pLevelCollisionPoints);

	m_spriteWidth = m_pTexture->GetWidth() /m_rowIndex;
	m_spriteHeight = m_pTexture->GetHeight() / m_colIndex;
	m_Shape = GetShape();
	m_Shape.left = 0;
	m_Shape.bottom = 0;
	m_levelPart = 1;

}


void Level::DrawBackground() const
{
	BasicSprite::Draw();
	for (const std::vector<Point2f>& polygon : m_pStairsCollisionPoints)
	{
		utils::DrawPolygon(polygon, true);
	}

}

void Level::HandelCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	const float actorCenter{ actorShape.left + actorShape.width / 2.0f };

	const Point2f topPoint{ actorCenter, actorShape.bottom + actorShape.height };
	const Point2f bottomPoint{actorCenter, actorShape.bottom};

	//Point2f midelLPoint{ actorShape.left, actorShape.bottom + actorShape.height / 2 };
	//Point2f midelRPoint{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2 };

	utils::HitInfo hitInfo{};
	for (size_t i = 0; i < m_pLevelCollisionPoints.size(); i++)
	{
		if (utils::Raycast(m_pLevelCollisionPoints[i], topPoint, bottomPoint, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0;
		}

		//if (utils::Raycast(m_pLevelCollisionPoints[i], midelLPoint, midelRPoint, hitInfo))
		//{
		//	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));

		//	Vector2f rayVector{ midelLPoint,midelRPoint };
		//	actorShape.left = hitInfo.intersectPoint.x + actorShape.width;
		//	actorVelocity.x = 0;
		//}
	}
}
void Level::HandleStairCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	const float actorCenter{ actorShape.left + actorShape.width / 2.0f };

	const Point2f topPoint{ actorCenter, actorShape.bottom + actorShape.height };
	const Point2f bottomPoint{ actorCenter, actorShape.bottom };

	utils::HitInfo hitInfo{};
	for (size_t i = 0; i < m_pStairsCollisionPoints.size(); i++)
	{
		if (utils::Raycast(m_pStairsCollisionPoints[i], topPoint, bottomPoint, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0;
		}
	}

}

bool Level::IsCollidingWithStair(Rectf& actorShape) const
{
	const float actorCenter{ actorShape.left + actorShape.width / 2.0f };

	const Point2f topPoint{ actorCenter, actorShape.bottom + actorShape.height / 2.0f };
	const Point2f bottomPoint{ actorCenter, actorShape.bottom };

	utils::HitInfo hitInfo{};
	for (size_t i = 0; i < m_pStairsCollisionPoints.size(); i++)
	{
		if (utils::Raycast(m_pStairsCollisionPoints[i], topPoint, bottomPoint, hitInfo))
			return true;
	}

	return false;
}


bool Level::IsOnGround(const Rectf& actorShape) const
{
	utils::HitInfo hitInfo{};

	const Point2f topPoint{ actorShape.left + actorShape.width / 2,actorShape.bottom + actorShape.height };
	const Point2f bottomPoint{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1 };

	for (size_t i = 0; i < m_pLevelCollisionPoints.size(); i++)
	{
		if (utils::Raycast(m_pLevelCollisionPoints[i], topPoint, bottomPoint, hitInfo))
			return true;
	}

	return false;
}

void Level::NextLevelPart(int levelPart) 
{
	m_levelPart = levelPart;
	m_levelPart = (m_levelPart != 5) ? m_levelPart + 1 : m_levelPart;

	//new texture
	const std::string base_stringTex = "Images/levelPart";
	const std::string file_extensionTex = ".png";
	const std::string TexFileName = base_stringTex + std::to_string(m_levelPart) + file_extensionTex;

	delete m_pTexture;
	m_pTexture = new Texture(TexFileName);


	//clear vertices
	m_pLevelCollisionPoints.clear();
	const std::string base_stringSvg = "Images/Level/levelPart";
	const std::string file_extensionSvg = ".svg";
	const std::string svgFileName = base_stringSvg + std::to_string(m_levelPart) + file_extensionSvg;
	SVGParser::GetVerticesFromSvgFile(svgFileName, m_pLevelCollisionPoints);
	
	SVGParser::GetVerticesFromSvgFile("Images/Level/levelPart21.svg", m_pStairsCollisionPoints);
}

Rectf Level::GetBoundaries() 
{
	m_spriteWidth = m_pTexture->GetWidth() / m_rowIndex;
	m_spriteHeight = m_pTexture->GetHeight() / m_colIndex;
	m_Shape = GetShape();
	m_Shape.left = 0;
	m_Shape.bottom = 0;
	m_Boundaries = Rectf(0, 0, m_spriteWidth * m_Scale, m_spriteHeight * m_Scale);
	return m_Boundaries;
}

