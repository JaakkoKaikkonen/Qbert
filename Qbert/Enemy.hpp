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

		void drop() { _fell = true; }

		bool fell() { return _fell; }

		sf::Sprite& getSprite() { return _enemy; }

		sf::Vector2f getPos() { return _enemy.getPosition(); }

		sf::Rect<float> getGlobalBounds() { return _enemy.getGlobalBounds(); }
	
	protected:
		gameDataRef _data;

		sf::Sprite _enemy;

		int _jumpCounter = 0;

		Dir _dir = Dir::Right;

		int _moveTimer;

		bool _drop = true;

		bool _fell = false;

		int _spawnCounter = 100;

		int _spawnDelay;

		sf::Vector2f _jumpStartPos;

		float x, y;

	};


}
