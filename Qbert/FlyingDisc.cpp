#include "FlyingDisc.hpp"

namespace Game {

	FlyingDisc::FlyingDisc(gameDataRef data, sf::Vector2f startPos)
		: _data(data), _disc(_data->assets.getTexture("Flying_disc"), FLYING_DISC_01), _discAnimation(_disc, _discAnimationFrames, 4, 0.25f)
	{
		_disc.setOrigin(_disc.getGlobalBounds().width / 2, _disc.getGlobalBounds().height / 2);
		_disc.setScale(2.0f, 2.0f);
		_disc.setPosition(startPos);

	}


	bool FlyingDisc::move() {
		if (_disc.getPosition().y <= FLYING_DISC_GOAL.y) {
			_waitCounter--;
			if (_waitCounter <= 0) {
				_disc.setPosition(0.0f, 0.0f);
				_done = true;
				return false;
			}
		} else {
			if (_upCounter > 0) {
				_upCounter--;
				_disc.move(0.0f, -2.0f);
			} else if (_upCounter == 0) {
				_upCounter--;
				_moveVector = (FLYING_DISC_GOAL - _disc.getPosition()) / 100.0f;
			} else {
				_disc.move(_moveVector);
			}
		}
		return true;
	}

	bool FlyingDisc::contains(sf::Vector2f point) {
		return _disc.getGlobalBounds().contains(point);
	}

	void FlyingDisc::reset(sf::Vector2f startPos) {
		_disc.setPosition(startPos);
		_done = false;
		_upCounter = 20;
		_waitCounter = 30;
	}

	void FlyingDisc::draw() {
		if (!_done) {
			_discAnimation.animate();
			_data->window.draw(_disc);
		}
	}

	

}