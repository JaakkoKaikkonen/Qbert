#include "Qbert.hpp"


namespace engine {

	Qbert::Qbert(gameDataRef data)
		: _data(data), _Qbert(_data->assets.getTexture("Qbert"), QBERT_FRONT_LEFT_JUMP), _swearSprite(_data->assets.getTexture("Swearing"))
	{	
		_Qbert.setOrigin(_Qbert.getGlobalBounds().width / 2, _Qbert.getGlobalBounds().height / 2);
		_Qbert.setScale(2.0f, 2.0f);
		_Qbert.setPosition(QBERT_START_POS);

		_swearSprite.setOrigin(_swearSprite.getGlobalBounds().width / 2, _swearSprite.getGlobalBounds().height / 2);
		_swearSprite.setScale(2.0f, 2.0f);
	}


	void Qbert::move(Dir dir) {
		if (_jumpTimer > 30) {
			_jumpTimer = 0;
			_jumpCounter = 24;
			_dir = dir;

			x = 0;
			y = 0;
			
			_jumpStartPos = _Qbert.getPosition();
		}
	}

	void Qbert::update() {

		_jumpTimer++;

		if (_swear) {

			_swearSprite.setPosition(_Qbert.getPosition().x + 8.0f, _Qbert.getPosition().y - TILESIZE * 0.7f);

		} else if (_jumpCounter > 0) {
		
			switch (_dir) {
			case Dir::Up:
				x += 32.0f/24.0f;
				y = 1 / 12.0f * pow(x - 25, 2) - 48.0f - 49.0f/12.0f;
				_Qbert.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
				break;
			case Dir::Down:
				x -= 32.0f/24.0f;
				y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(-x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
				_Qbert.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
				break;
			case Dir::Right:
				x += 32.0f/24.0f;
				y = ((4.0f + sqrt(7.0f)) / 64.0f) * pow(x - ((16.0f*((sqrt(7.0f) - 1.0f)) / 3.0f)), 2) - 8.0f;
				_Qbert.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
				break;
			case Dir::Left:
				x -= 32.0f/24.0f;
				y = 1 /12.0f * pow(-x - 25, 2) - 48.0f - 49.0f/12.0f;
				_Qbert.setPosition(_jumpStartPos.x + x, _jumpStartPos.y + y);
			}

			_jumpCounter--;


			//y = 1 / 12.0f * pow(x - 25, 2) - 48.0f - 49.0f / 12.0f;
			//y = 1 / 12.0f * pow(x - 8, 2);
		} 
	}

	bool Qbert::land() {
		if (_jumpCounter == 1) {
			return true;
		} else {
			return false;
		}
	}

	void Qbert::fall() {
		_Qbert.move(0.0f, FALL_SPEED);
	}

	void Qbert::reset() {
		_Qbert.setPosition(QBERT_START_POS);
		_swear = false;
		_fell = false;
		_fellFromLastRow = false;
		_dir = Dir::Down;
		_jumpCounter = 0;
	}

	void Qbert::setPos(sf::Vector2f pos) {
		_Qbert.setPosition(pos);
	}

	void Qbert::draw() {

		this->animate();

		_data->window.draw(_Qbert);

		if (_swear) {
			_data->window.draw(_swearSprite);
		}

	}

	void Qbert::animate() {
		if (_jumpCounter > 0) {
			switch (_dir) {
			case Dir::Up:
				_Qbert.setTextureRect(QBERT_BACK_RIGHT_JUMP);
				break;
			case Dir::Down:
				_Qbert.setTextureRect(QBERT_FRONT_LEFT_JUMP);
				break;
			case Dir::Right:
				_Qbert.setTextureRect(QBERT_FRONT_RIGHT_JUMP);
				break;
			case Dir::Left:
				_Qbert.setTextureRect(QBERT_BACK_LEFT_JUMP);
			}
		} else {
			switch (_dir) {
			case Dir::Up:
				_Qbert.setTextureRect(QBERT_BACK_RIGHT);
				break;
			case Dir::Down:
				_Qbert.setTextureRect(QBERT_FRONT_LEFT);
				break;
			case Dir::Right:
				_Qbert.setTextureRect(QBERT_FRONT_RIGHT);
				break;
			case Dir::Left:
				_Qbert.setTextureRect(QBERT_BACK_LEFT);
			}
		}
	}


}