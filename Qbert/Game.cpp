#include "Game.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"


namespace Game {

	Game::Game(int width, int height, std::string title) {

		sf::Image icon;
		icon.loadFromFile(TOP_ICON_FILEPATH);

		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		//_data->window.setVerticalSyncEnabled(true);
		//_data->window.setFramerateLimit(60);

		_data->window.setPosition(sf::Vector2i(500, 200));

		_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		//Seed rng
		srand(time(NULL));

		//Load Resources ----------------------------------------------------------------------

		//Textures
		_data->assets.loadTexture("Qbert", QBERT_TEXTURE_FILEPATH);
		_data->assets.loadTexture("Boxes", BOX_TEXTURE_FILEPATH);
		_data->assets.loadTexture("Enemy", ENEMY_TEXTURE_FILEPATH);
		_data->assets.loadTexture("Player_text", PLAYER_TEXT_TEXTURE_FILEPATH);
		_data->assets.loadTexture("HUD", HUD_ELEMENTS_FILEPATH);
		_data->assets.loadTexture("Swearing", SWEARING_TEXTURE_FILEPATH);
		_data->assets.loadTexture("Flying_disc", FLYING_DISC_TEXTURE_FILEPATH);

		//Sounds
		_data->assets.loadSound("Jump", JUMP_SOUND_FILEPATH);
		_data->assets.loadSound("Swear", SWEAR_SOUND_FILEPATH);
		_data->assets.loadSound("Lift", LIFT_SOUND_FILEPATH);
		_data->assets.loadSound("Fall", FALL_SOUND_FILEPATH);
		_data->assets.loadSound("Win", WIN_SOUND_FILEPATH);
		_data->assets.loadSound("Snake_fall", SNAKE_FALL_SOUND_FILEPATH);
		_data->assets.loadSound("Start", START_SOUND_FILEPATH);
		_data->assets.loadSound("Snake_egg_jump", SNAKE_EGG_JUMP_SOUND_FILEPATH);
		_data->assets.loadSound("Snake_jump", SNAKE_JUMP_SOUND_FILEPATH);
		_data->assets.loadSound("Red_ball_jump", RED_BALL_JUMP_SOUND_FILEPATH);

		//Fonts
		_data->assets.loadFont("Font", FONT_FILEPATH);

		//-------------------------------------------------------------------------------------

		_data->machine.addState(stateRef(new GameState(_data)), true);

		this->run();
	}

	void Game::run() {
		float newTime, frameTime;

		float currentTime = this->_clock.getElapsedTime().asSeconds();

		float accumulator = dt;

		float interpolation = 0.0f;


		while (this->_data->window.isOpen()) {

			this->_data->machine.processStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			currentTime = newTime;

			if (frameTime > 0.15f) {
				frameTime = 0.15f;
			}

			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.getActiveState()->handleInput();
				this->_data->machine.getActiveState()->update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;

			this->_data->machine.getActiveState()->draw(interpolation);


			//std::cout << 1 / frameTime << std::endl;
		}


	}


}