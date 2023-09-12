#include "Bullet.h"
#include <iostream>


Bullet::Bullet()
{
	m_bullet.setFillColor(sf::Color::Red);
}

void Bullet::update()
{
	if (m_active)
	{
		m_location += m_velocity;
		checkOutOfBounds();
	}
}

void Bullet::render(sf::RenderWindow& t_window)
{
	if (m_active)
	{
		m_bullet.setPosition(m_location);
		t_window.draw(m_bullet);
	}
}

void Bullet::checkOutOfBounds()
{
	if (m_location.x < 0.0f)
	{
		m_active = false;
	}
	if (m_location.x > 800.0f)
	{
		m_active = false;
	}
	if (m_location.y < 0.0f)
	{
		m_active = false;

	}
	if (m_location.y > 600.0f)
	{
		m_active = false;
	}
}

bool Bullet::fire(sf::Vector2f t_location, Direction t_direction)
{
	if (m_active)
	{
		return false;
	}
	else
	{
		m_active = true;
		m_location = t_location;
		switch (t_direction)
		{
		case Direction::None:
			break;
		case Direction::Up:
			m_velocity = sf::Vector2f{ 0.0f, -3.0f };
			break;
		case Direction::Down:
			m_velocity = sf::Vector2f{ 0.0f, 3.0f };
			break;
		case Direction::Left:
			m_velocity = sf::Vector2f{ -3.0f, 0.0f };
			break;
		case Direction::Right:
			m_velocity = sf::Vector2f{ 3.0f, 0.0f };
			break;
		default:
			break;
		}
		return true;
	}
}
