/// <summary>
/// @author Abdulaziz Aloufi 
/// @date August 2021
///
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>
#include <sstream>
#include "Dire.h"





/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}



/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
void Game::gameOver()
{

	m_window.clear();
	
	
	m_window.draw(m_finalScore);
	m_window.draw(m_welcomeMessage);
	m_window.display();
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		m_player.processEvent(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		fire();
	}
	
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{

	if (m_exitGame)
	{
		m_window.close();
	}
	m_player.update(t_deltaTime);
	
	for (int i = 0; i < 10; i++)
	{
		m_enemy[i].update(t_deltaTime);
	}
	for (int i = 0; i < 2; i++)
	{
		m_boss[i].update(t_deltaTime);
	}
	for (int i = 0; i < 12; i++)
	{
		m_bullets[i].update();
	}
	if (m_timeToFire > 0)
	{
		m_timeToFire--;
		if (m_timeToFire == 0)
		{
			m_canShoot = true;
			
		}

	}
	collisions();
	setScore(died(), diedAttempet);
	finalScore(score);
	


}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_BackgroundSprite);
	m_player.render(m_window);
	for (int i = 0; i < 10; i++)
	{
		m_enemy[i].render(m_window);
	}
	for (int i = 0; i < 2; i++)
	{
		m_boss[i].render(m_window);
	}
	for (int i = 0; i < 12; i++)
	{
		m_bullets[i].render(m_window);
	}
	m_window.draw(m_enemy->m_enemySprite);
	
	if (m_player.m_active) {
		m_window.draw(m_player.m_shipSprite);

	}
			
	m_window.draw(m_hitsMessage);
	m_window.draw(m_enemySprite);
	if (!m_player.m_active)
	{
		gameOver();
	}
	m_window.display();
}

void Game::fire()
{
	bool shootSuccess = false;
	if (m_canShoot && m_player.m_direction == Direction::Up)
	{

		m_canShoot = false;
		m_timeToFire = 20;

		for (int i = 0; i < 12 && !shootSuccess; i++)
		{
			shootSuccess = m_bullets[i].fire(m_player.m_location, m_player.m_direction);
		}
		for (int i = 0; i < 12 && !shootSuccess; i++)
		{
			shootSuccess = m_bullets[i].fire(m_boss->m_location, m_boss->m_direction);
		}
	}
}

void Game::collisions()
{



	for (int i = 0; i < 12; i++)
	{
		if (m_bullets[i].m_active)
		{
			
			for (int j = 0; j <10; j++)
			{
				if (m_enemy[j].m_active)
				{
					
					if (m_bullets[i].m_bullet.getGlobalBounds().intersects(m_enemy[j].m_enemySprite.getGlobalBounds()))
					{
						m_bullets[i].m_active = false;
						m_enemy[j].m_active = false;
						score++;
					
					}
									
				}
			}
			for (int k = 0; k < 2; k++)
			{
				if (m_boss[k].m_active)
				{
					if (m_bullets[i].m_bullet.getGlobalBounds().intersects(m_boss[k].m_bossSprite.getGlobalBounds()))
					{
						m_bullets[k].m_active = false;
						m_boss[k].m_active = false;
						score = score + 10;


					}
				}
			}
			setScore(score, diedAttempet);
		
		}

	}

}


int Game::died()
{
	       
			for (int j = 0; j < 10; j++)
			{

				if (m_enemy[j].m_active)
				{

					sf::FloatRect enemy = m_enemy[j].m_enemySprite.getGlobalBounds();
					sf::FloatRect ship = m_player.m_shipSprite.getGlobalBounds();
					if (ship.intersects(enemy))
					{
						m_enemy[j].m_active = false;
						if (diedAttempet > 0 && score >0)
						{
							
							score = score --;
							diedAttempet--;
				
						}
						else 
						{
							m_player.m_active = false;
							gameOver();

						
						}
					}
				}


			}
			for (int i = 0; i < 2; i++) {
				if (m_boss[i].m_active) {
					sf::FloatRect boss = m_boss[i].m_bossSprite.getGlobalBounds();
					sf::FloatRect ship = m_player.m_shipSprite.getGlobalBounds();
					if (ship.intersects(boss))
					{
						m_boss[i].m_active = false;
						if (diedAttempet > 0) {
							diedAttempet = 0;
							m_player.m_active = false;
							gameOver();
						}
						else {
							m_player.m_active = false;
							gameOver();
							

						}

					}

				}
			}
			return score;

}
/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Game Over ");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(170.0f, 200.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

	setScore(score, diedAttempet);

	


	

	if (!m_music.openFromFile("ASSETS\\Audio\\astreiod.ogg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_music.setVolume(65);
	m_music.play();


}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	
	
		if (!m_BackgroundTexture.loadFromFile("ASSETS\\IMAGES\\background4.jpg"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading background" << std::endl;
		}
		m_BackgroundSprite.setTexture(m_BackgroundTexture);
		m_BackgroundSprite.setPosition(0.0f, 0.0f);

	
	
}

void Game::setScore(int score, int life)
{
	std::ostringstream sscore;
	sscore << "Score: " << score;
	std::ostringstream Attempt;
	sscore << "\n life: " << life;
	m_hitsMessage.setFont(m_ArialBlackfont);
	m_hitsMessage.setString(sscore.str()+ "\n" + Attempt.str());
	m_hitsMessage.setPosition(20.0f, 20.0f);
	m_hitsMessage.setCharacterSize(20U);
	m_hitsMessage.setFillColor(sf::Color::Red);

}

void Game::finalScore(int score) {
	std::ostringstream sscore;
	sscore << "Your Score is:  " << score;
	m_finalScore.setFont(m_ArialBlackfont);
	m_finalScore.setString(sscore.str());
	m_finalScore.setPosition(200.0f, 300.0f);
	m_finalScore.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_finalScore.setCharacterSize(50U);
	m_finalScore.setOutlineColor(sf::Color::Red);
	m_finalScore.setFillColor(sf::Color::Black);
	m_finalScore.setOutlineThickness(3.0f);
	
}








