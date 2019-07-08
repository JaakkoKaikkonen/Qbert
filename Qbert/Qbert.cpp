#include "Qbert.hpp"


namespace Game {

	Qbert::Qbert(gameDataRef data)
		: data(data),
		  qbert(this->data->assets.getTexture("Qbert"), QBERT_FRONT_LEFT_JUMP),
		  swearSprite(this->data->assets.getTexture("Swearing"))
	{	
		qbert.setOrigin(qbert.getGlobalBounds().width / 2, qbert.getGlobalBounds().height / 2);
		qbert.setScale(2.0f, 2.0f);
		qbert.setPosition(QBERT_START_POS);

		swearSprite.setOrigin(swearSprite.getGlobalBounds().width / 2, swearSprite.getGlobalBounds().height / 2);
		swearSprite.setScale(2.0f, 2.0f);
	}


	void Qbert::move(Dir dir) {
		if (jumpTimer > 30) {
			jumpTimer = 0;
			jumpCounter = 24;
			this->dir = dir;

			x = 0;
			y = 0;
			
			jumpStartPos = qbert.getPosition();
		}
	}

	void Qbert::update() {

		jumpTimer++;

		if (swear) {

			swearSprite.setPosition(qbert.getPosition().x + 8.0f, qbert.getPosition().y - TILESIZE * 0.7f);

		} else if (jumpCounter > 0) {
		
			switch (dir) {
			case Dir::Up:
				x += 32.0f/24.0f;
				y = 1 / 12.0f * pow(x - 25, 2) - 48.0f - 49.0f/12.0f;
				qbert.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
				break;
			case Dir::Down:
				x -= 32.0f/24.0f;
				y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(-x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
				qbert.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
				break;
			case Dir::Right:
				x += 32.0f/24.0f;
				y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
				qbert.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
				break;
			case Dir::Left:
				x -= 32.0f/24.0f;
				y = 1 /12.0f * pow(-x - 25, 2) - 48.0f - 49.0f/12.0f;
				qbert.setPosition(jumpStartPos.x + x, jumpStartPos.y + y);
			}

			jumpCounter--;


			//y = 1 / 12.0f * pow(x - 25, 2) - 48.0f - 49.0f / 12.0f;
			//y = 1 / 12.0f * pow(x - 8, 2);
		} 
	}

	bool Qbert::land() {
		if (jumpCounter == 1) {
			return true;
		} else {
			return false;
		}
	}

	void Qbert::fall() {
		qbert.move(0.0f, FALL_SPEED);
	}

	void Qbert::reset() {
		qbert.setPosition(QBERT_START_POS);
		swear = false;
		fell = false;
		fellFromLastRow = false;
		dir = Dir::Down;
		jumpCounter = 0;
	}

	void Qbert::setPos(sf::Vector2f pos) {
		qbert.setPosition(pos);
	}

	void Qbert::draw() {

		this->animate();

		data->window.draw(qbert);

		if (swear) {
			data->window.draw(swearSprite);
		}

	}

	void Qbert::animate() {
		if (jumpCounter > 0) {
			switch (dir) {
			case Dir::Up:
				qbert.setTextureRect(QBERT_BACK_RIGHT_JUMP);
				break;
			case Dir::Down:
				qbert.setTextureRect(QBERT_FRONT_LEFT_JUMP);
				break;
			case Dir::Right:
				qbert.setTextureRect(QBERT_FRONT_RIGHT_JUMP);
				break;
			case Dir::Left:
				qbert.setTextureRect(QBERT_BACK_LEFT_JUMP);
			}
		} else {
			switch (dir) {
			case Dir::Up:
				qbert.setTextureRect(QBERT_BACK_RIGHT);
				break;
			case Dir::Down:
				qbert.setTextureRect(QBERT_FRONT_LEFT);
				break;
			case Dir::Right:
				qbert.setTextureRect(QBERT_FRONT_RIGHT);
				break;
			case Dir::Left:
				qbert.setTextureRect(QBERT_BACK_LEFT);
			}
		}
	}


}