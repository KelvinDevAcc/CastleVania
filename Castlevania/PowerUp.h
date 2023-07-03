#pragma once
#include <utils.h>
#include "BasicSprite.h"
#include "Level.h"

class Texture;

class PowerUp : public BasicSprite
{
public:
	enum class Type{Health, Wip, Trowingknife};
	PowerUp(Level* level, int rows, int coloms,float scale, int startrow, Point2f bottomleft, Type type);
	~PowerUp() = default;
	void Update(float elepsedSec);
	void Draw() const;
	bool IsOverlapping(const Rectf rect) const;
	void LevelColision();
	Type GetType();
private: 
	Type m_Type;
	Rectf m_TextClip;
	Point2f m_Position;
	Level* m_pLevel;
	Vector2f m_Velocity{ 0.0f,0.0f };
	const Vector2f m_GravityAccelaration;

};

