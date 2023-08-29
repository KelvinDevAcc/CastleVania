#pragma once
#include <Texture.h>

class BasicSprite
{
public:
	BasicSprite(int rows, int columns,float scale, int startrRow);
	BasicSprite(Texture* Texture, int rows, int columns, float scale, int startRow);

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

