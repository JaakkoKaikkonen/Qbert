#include "RedBall.hpp"

namespace engine {

	RedBall::RedBall(gameDataRef data, int spawnDelay)
		: Enemy(data, spawnDelay)
	{
		_enemy.setTexture(_data->assets.getTexture("Enemy"));  
		_enemy.setTextureRect(RED_BALL_JUMP);
	 	_enemy.setOrigin(_enemy.getGlobalBounds().width / 2, _enemy.getGlobalBounds().height / 2);
		_enemy.setScale(2.0f, 2.0f);
		_enemy.setPosition(RED_BALL_START_POS);
	}


	void RedBall::update(std::array<Box*, 28>& boxes, sf::Vector2f QbertPos) {

		//std::cout << _spawnCounter << std::endl;

		if (_spawnCounter > 0) {
			_spawnCounter--;
		} else {

			if (_fell) {

				this->fall();

			} else {

				if (_drop) {
					_enemy.move(0.0f, 5.0f);
					if (boxes[2]->contains(_enemy.getPosition() + sf::Vector2f(0.0f, -5.0f))) {
						_drop = false;
						_moveTimer = 25;
					}

				} else {

					_moveTimer++;

					if (_moveTimer > 40) {

						_jumpStartPos = _enemy.getPosition();

						x = 0;
						y = 0;

						_dir = (Dir)(rand() % 2);

						_jumpCounter = 28;
						_moveTimer = 0;

					}
				}

				if (_jumpCounter > 0) {

					switch (_dir) {
						case Dir::Down:
							x -= 32.0f/28.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(-x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							_enemy.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
							break;
						case Dir::Right:
							x += 32.0f / 28.0f;
							y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
							_enemy.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
						}

						_jumpCounter--;
						//y = ((3.0f*(21.0f + 8.0f*sqrt(5.0f))) / 1024.0f) * pow(x - ((32.0f*(4.0f*sqrt(5.0f) - 5.0f)) / 11.0f), 2) - 15.0f;
						//y = (3.0f * (13.0f + sqrt(105.0f))) / 512.0f * pow(x - (2.0f * (sqrt(105.0f) - 5.0f)), 2) - 15.0f;
				}

			}
		}
	}


	void RedBall::reset(bool gameOver) {
		if (gameOver) {
			_spawnCounter = _spawnDelay;
		} else {
			_spawnCounter = 100;
		}
		_enemy.setPosition(RED_BALL_START_POS);
		_drop = true;
		_fell = false;
		_jumpCounter = 0;
	}

	void RedBall::animate() {
		if (_jumpCounter > 0 || _drop) {
			_enemy.setTextureRect(RED_BALL_JUMP);
		} else {
			_enemy.setTextureRect(RED_BALL);
		}
	}


}