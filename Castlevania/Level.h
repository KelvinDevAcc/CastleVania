#pragma once
#include <vector>
#include <Vector2f.h>
#include "BasicSprite.h"


class Level : public BasicSprite
{
public: 
	Level();
	~Level() = default;

	void DrawBackground() const;
	void HandelCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	void HandleStairCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsCollidingWithStair(const Rectf& actorShape) const;
	bool IsOnGround(const Rectf& actorShape) const;

	//void NextLevelPart(int levelPart);

	void LoadLevel(int levelIndex);

	Rectf GetBoundaries();
	Rectf LevelShape;

	int m_CurrentLevelPart{-1};


private:

	std::vector<std::vector<Point2f>> m_pLevelCollisionPoints;
	std::vector<std::vector<Point2f>> m_pStairsCollisionPoints;

	std::vector<std::string> m_LevelTextures{};
	std::vector<std::string> m_LevelCollisionSVG{};


	Rectf m_Boundaries;
};

