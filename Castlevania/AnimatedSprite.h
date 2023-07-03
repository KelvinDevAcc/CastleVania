#pragma once
#include <Texture.h>

class AnimatedSprite
{
public:
	AnimatedSprite(int rows, int coloms,float framesec, float scale,int startrow);
	~AnimatedSprite();
	void Draw();
	void Update(float elapsedSec);
	Rectf GetShape() const;
	Rectf m_Shape;
	Rectf m_Desrect;

protected:
	Texture* m_pTexture;

	int m_StartRow{};

	int m_colomsIdx{};
	int m_RowIdx{};

	float m_spriteHeight{};
	float m_spriteWidth{};

private:
	float m_FrameSec{};
	float m_Scale{};
	int m_CurrentFrame{};
	float m_AccuSec{};

	int m_StartFrame{};

	Rectf m_destRect{};



	Point2f m_startpos{};
};

