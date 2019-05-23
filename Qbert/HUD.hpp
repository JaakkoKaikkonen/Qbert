#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Animation.hpp"
#include "DEFINITIONS.hpp"
#include <string>

namespace Game {

	class HUD
	{
	public:
		HUD(gameDataRef data);

		void addToScore(int score);

		void update();

		void win();

		void reset();

		void draw();

	private:
		gameDataRef _data;

		sf::Sprite _playerText;

		sf::IntRect _playerTextAnimationFrames[6] = { PLAYER_TEXT_01, PLAYER_TEXT_02, PLAYER_TEXT_03, PLAYER_TEXT_04, PLAYER_TEXT_05, PLAYER_TEXT_06 };

		Animation _playerTextAnimation;

		sf::Sprite _playerIndex;

		sf::IntRect _playerIndexAnimationFrames[3] = { PLAYER_INDEX_YELLOW, PLAYER_INDEX_BLUE, PLAYER_INDEX_RED };

		Animation _playerIndexAnimation;

		sf::Text _score;

		sf::Text _changeTo;

		sf::Sprite _changeToBox;

		sf::IntRect _changeToBoxAnimationFrames[3] = { CHANGE_TO_BOX_BLUE, CHANGE_TO_BOX_RED, CHANGE_TO_BOX_YELLOW };

		Animation _changeToBoxAnimation;

		sf::Sprite _arrows[4];

		int _arrowCount = 0;

		int _arrowTimer = 0;

	};

}

