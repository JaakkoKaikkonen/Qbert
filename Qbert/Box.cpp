#include "Box.hpp"

namespace Game {

	Box::Box(gameDataRef data, sf::IntRect sprite, float x, float y)
		: _data(data), _box(_data->assets.getTexture("Boxes"), sprite), _changeColorAnimation(_box, _changeColorAnimationFrames, 3, 0.25f)
	{
		_box.setOrigin(_box.getGlobalBounds().width / 2, _box.getGlobalBounds().height / 2);
		_box.setScale(2.0f, 2.0f);
		_box.setPosition(x, y);
	}


	bool Box::contains(sf::Vector2f point) {
		return _box.getGlobalBounds().contains(point);
	}

	void Box::animation() {
		_changeColorAnimation.animate();
	}

	void Box::reset() {
		_box.setTextureRect(BLUE_BOX);
	}

	void Box::draw() {
		_data->window.draw(_box);
	}


	bool Box::changeColor() {
		if (_box.getTextureRect() == BLUE_BOX) {
			_box.setTextureRect(YELLOW_BOX);
			return true;
		} else {
			return false;
		}
	}

}