#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32U }, "Fuzzy Logic" },
	m_exitGame{ false }
{
	setupFontAndText(); // load font 
	srand(time(NULL));

	sf::CircleShape circleShape;
	circleShape.setRadius(10.0f);
	circleShape.setFillColor(sf::Color::Red);

	for (int i = 0; i < 30; i++)
	{
		m_enemiesUnits.push_back(circleShape);
	}

	circleShape.setFillColor(sf::Color::Green);

	int row = 0, col = 0;

	for (int i = 0; i < 50; i++)
	{
		if (col >= 10)
		{
			row++;
			col = 0;
			circleShape.setPosition(250.0f + col * 25.0f, 0.0f + row * 25.0f);
		}
		if (col < 10)
		{
			circleShape.setPosition(250.0f + col * 25.0f, 25.0f + row * 25.0f);
			col++;
		}
		m_aiUnits.push_back(circleShape);
	}

	SetUpEnemies();
	SetUpAiResponse();

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
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			if (sf::Mouse::Left == newEvent.key.code)
			{
				SetUpEnemies();
				SetUpAiResponse();
			}
		}
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
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_message);

	for (int i = 0; i < m_deploy; i++)
	{
		m_window.draw(m_aiUnits[i]);
	}

	for (int i = 0; i < m_enemySize; i++)
	{
		m_window.draw(m_enemiesUnits[i]);
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("Assets\\fonts\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_message.setFont(m_ArialBlackfont);
	m_message.setPosition(150.0f, 250.0f);
	m_message.setCharacterSize(18);
	m_message.setString("");
	m_message.setFillColor(sf::Color::White);
}

void Game::SetUpEnemies()
{
	m_enemySize = rand() % 30 + 1;
	m_enemyDistance = rand() % 70 + 1;

	int row = 0, col = 0;

	for (int i = 0; i < m_enemySize; i++)
	{
		if (col >= 10)
		{
			row++;
			col = 0;
			m_enemiesUnits[i].setPosition(250.0f + col * 25.0f, 300.f + m_enemyDistance * 3.0f + row * 25.0f);
		}
		if (col < 10)
		{
			m_enemiesUnits[i].setPosition(250.0f + col * 25.0f, 300.f + m_enemyDistance * 3.0f + row * 25.0f);
			col++;
		}
	}
}

void Game::SetUpAiResponse()
{
	m_deploy = m_fuzzy.Defuzzify(m_enemySize, m_enemyDistance);
	std::cout << m_deploy << std::endl;
	std::string str = "The enemy army has a size of: " + std::to_string(m_enemySize) + " and is: " 
		+ std::to_string(m_enemyDistance) + " units away. \n Ai deployed: " + std::to_string(m_deploy) + " units.";
	m_message.setString(str);
}
