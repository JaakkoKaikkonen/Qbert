#include "Box.hpp"

namespace Game {

	Box::Box(gameDataRef data, sf::IntRect sprite, float x, float y)
		: data(data),
		  box(this->data->assets.getTexture("Boxes"), sprite),
		  changeColorAnimation(box, changeColorAnimationFrames, 3, 0.25f)
	{
		box.setOrigin(box.getGlobalBounds().width / 2, box.getGlobalBounds().height / 2);
		box.setScale(2.0f, 2.0f);
		box.setPosition(x, y);
	}


	bool Box::contains(sf::Vector2f point) {
		return box.getGlobalBounds().contains(point);
	}

	void Box::animation() {
		changeColorAnimation.animate();
	}

	void Box::reset() {
		box.setTextureRect(BLUE_BOX);
	}

	void Box::draw() {
		data->window.draw(box);
	}


	bool Box::changeColor() {
		if (box.getTextureRect() == BLUE_BOX) {
			box.setTextureRect(YELLOW_BOX);
			return true;
		} else {
			return false;
		}
	}

}