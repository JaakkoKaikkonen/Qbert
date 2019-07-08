#include "Enemy.hpp"
#include "Collision.hpp"

namespace Game {

	Enemy::Enemy(gameDataRef data, int spawnDelay)
		: data(data)
	{
		this->spawnDelay = spawnDelay;
		spawnCounter = spawnDelay;
	}


	bool Enemy::land() {
		if (jumpCounter == 1) {
			return true;
		} else {
			return false;
		}
	}


	void Enemy::fall() {
		enemy.move(0.0f, FALL_SPEED);
		if (enemy.getPosition().y > SCREEN_HEIGHT*1.2f) {
			this->reset(false);
		}
	}


	void Enemy::draw() {
		if (spawnCounter <= 0) {
			this->animate();
			data->window.draw(enemy);
		}
	}


}