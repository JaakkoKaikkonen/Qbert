#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Qbert.hpp"
#include "Box.hpp"
#include "Enemy.hpp"
#include "Snake.hpp"
#include "RedBall.hpp"
#include "FlyingDisc.hpp"
#include <array>
#include "HUD.hpp"


namespace Game {

	class GameState : public State
	{
	public:
		GameState(gameDataRef data);

		void init();

		void handleInput();
		void update();
		void draw();

	private:
		void newBoxHit();

		void updateDiscs();

		void checkMapCollision();

		void checkEnemyCollision();

		void updateEnemies();

		void win();

		void reset();

	private:
		gameDataRef data;

		HUD hud;

		std::array<Box*, AMOUNT_OF_BOXES> boxes;

		int boxesHit = 0;

		Qbert* qbert;

		Snake* snake;

		RedBall* redBalls[AMOUNT_OF_RED_BALLS];

		FlyingDisc* discs[2];

		bool onDisc[2] = { 0, 0 };

		sf::Vector2f oldQbertPos;

		int swearCounter = 0;

		bool won = false;

		int winTimer = 190;

		sf::Color backGroundColor = sf::Color::Black;

	};

}

