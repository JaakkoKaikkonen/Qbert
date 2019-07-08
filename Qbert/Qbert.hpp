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

		void setFell() { fell = true; }

		void setSwear() { swear = true; }

		void setFellFromLastRow() { fellFromLastRow = true; }

		bool getSwear() { return swear; }

		sf::Rect<float> getGlobalBounds() { return qbert.getGlobalBounds(); }

		sf::Vector2f getPos() { return qbert.getPosition(); }

		sf::Sprite& getSprite() { return qbert; }

		bool getFell() { return fell; }

		bool getFellFromLastRow() { return fellFromLastRow; }

	private:
		void animate();

	private:
		gameDataRef data;

		sf::Sprite qbert;

		sf::Sprite swearSprite;

		Dir dir = Dir::Down;

		int jumpCounter = 0;

		int jumpTimer = 0;

		bool fell = false;

		bool fellFromLastRow = false;

		bool swear = false;

		int swearCounter = 0;

		float x, y;

		sf::Vector2f jumpStartPos;

	};

}

