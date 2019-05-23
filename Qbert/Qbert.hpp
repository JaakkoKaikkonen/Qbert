#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace Game {

	class Qbert
	{
	public:
		Qbert(gameDataRef data);

		void move(Dir dir);

		void update();

		bool land();

		void fall();

		void reset();

		void setPos(sf::Vector2f pos);

		void draw();

		void drop() { _fell = true; }

		void swear() { _swear = true; }

		void fellFromLastRow() { _fellFromLastRow = true; }

		bool getSwear() { return _swear; }

		sf::Rect<float> getGlobalBounds() { return _Qbert.getGlobalBounds(); }

		sf::Vector2f getPos() { return _Qbert.getPosition(); }

		sf::Sprite& getSprite() { return _Qbert; }

		bool fell() { return _fell; }

		bool returnFellFromLastRow() { return _fellFromLastRow; }

	private:
		void animate();

	private:
		gameDataRef _data;

		sf::Sprite _Qbert;

		sf::Sprite _swearSprite;

		Dir _dir = Dir::Down;

		int _jumpCounter = 0;

		int _jumpTimer = 0;

		bool _fell = false;

		bool _fellFromLastRow = false;

		bool _swear = false;

		int _swearCounter = 0;

		float x, y;

		sf::Vector2f _jumpStartPos;

	};

}

