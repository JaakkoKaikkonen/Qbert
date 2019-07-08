#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Enemy.hpp"
#include "HUD.hpp"
#include "DEFINITIONS.hpp"
#include <array>

namespace Game {

	class Snake : public Enemy
	{
	public:
		Snake(gameDataRef data, HUD* hud, int spawnDelay);

		void update(std::array<Box*, AMOUNT_OF_BOXES>& boxes, sf::Vector2f qbertPos) override;

		void reset(bool gameOver) override;

		void animate() override;

		bool getEgg() { return egg; }

	private:
		bool egg = true;

		bool eggHatch = false;

		HUD* hud;

	};

}