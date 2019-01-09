#include "HUD.hpp"

namespace engine {

	HUD::HUD(gameDataRef data)
		: _data(data), _playerText(_data->assets.getTexture("Player_text"), PLAYER_TEXT_01), _playerTextAnimation(_playerText, _playerTextAnimationFrames, 6, 0.6f),
		  _playerIndex(_data->assets.getTexture("HUD"), PLAYER_INDEX_YELLOW), _playerIndexAnimation(_playerIndex, _playerIndexAnimationFrames, 3, 0.25f),
		  _score("0", _data->assets.getFont("Font"), 20),
		  _changeTo("CHANGE TO:", _data->assets.getFont("Font"), 11), _changeToBox(_data->assets.getTexture("Boxes"), CHANGE_TO_BOX_YELLOW), 
		  _changeToBoxAnimation(_changeToBox, _changeToBoxAnimationFrames, 3, 0.25f)
	{
		_playerText.setScale(2.0f, 2.0f);
		_playerText.setPosition(20.0f, 20.0f);

		_playerIndex.setScale(2.0f, 2.0f);
		_playerIndex.setPosition(132.0f, 15.0f);

		_score.setFillColor(sf::Color(255, 119, 0));
		_score.setPosition(20.0f, 40.0f);

		_changeTo.setFillColor(sf::Color::Red);
		_changeTo.setPosition(20.0f, 83.0f);

		_changeToBox.setScale(2.0f, 2.0f);
		_changeToBox.setPosition(58.0f, 102.0f);


		for (int i = 0; i < 4; i++) {
			_arrows[i].setTexture(_data->assets.getTexture("HUD"));
			_arrows[i].setTextureRect(i % 2 == 0 ? ARROW_RIGHT : ARROW_LEFT);
			_arrows[i].setScale(2.0f, 2.0f);
			if (i % 2 == 0) {
				_arrows[i].setPosition(20.0f + 9.0f*i, 106.0f);
			} else {
				_arrows[i].setPosition(118.0f - 9.0f*i, 106.0f);
			}
		}
	}


	void HUD::addToScore(int score) {
		_score.setString(std::to_string(std::stoi((std::string)_score.getString()) + score));
	}

	void HUD::update() {
		_playerTextAnimation.animate();

		_arrowTimer++;
		if (_arrowTimer > 15) {
			if (_arrowCount == 4) {
				_arrowCount = 0;
			} else {
				_arrowCount += 2;
			}
			_arrowTimer = 0;
		}
	}

	void HUD::win() {
		_arrowCount = 4;
		_changeToBoxAnimation.animate();
		_playerIndexAnimation.animate();
	}


	void HUD::reset() {
		_score.setString("0");
		_changeToBox.setTextureRect(CHANGE_TO_BOX_YELLOW);
		_playerIndex.setTextureRect(PLAYER_INDEX_YELLOW);
	}

	void HUD::draw() {

		_data->window.draw(_playerText);

		_data->window.draw(_playerIndex);

		_data->window.draw(_score);

		_data->window.draw(_changeTo);

		_data->window.draw(_changeToBox);


		for (int i = 0; i < _arrowCount; i++) {
			_data->window.draw(_arrows[i]);
		}

	}


}