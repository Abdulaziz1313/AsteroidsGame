#include "Player.h"
#include "Game.h"
#include <iostream>


Player::Player()
{

		m_location = sf::Vector2f(350.0f, 500.0f);
		m_Ship.setFillColor(sf::Color::Blue);
		m_Ship.setSize(sf::Vector2f(20.0f, 20.0f));
		m_Ship.setPosition(m_location);
		setupSprite();
	


}

void Player::processEvent(sf::Event t_event)
{
}

void Player::update(sf::Time t_delteTime)
{
	if (m_active) {
		m_direction = Direction::Up;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_direction = Direction::Up;
			m_location += sf::Vector2f(0.0f, -1.9f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_direction = Direction::Down;
			m_location += sf::Vector2f(0.0f, 1.9f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_direction = Direction::Left;
			m_location += sf::Vector2f(-1.9f, 0.0f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_direction = Direction::Right;
			m_location += sf::Vector2f(1.9f, 0.0f);
		}

	}
	
	

}

void Player::render(sf::RenderWindow& t_window)
{
	if (m_active) {
		m_shipSprite.setPosition(m_location);
		t_window.draw(m_shipSprite);
	}
}

void Player::setupSprite()
{

	if (!m_shipTexture.loadFromFile("ASSETS\\IMAGES\\ship.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading ship" << std::endl;
	}
	m_shipSprite.setTexture(m_shipTexture);
	m_shipSprite.setPosition(m_location);
	m_shipSprite.setTextureRect({ 0, 0, 64, 64 });


}

