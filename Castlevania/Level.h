#pragma once
#include <vector>
#include <Vector2f.h>
#include "BasicSprite.h"


class Level : public BasicSprite
{
public: 
	Level();
	~Level() = default;

	void DrawBackground();
	void HandelCollision(Rectf& actorShape, Vector2f& actorVelocity);
	void HandelUpCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsonStairs(const Rectf& actorShape) const;
	bool IsOnGround(const Rectf& actorShape) const;
	void NextlevelPart(int levelPart);
	Rectf GetBoundaries();
	Rectf LevelShape;
	int m_levelPart;


private:

	std::vector<std::vector<Point2f>> m_pLevelCollisionPoints;
	std::vector<std::vector<Point2f>> m_pStairsCollisionPoints;


	Rectf m_Boundaries;
};

