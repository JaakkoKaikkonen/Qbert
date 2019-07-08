#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Animation.hpp"

namespace Game {

	class Box
	{
	public:
		Box(gameDataRef data, sf::IntRect sprite, float x, float y);

		bool contains(sf::Vector2f point);

		bool changeColor();

		void animation();

		void reset();

		void draw();

		sf::Vector2f getPos() { return box.getPosition(); }

		
	private:
		gameDataRef data;

		sf::Sprite box;

		sf::IntRect changeColorAnimationFrames[3] = { BLUE_BOX, RED_BOX, YELLOW_BOX };

		Animation changeColorAnimation;
	};

}
