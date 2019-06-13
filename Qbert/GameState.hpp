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
		gameDataRef _data;

		HUD _hud;

		std::array<Box*, AMOUNT_OF_BOXES> _boxes;

		int _boxesHit = 0;

		Qbert* _Qbert;

		Snake* _snake;

		RedBall* _redBalls[AMOUNT_OF_RED_BALLS];

		FlyingDisc* _discs[2];

		bool _onDisc[2] = { 0, 0 };

		sf::Vector2f _oldQbertPos;

		int _swearCounter = 0;

		bool _win = false;

		int _winTimer = 190;

		sf::Color _backGroundColor = sf::Color::Black;

	};

}

