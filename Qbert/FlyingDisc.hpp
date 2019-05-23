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

		sf::Vector2f getPos() { return _disc.getPosition(); }

	private:
		gameDataRef _data;

		sf::Sprite _disc;

		sf::IntRect _discAnimationFrames[4] = { FLYING_DISC_01, FLYING_DISC_02, FLYING_DISC_03, FLYING_DISC_04 };

		Animation _discAnimation;

		sf::Vector2f _moveVector;

		bool _done = false;

		int _waitCounter = 30;

		int _upCounter = 20;
	};

}

