#include "pch.h"
#include <iostream>
#include "Camera.h"

Camera::Camera(float width, float height) :
	m_width{ width },
	m_height{ height },
	m_bottomleft{},
	m_Normalwitdh{width}
{
}

void Camera::SetlevelBoundaries(const Rectf& levelBounderies)
{
	m_LevelBoundaries = levelBounderies;
}

Point2f Camera::Track(const Rectf& target) const
{
	utils::DrawRect(target);
	return Point2f(target.left - m_width/2 + target.width/2, target.bottom-m_height/2 + target.height/2);
}

void Camera::clamp(Point2f& bottomLeftPos)
{
	if (bottomLeftPos.x <= 0.f)
	{
		bottomLeftPos.x = 0;
	}
	else if (bottomLeftPos.x + m_width >= m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.width - m_width;
	}
	if (bottomLeftPos.y <= 0.f)
	{
		bottomLeftPos.y = 0;
	}
	else if (bottomLeftPos.y + m_height >= m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.height - m_height;
	}
}

void  Camera::Transform(const Rectf& target)
{
	m_bottomleft = Track(target);
	clamp(m_bottomleft);
	glTranslatef(-m_bottomleft.x, -m_bottomleft.y, 0);
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






