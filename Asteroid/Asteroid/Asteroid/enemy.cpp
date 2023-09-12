#include "enemy.h"
#include <iostream>

enemy::enemy()
{
	float rngX = static_cast<float>(((std::rand() % 750)) + 25);
	float rngY = static_cast<float>(((std::rand() % 550)) + 25);
	m_location = sf::Vector2f(rngX, rngY);
	rngX = (static_cast<float>(std::rand() % 100) - 50.0f) / 25.0f;
	rngY = (static_cast<float>(std::rand() % 100) - 50.0f) / 25.0f;
	m_velocity = sf::Vector2f(rngX, rngY);
	m_enemy.setFillColor(sf::Color::Green);
	m_enemy.setRadius(20.0f);
	m_enemy.setPosition(m_location);
	setupSprite();
}

void enemy::processEvent(sf::Event t_event)
{
}

void enemy::update(sf::Time t_delteTime)
{
	if (m_active)
	{
		m_location += m_velocity;
		bounce();
		
	}
}

void enemy::render(sf::RenderWindow& t_window)
{
	if (m_active)
	{
	   m_enemySprite.setPosition(m_location);
	   t_window.draw(m_enemySprite);
	}
}

void enemy::bounce()
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

void enemy::setupSprite() {

	if (!m_enemyTexture.loadFromFile("ASSETS\\IMAGES\\enemy1.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading ship" << std::endl;
	}

	m_enemySprite.setTexture(m_enemyTexture);
	m_enemySprite.setPosition(m_location);
	m_enemySprite.setOrigin(20.0f, 20.0f);
	m_enemySprite.setTextureRect({ 50,50, 72, 72 });

}
