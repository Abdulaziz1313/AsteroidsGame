#include "Boss.h"
#include <iostream>

Boss::Boss()
{
	float rngX = static_cast<float>(((std::rand() % 750)) + 25);
	float rngY = static_cast<float>(((std::rand() % 550)) + 25);
	m_location = sf::Vector2f(rngX, rngY);
	rngX = (static_cast<float>(std::rand() % 100) - 50.0f) / 25.0f;
	rngY = (static_cast<float>(std::rand() % 100) - 50.0f) / 25.0f;
	m_velocity = sf::Vector2f(rngX, rngY);
	m_boss.setFillColor(sf::Color::Red);
	m_boss.setRadius(40.0f);
	m_boss.setPosition(m_location);
	setupSprite();
}

void Boss::processEvent(sf::Event t_event)
{
}

void Boss::update(sf::Time t_delteTime)
{
	if (m_active)
	{
		m_location += m_velocity;
		bounce();
	}
}

void Boss::render(sf::RenderWindow& t_window)
{
	if (m_active)
	{
		m_bossSprite.setPosition(m_location);
		t_window.draw(m_bossSprite);
	}
}

void Boss::bounce()
{
	if (m_location.x < 0.0f)
	{
		m_location.x = 0.0f;
		m_velocity.x = -m_velocity.x;
	}
	if (m_location.x > 750.0f)
	{
		m_location.x = 750.0f;
		m_velocity.x = -m_velocity.x;
	}
	if (m_location.y < 0.0f)
	{
		m_location.y = 0.0f;
		m_velocity.y = -m_velocity.y;
	}
	if (m_location.y > 600.0f)
	{
		m_location.y = 600.0f;
		m_velocity.y = -m_velocity.y;
	}
}

void Boss::setupSprite() {

	if (!m_bossTexture.loadFromFile("ASSETS\\IMAGES\\boss.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading ship" << std::endl;
	}
	m_bossSprite.setTexture(m_bossTexture);
	m_bossSprite.setPosition(m_location);
	m_bossSprite.setTextureRect(sf::IntRect(120, 50,170,150));
}