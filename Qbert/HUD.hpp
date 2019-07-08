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
		gameDataRef data;

		sf::Sprite playerText;

		sf::IntRect playerTextAnimationFrames[6] = { PLAYER_TEXT_01, PLAYER_TEXT_02, PLAYER_TEXT_03, PLAYER_TEXT_04, PLAYER_TEXT_05, PLAYER_TEXT_06 };

		Animation playerTextAnimation;

		sf::Sprite playerIndex;

		sf::IntRect playerIndexAnimationFrames[3] = { PLAYER_INDEX_YELLOW, PLAYER_INDEX_BLUE, PLAYER_INDEX_RED };

		Animation playerIndexAnimation;

		sf::Text score;

		sf::Text changeTo;

		sf::Sprite changeToBox;

		sf::IntRect changeToBoxAnimationFrames[3] = { CHANGE_TO_BOX_BLUE, CHANGE_TO_BOX_RED, CHANGE_TO_BOX_YELLOW };

		Animation changeToBoxAnimation;

		sf::Sprite arrows[4];

		int arrowCount = 0;

		int arrowTimer = 0;

	};

}

