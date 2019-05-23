#include <string>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "Collision.hpp"


namespace Game {

	GameState::GameState(gameDataRef data)
		: _data(data), _hud(data)
	{
	}

	void GameState::init() {

		_data->assets.getSound("Start").play();

		int rowSize = 1;
		for (int i = 0; i < _boxes.size();) {
			for (int j = 0; j < rowSize;) {
				_boxes[i] = new Box(_data, BLUE_BOX, 
								    SCREEN_WIDTH / 2 + j * TILESIZE - rowSize * TILESIZE/2 + TILESIZE / 2, //x
									SCREEN_HEIGHT * 0.18f + rowSize * TILESIZE*0.75f); //y
				j++;
				i++;
				if (j == rowSize) {
					rowSize++;
					break;
				}
			}
		}

		_Qbert = new Qbert(_data);

		_snake = new Snake(_data, &_hud, 70);

		_redBalls[0] = new RedBall(_data, 200);
		_redBalls[1] = new RedBall(_data, 400);

		_discs[0] = new FlyingDisc(_data, FLYING_DISC_POSITION_01);
		_discs[1] = new FlyingDisc(_data, FLYING_DISC_POSITION_02);
		
	}

	void GameState::handleInput() {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}

		if (!_Qbert->getSwear() && !_win && !_onDisc[0] && !_onDisc[1]) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				_Qbert->move(Dir::Up);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				_Qbert->move(Dir::Down);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				_Qbert->move(Dir::Right);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				_Qbert->move(Dir::Left);
			}
		}

	}

	void GameState::update(float dt) {

		if (_win) {

			this->win();

		} else {

			if (!_Qbert->getSwear()) {

				if (_Qbert->fell()) {

					_Qbert->fall();

					if (_Qbert->getPos().y > SCREEN_HEIGHT*1.5f) {
						this->reset();
					}

				} else {

					this->updateDiscs();

					_Qbert->update();

					this->checkMapCollision();

					this->checkEnemyCollision();

				}

				this->updateEnemies();

			} else if (_swearCounter <= 0) {

				this->reset();

			} else {

				_swearCounter--;

			}

			_hud.update();
			
		}

	}

	void GameState::draw(float interpolation) {

		_data->window.clear(_backGroundColor);

		_discs[0]->draw();
		_discs[1]->draw();

		if (_snake->fell()) {
			_snake->draw();
		}

		if (_Qbert->fell() && !_Qbert->returnFellFromLastRow()) {
			_Qbert->draw();
			for (int i = 0; i < _boxes.size(); i++) {
				_boxes[i]->draw();
			}
		} else {
			for (int i = 0; i < _boxes.size(); i++) {
				_boxes[i]->draw();
			}
			_Qbert->draw();
		}


		if (!_snake->fell()) {
			_snake->draw();
		}

		_redBalls[0]->draw();
		_redBalls[1]->draw();


		_hud.draw();

		_data->window.display();
	}




	void GameState::newBoxHit() {
		_boxesHit++;
		_hud.addToScore(25);
		if (_boxesHit == AMOUNT_OF_BOXES) {
			_data->assets.getSound("Win").play();
			_win = true;
		}
	}


	void GameState::updateDiscs() {
		for (int i = 0; i < 2; i++) {
			if (_onDisc[i]) {
				if (_discs[i]->move()) {
					if (_backGroundColor.g > 0) {
						_backGroundColor.g -= 25;
					}
					_Qbert->setPos(_discs[i]->getPos() - sf::Vector2f(0.0f, 17.0f));
				} else {
					_Qbert->setPos(_Qbert->getPos() + sf::Vector2f(0.0f, 4.0f));
					if (_Qbert->getPos().y > QBERT_START_POS.y) {
						_Qbert->setPos(QBERT_START_POS);
						if (_boxes[0]->changeColor()) {
							this->newBoxHit();
						}
						_onDisc[i] = false;
					}
				}
			}
		}
	}

	void GameState::checkMapCollision() {
		if (_Qbert->land()) {
			bool collided = false;
			for (int i = 0; i < _boxes.size(); i++) {
				if (_boxes[i]->contains(_Qbert->getPos() + sf::Vector2f(0.0f, _Qbert->getGlobalBounds().height*0.75f))) {
					if (_boxes[i]->changeColor()) {
						this->newBoxHit();
					}
					_data->assets.getSound("Jump").play();
					collided = true;
					break;
				}
			}
			for (int i = 0; i < 2; i++) {
				if (_discs[i]->contains(_Qbert->getPos() + sf::Vector2f(0.0f, 30.0f))) {
					_data->assets.getSound("Lift").play();
					_onDisc[i] = true;
					_backGroundColor.g = 250;
					_Qbert->update();
					_oldQbertPos = _Qbert->getPos();
					collided = true;
				}
			}
			if (collided == false) {
				_Qbert->drop();
				_data->assets.getSound("Fall").play();
				if (_Qbert->getPos().y > _boxes[_boxes.size() - 1]->getPos().y) {
					_Qbert->fellFromLastRow();
				}
			}
		}
	}

	void GameState::checkEnemyCollision() {
		if (Collision::checkSpriteCollision(_Qbert->getSprite(), 1.0f, _snake->getSprite(), 0.2f) ||
			Collision::checkSpriteCollision(_Qbert->getSprite(), 1.0f, _redBalls[0]->getSprite(), 0.15f) ||
			Collision::checkSpriteCollision(_Qbert->getSprite(), 1.0f, _redBalls[1]->getSprite(), 0.15f)) {
			_Qbert->swear();
			_data->assets.getSound("Swear").play();
			_Qbert->update();
			_swearCounter = 100;
		}
	}

	void GameState::updateEnemies() {
		if (_onDisc[0] || _onDisc[1]) {
			_snake->update(_boxes, _oldQbertPos);
		} else {
			_snake->update(_boxes, _Qbert->getPos());
		}
		_redBalls[0]->update(_boxes, _Qbert->getPos());
		_redBalls[1]->update(_boxes, _Qbert->getPos());

		if (_snake->land() && !_snake->fell()) {
			bool collided = false;
			for (int i = 0; i < _boxes.size(); i++) {
				if (_boxes[i]->contains(_snake->getPos() + sf::Vector2f(0.0f, 10.0f))) {
					if (_snake->egg()) {
						_data->assets.getSound("Snake_egg_jump").play();
					} else {
						_data->assets.getSound("Snake_jump").play();
					}
					collided = true;
					break;
				}
			}
			if (collided == false) {
				_data->assets.getSound("Snake_fall").play();
				_snake->drop();
			}
		}

		for (int i = 0; i < AMOUNT_OF_RED_BALLS; i++) {
			if (_redBalls[i]->land()) {
				bool collided = false;
				for (int j = 0; j < _boxes.size(); j++) {
					if (_boxes[j]->contains(_redBalls[i]->getPos() + sf::Vector2f(0.0f, 15.0f))) {
						_data->assets.getSound("Red_ball_jump").play();
						collided = true;
						break;
					}
				}
				if (collided == false) {
					_redBalls[i]->drop();
				}
			}
		}
	}


	void GameState::win() {
		for (int i = 0; i < _boxes.size(); i++) {
			_boxes[i]->animation();
		}
		_hud.win();
		_winTimer--;
		if (_winTimer <= 0) {
			this->reset();
		}
	}


	void GameState::reset() {
		_Qbert->reset();
		_snake->reset(true);
		_redBalls[0]->reset(true);
		_redBalls[1]->reset(true);
		_discs[0]->reset(FLYING_DISC_POSITION_01);
		_discs[1]->reset(FLYING_DISC_POSITION_02);
		_hud.reset();
		for (int i = 0; i < _boxes.size(); i++) {
			_boxes[i]->reset();
		}
		_boxesHit = 0;
		_onDisc[0] = false;
		_onDisc[1] = false;
		_win = false;
		_winTimer = 150;
	}

}


