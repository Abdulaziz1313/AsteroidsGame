#pragma once

#include <SFML/Graphics.hpp>

class enemy
{

public:

	enemy();

	void processEvent(sf::Event t_event);
	void update(sf::Time t_delteTime);
	void render(sf::RenderWindow& t_window);
	void bounce();

	void setupSprite();

	sf::Vector2f m_location;
	sf::Vector2f m_velocity;
	sf::CircleShape m_enemy;
	sf::Texture m_enemyTexture;
	sf::Sprite m_enemySprite;
	bool m_active{ true };
};

