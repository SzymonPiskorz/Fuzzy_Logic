#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Rules.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_message;
	bool m_exitGame; // control exiting game
	Rules m_fuzzy;

	void SetUpEnemies();
	void SetUpAiResponse();
	int m_deploy;
	int m_enemySize;
	int m_enemyDistance;

	std::vector<sf::CircleShape> m_enemiesUnits;
	std::vector<sf::CircleShape> m_aiUnits;
};

#endif // !GAME_HPP

