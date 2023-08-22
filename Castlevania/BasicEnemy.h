#pragma once

#include "AnimatedSprite.h"

class BasicEnemy : public AnimatedSprite
{
public:
	BasicEnemy(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft);
	~BasicEnemy() = default;

	virtual void Update(float elapsed);
	virtual void Draw();
	virtual bool IsOverlapping(const Rectf& rect) const;
	virtual void Attack();
};