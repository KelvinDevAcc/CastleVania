#pragma once
#include <Vector2f.h>
#include "AnimatedSprite.h"
#include "PowerUpManager.h"
class Texture;

class Statue final: public AnimatedSprite
{
public:
	enum class DropType{health,wip,throwingKnives};

	Statue(int rows, int columns, float frameSec, float scale, int startRow, Point2f bottomLeft, DropType type, PowerUpManager* powerUpManager);

	void Draw() override;
	void Update(float elapsed) override;
	bool IsOverlapping(const Rectf rect) const;
	void DropItem() const;

private:
	DropType m_Type;
	Rectf m_Boundaries;
	PowerUpManager* m_pPowerUpManager;
};

