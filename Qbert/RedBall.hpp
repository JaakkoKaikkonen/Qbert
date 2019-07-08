#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Enemy.hpp"
#include "DEFINITIONS.hpp"

namespace Game {

	class RedBall : public Enemy
	{
	public:
		RedBall(gameDataRef data, int spawnDelay);

		void update(std::array<Box*, 28>& boxes, sf::Vector2f qbertPos) override;

		void reset(bool gameOver) override;

		void animate() override;
	};

}