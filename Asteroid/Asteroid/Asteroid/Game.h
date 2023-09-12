/// <summary>
/// author Abdulaziz Aloufi August 2021
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "enemy.h"
#include "Bullet.h"
#include "Boss.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	void gameOver();

	int diedAttempet = 3;

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void fire();
	void collisions();

	int died();
	
	void setupFontAndText();
	void setupSprite();
	void setScore(int score, int life);
	void finalScore(int score);

	

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Text m_hitsMessage;
	sf::Text m_finalScore;
	int m_hits{ 0 };
	sf::Texture m_BackgroundTexture; // texture used for sfml logo
	sf::Sprite m_BackgroundSprite; // sprite used for sfml logo
	sf::Texture m_shipTexture;
	sf::Sprite m_shipSprite;
	sf::Sprite m_enemySprite;
	sf::Texture m_enemyTexture;
	sf::Texture m_BulletTexture;
	sf::Sprite m_BulletSprite;
	sf::Vector2f m_playerLocation;
	sf::Music m_music;
	int score = 0;


	Player m_player;
	enemy m_enemy[10];
	bool m_exitGame; // control exiting game
	Bullet m_bullets[12];
	Boss m_boss[2];
	sf::Vector2f m_BulletLocation{ 0.0f, 0.0f };
	bool m_canShoot{ true };
	int m_timeToFire{ 0 };


	

	


};

#endif // !GAME_HPP

