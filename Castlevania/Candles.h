#pragma once
#include "AnimatedSprite.h"

class Texture;

class Candles final : public AnimatedSprite
{
public:
	enum class DropType { Healt, wip, trowingknife };
	Candles(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, DropType type);
	~Candles();
	void Draw();
	void Update(float elpasedSec);
	bool IsOverlapping(const Rectf rect) const;
	void DropItem();

private:
	DropType m_Type;

	Rectf m_Boundaries;
};
