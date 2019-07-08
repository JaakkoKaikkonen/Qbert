#include "FlyingDisc.hpp"

namespace Game {

	FlyingDisc::FlyingDisc(gameDataRef data, sf::Vector2f startPos)
		: data(data),
		  disc(this->data->assets.getTexture("Flying_disc"), FLYING_DISC_01),
		  discAnimation(disc, discAnimationFrames, 4, 0.25f)
	{
		disc.setOrigin(disc.getGlobalBounds().width / 2, disc.getGlobalBounds().height / 2);
		disc.setScale(2.0f, 2.0f);
		disc.setPosition(startPos);
	}


	bool FlyingDisc::move() {
		if (disc.getPosition().y <= FLYING_DISC_GOAL.y) {
			waitCounter--;
			if (waitCounter <= 0) {
				disc.setPosition(0.0f, 0.0f);
				done = true;
				return false;
			}
		} else {
			if (upCounter > 0) {
				upCounter--;
				disc.move(0.0f, -2.0f);
			} else if (upCounter == 0) {
				upCounter--;
				moveVector = (FLYING_DISC_GOAL - disc.getPosition()) / 100.0f;
			} else {
				disc.move(moveVector);
			}
		}
		return true;
	}

	bool FlyingDisc::contains(sf::Vector2f point) {
		return disc.getGlobalBounds().contains(point);
	}

	void FlyingDisc::reset(sf::Vector2f startPos) {
		disc.setPosition(startPos);
		done = false;
		upCounter = 20;
		waitCounter = 30;
	}

	void FlyingDisc::draw() {
		if (!done) {
			discAnimation.animate();
			data->window.draw(disc);
		}
	}

	

}