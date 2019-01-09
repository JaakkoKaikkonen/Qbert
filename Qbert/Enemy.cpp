#include "Enemy.hpp"
#include "Collision.hpp"

namespace engine {

	Enemy::Enemy(gameDataRef data, int spawnDelay)
		: _data(data)
	{
		_spawnDelay = spawnDelay;
		_spawnCounter = _spawnDelay;
	}


	bool Enemy::land() {
		if (_jumpCounter == 1) {
			return true;
		} else {
			return false;
		}
	}


	void Enemy::fall() {
		_enemy.move(0.0f, FALL_SPEED);
		if (_enemy.getPosition().y > SCREEN_HEIGHT*1.2f) {
			this->reset(false);
		}
	}


	void Enemy::draw() {
		if (_spawnCounter <= 0) {
			this->animate();
			_data->window.draw(_enemy);
		}
	}


}