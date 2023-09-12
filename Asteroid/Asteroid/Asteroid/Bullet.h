#pragma once

#include <SFML/Graphics.hpp>
#include "Dire.h"

class Bullet
{
public:
	Bullet();
	void update();
	void render(sf::RenderWindow& t_window);
	void checkOutOfBounds();
	bool fire(sf::Vector2f t_location, Direction t_direction);


	bool m_active{ false };
	sf::Vector2f m_location;
	sf::Vector2f m_velocity;
	sf::CircleShape m_bullet{ 5.0f };
};

