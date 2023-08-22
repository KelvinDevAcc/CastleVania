#pragma once
#include "utils.h"


struct Rectf;

class Camera 
{
public:
	Camera( float width, float height);
	~Camera() = default;
	void SetlevelBoundaries(const Rectf& levelBounderies);
	void Transform(const Rectf& target);
	Point2f Track(const Rectf& target) const;
	void clamp(Point2f& bottomLeftPos) const;

	Point2f m_BottomLeft;

	void FadeIn(float duration);
	void FadeOut(float duration);


private:
	float m_Height;
	Rectf m_LevelBoundaries;
	const float m_NormalWidth;
	float m_Width;


	bool m_fadeInActive;
	bool m_fadeOutActive;
	float m_fadeTimer;
	float m_fadeDuration;

	
};

