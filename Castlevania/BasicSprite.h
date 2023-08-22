#pragma once
#include <Texture.h>

class BasicSprite
{
public:
	BasicSprite(int rows, int coloms,float scale, int startrow);
	BasicSprite(Texture* Texture, int rows, int coloms, float scale, int startrow);

	~BasicSprite();
	void Draw() const;
	Rectf GetShape() const;
	Rectf m_Shape;

protected:
	Texture* m_pTexture;

	int m_StartRow;
	int m_StartFrame;

	int m_colIndex;
	int m_rowIndex;

	float m_spriteHeight;
	float m_spriteWidth;

	float m_Scale;

private:


	Point2f m_startpos;
};

