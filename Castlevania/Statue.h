#pragma once
#include <Vector2f.h>
#include "AnimatedSprite.h"
#include "PowerUpManager.h"
class Texture;

class Statue final: public AnimatedSprite
{
public:
	enum class DropType{Healt,Wip,Trowingknife};
	Statue(int rows, int coloms, float framesec, float scale, int startrow, Point2f bottomleft, DropType type, PowerUpManager* powerUpManager);
	~Statue() = default;
	void Draw();
	void Update(float elpasedSec);
	bool IsOverlapping(const Rectf rect) const;
	void DropItem();

private:
	DropType m_Type;
	Rectf m_Boundaries;
	PowerUpManager* m_pPowerUpManager;
};

