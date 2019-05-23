#include "Snake.hpp"
#include "Collision.hpp"

namespace Game {

	Snake::Snake(gameDataRef data, HUD* hud, int spawnDelay)
		: Enemy(data, spawnDelay)
	{
		_enemy.setTexture(_data->assets.getTexture("Enemy"));
		_enemy.setTextureRect(SNAKE_BACK_RIGHT);
		_enemy.setOrigin(_enemy.getGlobalBounds().width / 2, _enemy.getGlobalBounds().height / 2);
		_enemy.setScale(2.0f, 2.0f);
		_enemy.setPosition(SNAKE_START_POS);

		_hud = hud;
	}


	void Snake::update(std::array<Box*, AMOUNT_OF_BOXES>& boxes, sf::Vector2f QbertPos) {
		if (_spawnCounter > 0) {
			_spawnCounter--;
		} else {

			if (_fell) {

				this->fall();

			} else {

				if (_drop) {
					_enemy.move(0.0f, 5.0f);
					if (boxes[1]->contains(_enemy.getPosition() + sf::Vector2f(0.0f, -28.0f))) {
						_drop = false;
						_moveTimer = 30;
					}
				} else {

					_moveTimer++;

					if (_moveTimer > 47) {

						if (_egg && boxes[boxes.size() - 1]->getPos().y < _enemy.getPosition().y + TILESIZE * 0.25f) {
							if (_eggHatch) {
								_enemy.move(0.0f, -38.0f);
								_egg = false;
							} else {
								_eggHatch = true;
								_moveTimer = 0;
								return;
							}
						}

						if (_egg) {

							_dir = (Dir)(rand() % 2);

						} else {

							sf::Vector2f _points[4];
							//Down
							_points[0] = sf::Vector2f((int)(cos(PI / 2 + 40 * (PI / 180)) * TILESIZE/2), (int)(sin(PI / 2 + 40 * (PI / 180)) * TILESIZE/2)) + _enemy.getPosition();
							//Right
							_points[1] = sf::Vector2f((int)(cos(PI / 2 - 40 * (PI / 180)) * TILESIZE/2), (int)(sin(PI / 2 - 40 * (PI / 180)) * TILESIZE/2)) + _enemy.getPosition();
							//Up
							_points[2] = sf::Vector2f((int)(cos(-PI / 2 + 40 * (PI / 180)) * TILESIZE/2), (int)(sin(-PI / 2 + 40 * (PI / 180)) * TILESIZE/2)) + _enemy.getPosition();
							//Left
							_points[3] = sf::Vector2f((int)(cos(-PI / 2 - 40 * (PI / 180)) * TILESIZE/2), (int)(sin(-PI / 2 - 40 * (PI / 180)) * TILESIZE/2)) + _enemy.getPosition();

							float _distances[4];

							for (int i = 0; i < 4; i++) {
								_distances[i] = Collision::distanceBetween(_points[i], QbertPos);
							}

							int winnerIndex = 0;
							if (boxes[boxes.size() - 1]->getPos().y > _enemy.getPosition().y + TILESIZE) {
								for (int i = 0; i < 4; i++) {
									if (_distances[winnerIndex] > _distances[i]) {
										winnerIndex = i;
									}
								}
							} else {
								winnerIndex = 2;
								for (int i = 2; i < 4; i++) {
									if (_distances[winnerIndex] > _distances[i]) {
										winnerIndex = i;
									}
								}
							}

							_dir = (Dir)winnerIndex;
						}

						_jumpCounter = 26;
						_moveTimer = 0;

						_jumpStartPos = _enemy.getPosition();
						x = 0;
						y = 0;
					}

					if (_jumpCounter > 0) {

						switch (_dir) {
						case Dir::Up:
							x += 32.0f / 26.0f;
							y = 1 / 12.0f * pow(x - 25, 2) - 48.0f - 49.0f / 12.0f;
							_enemy.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
							break;
						case Dir::Down:
							x -= 32.0f / 26.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(-x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							_enemy.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
							break;
						case Dir::Right:
							x += 32.0f / 26.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							_enemy.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
							break;
						case Dir::Left:
							x -= 32.0f / 26.0f;
							y = 1 / 12.0f * pow(-x - 25, 2) - 48.0f - 49.0f / 12.0f;
							_enemy.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
						}

						_jumpCounter--;

					}
				}
			}
		}
	}

	void Snake::reset(bool gameOver) {
		if (gameOver) {
			_spawnCounter = _spawnDelay;
		} else {
			_spawnCounter = 100;
			_hud->addToScore(500);
		}
		_enemy.setPosition(SNAKE_START_POS);
		_egg = true;
		_eggHatch = false;
		_drop = true;
		_fell = false;
		_jumpCounter = 0;
	}

	void Snake::animate() {
		if (_jumpCounter > 0 || _drop) {
			if (_egg) {
				_enemy.setTextureRect(SNAKE_EGG_JUMP);
			} else {
				switch (_dir) {
				case Dir::Up:
					_enemy.setTextureRect(SNAKE_BACK_RIGHT_JUMP);
					break;
				case Dir::Down:
					_enemy.setTextureRect(SNAKE_FRONT_LEFT_JUMP);
					break;
				case Dir::Right:
					_enemy.setTextureRect(SNAKE_FRONT_RIGHT_JUMP);
					break;
				case Dir::Left:
					_enemy.setTextureRect(SNAKE_BACK_LEFT_JUMP);
				}
			}
		} else {
			if (_egg) {
				_enemy.setTextureRect(SNAKE_EGG);
			} else {
				switch (_dir) {
				case Dir::Up:
					_enemy.setTextureRect(SNAKE_BACK_RIGHT);
					break;
				case Dir::Down:
					_enemy.setTextureRect(SNAKE_FRONT_LEFT);
					break;
				case Dir::Right:
					_enemy.setTextureRect(SNAKE_FRONT_RIGHT);
					break;
				case Dir::Left:
					_enemy.setTextureRect(SNAKE_BACK_LEFT);
				}
			}
		}
	}

}
