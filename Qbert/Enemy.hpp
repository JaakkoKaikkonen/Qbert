#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Box.hpp"
#include <array>

namespace Game {

	class Enemy
	{
	public:
		Enemy(gameDataRef data, int spawnDelay);

		void draw();

		virtual void update(std::array<Box*, AMOUNT_OF_BOXES>& boxes, sf::Vector2f QbertPos) = 0;

		virtual void reset(bool gameOver) = 0;

		virtual void animate() = 0;

		bool land();

		void fall();

		void setFell() { fell = true; }

		bool getFell() { return fell; }

		sf::Sprite& getSprite() { return enemy; }

		sf::Vector2f getPos() { return enemy.getPosition(); }

		sf::Rect<float> getGlobalBounds() { return enemy.getGlobalBounds(); }
	
	protected:
		gameDataRef data;

		sf::Sprite enemy;

		int jumpCounter = 0;

		Dir dir = Dir::Right;

		int moveTimer;

		bool drop = true;

		bool fell = false;

		int spawnCounter = 100;

		int spawnDelay;

		sf::Vector2f jumpStartPos;

		float x, y;

	};


}
