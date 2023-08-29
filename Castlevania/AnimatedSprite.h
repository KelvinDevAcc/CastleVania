#pragma once
#include <Texture.h>

class AnimatedSprite
{
public:
	AnimatedSprite(int rows, int columns,float frameRec, float scale,int startRow);
	virtual ~AnimatedSprite();
	virtual void Draw();
	virtual void Draw(Point2f drawPosition, int flip);
	

	virtual void Update(float elapsedSec);
	Rectf GetShape() const;
	Rectf m_PlayerRect;
	Rectf m_desrect;
	Rectf m_AtackBox;

protected:
	Texture* m_pTexture;

	int m_StartRow{};

	int m_ColomsIdx{};
	int m_RowIdx{};

	float m_spriteHeight{};
	float m_spriteWidth{};
	Rectf m_DestRect{};


private:
	float m_FrameSec{};
	float m_Scale{};
	int m_CurrentFrame{};
	float m_AccuSec{};

	int m_StartFrame{};




	Point2f m_StartPos{};
};

