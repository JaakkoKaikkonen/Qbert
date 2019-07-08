#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Animation.hpp"
#include "DEFINITIONS.hpp"

namespace Game {

	class FlyingDisc
	{
	public:
		FlyingDisc(gameDataRef data, sf::Vector2f startPos);

		bool move();

		bool contains(sf::Vector2f point);

		void reset(sf::Vector2f startPos);

		void draw();

		sf::Vector2f getPos() { return disc.getPosition(); }

	private:
		gameDataRef data;

		sf::Sprite disc;

		sf::IntRect discAnimationFrames[4] = { FLYING_DISC_01, FLYING_DISC_02, FLYING_DISC_03, FLYING_DISC_04 };

		Animation discAnimation;

		sf::Vector2f moveVector;

		bool done = false;

		int waitCounter = 30;

		int upCounter = 20;
	};

}

