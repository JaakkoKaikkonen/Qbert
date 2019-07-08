#include "Snake.hpp"
#include "Collision.hpp"

namespace Game {

	Snake::Snake(gameDataRef data, HUD* hud, int spawnDelay)
		: Enemy(data, spawnDelay)
	{
		enemy.setTexture(this->data->assets.getTexture("Enemy"));
		enemy.setTextureRect(SNAKE_BACK_RIGHT);
		enemy.setOrigin(enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().height / 2);
		enemy.setScale(2.0f, 2.0f);
		enemy.setPosition(SNAKE_START_POS);

		this->hud = hud;
	}


	void Snake::update(std::array<Box*, AMOUNT_OF_BOXES>& boxes, sf::Vector2f qbertPos) {
		if (spawnCounter > 0) {
			spawnCounter--;
		} else {

			if (fell) {

				this->fall();

			} else {

				if (drop) {
					enemy.move(0.0f, 5.0f);
					if (boxes[1]->contains(enemy.getPosition() + sf::Vector2f(0.0f, -28.0f))) {
						drop = false;
						moveTimer = 30;
					}
				} else {

					moveTimer++;

					if (moveTimer > 47) {

						if (egg && boxes[boxes.size() - 1]->getPos().y < enemy.getPosition().y + TILESIZE * 0.25f) {
							if (eggHatch) {
								enemy.move(0.0f, -38.0f);
								egg = false;
							} else {
								eggHatch = true;
								moveTimer = 0;
								return;
							}
						}

						if (egg) {

							dir = (Dir)(rand() % 2);

						} else {

							sf::Vector2f points[4];
							//Down
							points[0] = sf::Vector2f((int)(cos(PI / 2 + 40 * (PI / 180)) * TILESIZE/2), (int)(sin(PI / 2 + 40 * (PI / 180)) * TILESIZE/2)) + enemy.getPosition();
							//Right
							points[1] = sf::Vector2f((int)(cos(PI / 2 - 40 * (PI / 180)) * TILESIZE/2), (int)(sin(PI / 2 - 40 * (PI / 180)) * TILESIZE/2)) + enemy.getPosition();
							//Up
							points[2] = sf::Vector2f((int)(cos(-PI / 2 + 40 * (PI / 180)) * TILESIZE/2), (int)(sin(-PI / 2 + 40 * (PI / 180)) * TILESIZE/2)) + enemy.getPosition();
							//Left
							points[3] = sf::Vector2f((int)(cos(-PI / 2 - 40 * (PI / 180)) * TILESIZE/2), (int)(sin(-PI / 2 - 40 * (PI / 180)) * TILESIZE/2)) + enemy.getPosition();

							float distances[4];

							for (int i = 0; i < 4; i++) {
								distances[i] = Collision::distanceBetween(points[i], qbertPos);
							}

							int winnerIndex = 0;
							if (boxes[boxes.size() - 1]->getPos().y > enemy.getPosition().y + TILESIZE) {
								for (int i = 0; i < 4; i++) {
									if (distances[winnerIndex] > distances[i]) {
										winnerIndex = i;
									}
								}
							} else {
								winnerIndex = 2;
								for (int i = 2; i < 4; i++) {
									if (distances[winnerIndex] > distances[i]) {
										winnerIndex = i;
									}
								}
							}

							dir = (Dir)winnerIndex;
						}

						jumpCounter = 26;
						moveTimer = 0;

						jumpStartPos = enemy.getPosition();
						x = 0;
						y = 0;
					}

					if (jumpCounter > 0) {

						switch (dir) {
						case Dir::Up:
							x += 32.0f / 26.0f;
							y = 1 / 12.0f * pow(x - 25, 2) - 48.0f - 49.0f / 12.0f;
							enemy.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
							break;
						case Dir::Down:
							x -= 32.0f / 26.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(-x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							enemy.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
							break;
						case Dir::Right:
							x += 32.0f / 26.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							enemy.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
							break;
						case Dir::Left:
							x -= 32.0f / 26.0f;
							y = 1 / 12.0f * pow(-x - 25, 2) - 48.0f - 49.0f / 12.0f;
							enemy.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
						}

						jumpCounter--;

					}
				}
			}
		}
	}

	void Snake::reset(bool gameOver) {
		if (gameOver) {
			spawnCounter = spawnDelay;
		} else {
			spawnCounter = 100;
			hud->addToScore(500);
		}
		enemy.setPosition(SNAKE_START_POS);
		egg = true;
		eggHatch = false;
		drop = true;
		fell = false;
		jumpCounter = 0;
	}

	void Snake::animate() {
		if (jumpCounter > 0 || drop) {
			if (egg) {
				enemy.setTextureRect(SNAKE_EGG_JUMP);
			} else {
				switch (dir) {
				case Dir::Up:
					enemy.setTextureRect(SNAKE_BACK_RIGHT_JUMP);
					break;
				case Dir::Down:
					enemy.setTextureRect(SNAKE_FRONT_LEFT_JUMP);
					break;
				case Dir::Right:
					enemy.setTextureRect(SNAKE_FRONT_RIGHT_JUMP);
					break;
				case Dir::Left:
					enemy.setTextureRect(SNAKE_BACK_LEFT_JUMP);
				}
			}
		} else {
			if (egg) {
				enemy.setTextureRect(SNAKE_EGG);
			} else {
				switch (dir) {
				case Dir::Up:
					enemy.setTextureRect(SNAKE_BACK_RIGHT);
					break;
				case Dir::Down:
					enemy.setTextureRect(SNAKE_FRONT_LEFT);
					break;
				case Dir::Right:
					enemy.setTextureRect(SNAKE_FRONT_RIGHT);
					break;
				case Dir::Left:
					enemy.setTextureRect(SNAKE_BACK_LEFT);
				}
			}
		}
	}

}
