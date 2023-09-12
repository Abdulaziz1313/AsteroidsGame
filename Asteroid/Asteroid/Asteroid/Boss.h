#pragma once
#include <SFML/Graphics.hpp>
#include "Dire.h"

class Boss
{





	public:

		Boss();

		void processEvent(sf::Event t_event);
		void update(sf::Time t_delteTime);
		void render(sf::RenderWindow& t_window);
		void bounce();

		void setupSprite();

		Direction m_direction;
		sf::Vector2f m_location;
		sf::Vector2f m_velocity;
		sf::CircleShape m_boss;
		bool m_active{ true };
		sf::Texture m_bossTexture;
		sf::Sprite m_bossSprite;
};

