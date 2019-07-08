#include "HUD.hpp"

namespace Game {

	HUD::HUD(gameDataRef data)
		: data(data),
		  playerText(this->data->assets.getTexture("Player_text"), PLAYER_TEXT_01),
		  playerTextAnimation(playerText, playerTextAnimationFrames, 6, 0.6f),
		  playerIndex(this->data->assets.getTexture("HUD"), PLAYER_INDEX_YELLOW),
		  playerIndexAnimation(playerIndex, playerIndexAnimationFrames, 3, 0.25f),
		  score("0", this->data->assets.getFont("Font"), 20),
		  changeTo("CHANGE TO:", this->data->assets.getFont("Font"), 11),
		  changeToBox(this->data->assets.getTexture("Boxes"), CHANGE_TO_BOX_YELLOW), 
		  changeToBoxAnimation(changeToBox, changeToBoxAnimationFrames, 3, 0.25f)
	{
		playerText.setScale(2.0f, 2.0f);
		playerText.setPosition(20.0f, 20.0f);

		playerIndex.setScale(2.0f, 2.0f);
		playerIndex.setPosition(132.0f, 15.0f);

		score.setFillColor(sf::Color(255, 119, 0));
		score.setPosition(20.0f, 40.0f);

		changeTo.setFillColor(sf::Color::Red);
		changeTo.setPosition(20.0f, 83.0f);

		changeToBox.setScale(2.0f, 2.0f);
		changeToBox.setPosition(58.0f, 102.0f);


		for (int i = 0; i < 4; i++) {
			arrows[i].setTexture(this->data->assets.getTexture("HUD"));
			arrows[i].setTextureRect(i % 2 == 0 ? ARROW_RIGHT : ARROW_LEFT);
			arrows[i].setScale(2.0f, 2.0f);
			if (i % 2 == 0) {
				arrows[i].setPosition(20.0f + 9.0f*i, 106.0f);
			} else {
				arrows[i].setPosition(118.0f - 9.0f*i, 106.0f);
			}
		}
	}


	void HUD::addToScore(int score) {
		this->score.setString(std::to_string(std::stoi((std::string)this->score.getString()) + score));
	}

	void HUD::update() {
		playerTextAnimation.animate();

		arrowTimer++;
		if (arrowTimer > 15) {
			if (arrowCount == 4) {
				arrowCount = 0;
			} else {
				arrowCount += 2;
			}
			arrowTimer = 0;
		}
	}

	void HUD::win() {
		arrowCount = 4;
		changeToBoxAnimation.animate();
		playerIndexAnimation.animate();
	}


	void HUD::reset() {
		score.setString("0");
		changeToBox.setTextureRect(CHANGE_TO_BOX_YELLOW);
		playerIndex.setTextureRect(PLAYER_INDEX_YELLOW);
	}

	void HUD::draw() {

		data->window.draw(playerText);

		data->window.draw(playerIndex);

		data->window.draw(score);

		data->window.draw(changeTo);

		data->window.draw(changeToBox);


		for (int i = 0; i < arrowCount; i++) {
			data->window.draw(arrows[i]);
		}

	}


}