#pragma once

#include <SFML/Graphics.hpp>
#include "Dire.h"
class Player
{
public:
	Player();
	void setupSprite();

	void processEvent(sf::Event t_event);
	void update(sf::Time t_delteTime);
	void render(sf::RenderWindow& t_window);

	sf::RenderWindow m_window;

	sf::Vector2f m_location;
	Direction m_direction;
	sf::RectangleShape m_Ship;
	sf::Texture m_shipTexture;
	sf::Sprite m_shipSprite;
	bool m_active{ true };

	

};

