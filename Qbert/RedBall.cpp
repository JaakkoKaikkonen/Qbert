#include "RedBall.hpp"

namespace Game {

	RedBall::RedBall(gameDataRef data, int spawnDelay)
		: Enemy(data, spawnDelay)
	{
		enemy.setTexture(this->data->assets.getTexture("Enemy"));  
		enemy.setTextureRect(RED_BALL_JUMP);
	 	enemy.setOrigin(enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().height / 2);
		enemy.setScale(2.0f, 2.0f);
		enemy.setPosition(RED_BALL_START_POS);
	}


	void RedBall::update(std::array<Box*, 28>& boxes, sf::Vector2f qbertPos) {

		//std::cout << _spawnCounter << std::endl;

		if (spawnCounter > 0) {
			spawnCounter--;
		} else {

			if (fell) {

				this->fall();

			} else {

				if (drop) {
					enemy.move(0.0f, 5.0f);
					if (boxes[2]->contains(enemy.getPosition() + sf::Vector2f(0.0f, -5.0f))) {
						drop = false;
						moveTimer = 25;
					}

				} else {

					moveTimer++;

					if (moveTimer > 40) {

						jumpStartPos = enemy.getPosition();

						x = 0;
						y = 0;

						dir = (Dir)(rand() % 2);

						jumpCounter = 28;
						moveTimer = 0;

					}
				}

				if (jumpCounter > 0) {

					switch (dir) {
						case Dir::Down:
							x -= 32.0f/28.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(-x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							enemy.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
							break;
						case Dir::Right:
							x += 32.0f / 28.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							enemy.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
						}

						jumpCounter--;
						//y = ((3.0f*(21.0f + 8.0f*sqrt(5.0f))) / 1024.0f) * pow(x - ((32.0f*(4.0f*sqrt(5.0f) - 5.0f)) / 11.0f), 2) - 15.0f;
						//y = (3.0f * (13.0f + sqrt(105.0f))) / 512.0f * pow(x - (2.0f * (sqrt(105.0f) - 5.0f)), 2) - 15.0f;
				}

			}
		}
	}


	void RedBall::reset(bool gameOver) {
		if (gameOver) {
			spawnCounter = spawnDelay;
		} else {
			spawnCounter = 100;
		}
		enemy.setPosition(RED_BALL_START_POS);
		drop = true;
		fell = false;
		jumpCounter = 0;
	}

	void RedBall::animate() {
		if (jumpCounter > 0 || drop) {
			enemy.setTextureRect(RED_BALL_JUMP);
		} else {
			enemy.setTextureRect(RED_BALL);
		}
	}


}