#include "pch.h"
#include <iostream>
#include "Camera.h"

Camera::Camera(float width, float height) :
	m_BottomLeft{},
	m_Height{height},
	m_Width{width}, m_fadeInActive(false), m_fadeOutActive(false), m_fadeTimer(0), m_fadeDuration(0)
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left - m_Width/2 + target.width/2, target.bottom-m_Height/2 + target.height/2);
}

void Camera::clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x <= 0.f)
	{
		bottomLeftPos.x = 0;
	}
	else if (bottomLeftPos.x + m_Width >= m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.y <= 0.f)
	{
		bottomLeftPos.y = 0;
	}
	else if (bottomLeftPos.y + m_Height >= m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.height - m_Height;
	}
}

void  Camera::Transform(const Rectf& target)
{
	m_BottomLeft = Track(target);
	clamp(m_BottomLeft);
	glTranslatef(-m_BottomLeft.x,0, 0);
}

void Camera::FadeIn(float duration)
{
	m_fadeInActive = true;
	m_fadeOutActive = false;
	m_fadeTimer = 0.0f;
	m_fadeDuration = duration;
}

void Camera::FadeOut(float duration)
{
	m_fadeInActive = false;
	m_fadeOutActive = true;
	m_fadeTimer = 0.0f;
	m_fadeDuration = duration;
}






