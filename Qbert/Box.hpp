#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Animation.hpp"

namespace engine {

	class Box
	{
	public:
		Box(gameDataRef data, sf::IntRect sprite, float x, float y);

		bool contains(sf::Vector2f point);

		bool changeColor();

		void animation();

		void reset();

		void draw();

		sf::Vector2f getPos() { return _box.getPosition(); }

		
	private:
		gameDataRef _data;

		sf::Sprite _box;

		sf::IntRect _changeColorAnimationFrames[3] = { BLUE_BOX, RED_BOX, YELLOW_BOX };

		Animation _changeColorAnimation;
	};

}
