#pragma once
#include "utils.h"


class Rectf;

class Camera 
{
public:
	Camera( float width, float height);
	~Camera() = default;
	void SetlevelBoundaries(const Rectf& levelBounderies);
	void Transform(const Rectf& target);
	Point2f Track(const Rectf& target) const;
	void clamp(Point2f& bottomLeftPos);

	Point2f m_bottomleft;

	void FadeIn(float duration);
	void FadeOut(float duration);


private:
	float m_height;
	Rectf m_LevelBoundaries;
	const float m_Normalwitdh;
	float m_width;


	bool m_fadeInActive;
	bool m_fadeOutActive;
	float m_fadeTimer;
	float m_fadeDuration;

	
};

