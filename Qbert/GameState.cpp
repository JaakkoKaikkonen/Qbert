#include <string>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "Collision.hpp"


namespace Game {

	GameState::GameState(gameDataRef data)
		: data(data),
		  hud(data)
	{
	}

	void GameState::init() {

		data->assets.getSound("Start").play();

		int rowSize = 1;
		for (int i = 0; i < boxes.size();) {
			for (int j = 0; j < rowSize;) {
				boxes[i] = new Box(data, BLUE_BOX, 
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

		qbert = new Qbert(data);

		snake = new Snake(data, &hud, 70);

		redBalls[0] = new RedBall(data, 200);
		redBalls[1] = new RedBall(data, 400);

		discs[0] = new FlyingDisc(data, FLYING_DISC_POSITION_01);
		discs[1] = new FlyingDisc(data, FLYING_DISC_POSITION_02);
		
	}

	void GameState::handleInput() {
		sf::Event event;
		while (data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				data->window.close();
			}
		}

		if (!qbert->getSwear() && !won && !onDisc[0] && !onDisc[1]) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				qbert->move(Dir::Up);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				qbert->move(Dir::Down);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				qbert->move(Dir::Right);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				qbert->move(Dir::Left);
			}
		}

	}

	void GameState::update() {

		if (won) {

			this->win();

		} else {

			if (!qbert->getSwear()) {

				if (qbert->getFell()) {

					qbert->fall();

					if (qbert->getPos().y > SCREEN_HEIGHT*1.5f) {
						this->reset();
					}

				} else {

					this->updateDiscs();

					qbert->update();

					this->checkMapCollision();

					this->checkEnemyCollision();

				}

				this->updateEnemies();

			} else if (swearCounter <= 0) {

				this->reset();

			} else {

				swearCounter--;

			}

			hud.update();
			
		}

	}

	void GameState::draw() {

		data->window.clear(backGroundColor);

		discs[0]->draw();
		discs[1]->draw();

		if (snake->getFell()) {
			snake->draw();
		}

		if (qbert->getFell() && !qbert->getFellFromLastRow()) {
			qbert->draw();
			for (int i = 0; i < boxes.size(); i++) {
				boxes[i]->draw();
			}
		} else {
			for (int i = 0; i < boxes.size(); i++) {
				boxes[i]->draw();
			}
			qbert->draw();
		}


		if (!snake->getFell()) {
			snake->draw();
		}

		redBalls[0]->draw();
		redBalls[1]->draw();


		hud.draw();

		data->window.display();
	}




	void GameState::newBoxHit() {
		boxesHit++;
		hud.addToScore(25);
		if (boxesHit == AMOUNT_OF_BOXES) {
			data->assets.getSound("Win").play();
			won = true;
		}
	}


	void GameState::updateDiscs() {
		for (int i = 0; i < 2; i++) {
			if (onDisc[i]) {
				if (discs[i]->move()) {
					if (backGroundColor.g > 0) {
						backGroundColor.g -= 25;
					}
					qbert->setPos(discs[i]->getPos() - sf::Vector2f(0.0f, 17.0f));
				} else {
					qbert->setPos(qbert->getPos() + sf::Vector2f(0.0f, 4.0f));
					if (qbert->getPos().y > QBERT_START_POS.y) {
						qbert->setPos(QBERT_START_POS);
						if (boxes[0]->changeColor()) {
							this->newBoxHit();
						}
						onDisc[i] = false;
					}
				}
			}
		}
	}

	void GameState::checkMapCollision() {
		if (qbert->land()) {
			bool collided = false;
			for (int i = 0; i < boxes.size(); i++) {
				if (boxes[i]->contains(qbert->getPos() + sf::Vector2f(0.0f, qbert->getGlobalBounds().height*0.75f))) {
					if (boxes[i]->changeColor()) {
						this->newBoxHit();
					}
					data->assets.getSound("Jump").play();
					collided = true;
					break;
				}
			}
			for (int i = 0; i < 2; i++) {
				if (discs[i]->contains(qbert->getPos() + sf::Vector2f(0.0f, 30.0f))) {
					data->assets.getSound("Lift").play();
					onDisc[i] = true;
					backGroundColor.g = 250;
					qbert->update();
					oldQbertPos = qbert->getPos();
					collided = true;
				}
			}
			if (collided == false) {
				qbert->setFell();
				data->assets.getSound("Fall").play();
				if (qbert->getPos().y > boxes[boxes.size() - 1]->getPos().y) {
					qbert->setFellFromLastRow();
				}
			}
		}
	}

	void GameState::checkEnemyCollision() {
		if (Collision::checkSpriteCollision(qbert->getSprite(), 1.0f, snake->getSprite(), 0.2f) ||
			Collision::checkSpriteCollision(qbert->getSprite(), 1.0f, redBalls[0]->getSprite(), 0.15f) ||
			Collision::checkSpriteCollision(qbert->getSprite(), 1.0f, redBalls[1]->getSprite(), 0.15f)) {
			qbert->setSwear();
			data->assets.getSound("Swear").play();
			qbert->update();
			swearCounter = 100;
		}
	}

	void GameState::updateEnemies() {
		if (onDisc[0] || onDisc[1]) {
			snake->update(boxes, oldQbertPos);
		} else {
			snake->update(boxes, qbert->getPos());
		}
		redBalls[0]->update(boxes, qbert->getPos());
		redBalls[1]->update(boxes, qbert->getPos());

		if (snake->land() && !snake->getFell()) {
			bool collided = false;
			for (int i = 0; i < boxes.size(); i++) {
				if (boxes[i]->contains(snake->getPos() + sf::Vector2f(0.0f, 10.0f))) {
					if (snake->getEgg()) {
						data->assets.getSound("Snake_egg_jump").play();
					} else {
						data->assets.getSound("Snake_jump").play();
					}
					collided = true;
					break;
				}
			}
			if (collided == false) {
				data->assets.getSound("Snake_fall").play();
				snake->setFell();
			}
		}

		for (int i = 0; i < AMOUNT_OF_RED_BALLS; i++) {
			if (redBalls[i]->land()) {
				bool collided = false;
				for (int j = 0; j < boxes.size(); j++) {
					if (boxes[j]->contains(redBalls[i]->getPos() + sf::Vector2f(0.0f, 15.0f))) {
						data->assets.getSound("Red_ball_jump").play();
						collided = true;
						break;
					}
				}
				if (collided == false) {
					redBalls[i]->setFell();
				}
			}
		}
	}


	void GameState::win() {
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i]->animation();
		}
		hud.win();
		winTimer--;
		if (winTimer <= 0) {
			this->reset();
		}
	}


	void GameState::reset() {
		qbert->reset();
		snake->reset(true);
		redBalls[0]->reset(true);
		redBalls[1]->reset(true);
		discs[0]->reset(FLYING_DISC_POSITION_01);
		discs[1]->reset(FLYING_DISC_POSITION_02);
		hud.reset();
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i]->reset();
		}
		boxesHit = 0;
		onDisc[0] = false;
		onDisc[1] = false;
		won = false;
		winTimer = 150;
	}

}


