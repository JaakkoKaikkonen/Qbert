#include "Game.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"


namespace Game {

	Game::Game(int width, int height, std::string title) {

		sf::Image icon;
		icon.loadFromFile(TOP_ICON_FILEPATH);

		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		data->window.setPosition(sf::Vector2i(500, 200));

		data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		//Seed rng
		srand((unsigned int)time(NULL));

		//Load Resources ----------------------------------------------------------------------

		//Textures
		data->assets.loadTexture("Qbert", QBERT_TEXTURE_FILEPATH);
		data->assets.loadTexture("Boxes", BOX_TEXTURE_FILEPATH);
		data->assets.loadTexture("Enemy", ENEMY_TEXTURE_FILEPATH);
		data->assets.loadTexture("Player_text", PLAYER_TEXT_TEXTURE_FILEPATH);
		data->assets.loadTexture("HUD", HUD_ELEMENTS_FILEPATH);
		data->assets.loadTexture("Swearing", SWEARING_TEXTURE_FILEPATH);
		data->assets.loadTexture("Flying_disc", FLYING_DISC_TEXTURE_FILEPATH);

		//Sounds
		data->assets.loadSound("Jump", JUMP_SOUND_FILEPATH);
		data->assets.loadSound("Swear", SWEAR_SOUND_FILEPATH);
		data->assets.loadSound("Lift", LIFT_SOUND_FILEPATH);
		data->assets.loadSound("Fall", FALL_SOUND_FILEPATH);
		data->assets.loadSound("Win", WIN_SOUND_FILEPATH);
		data->assets.loadSound("Snake_fall", SNAKE_FALL_SOUND_FILEPATH);
		data->assets.loadSound("Start", START_SOUND_FILEPATH);
		data->assets.loadSound("Snake_egg_jump", SNAKE_EGG_JUMP_SOUND_FILEPATH);
		data->assets.loadSound("Snake_jump", SNAKE_JUMP_SOUND_FILEPATH);
		data->assets.loadSound("Red_ball_jump", RED_BALL_JUMP_SOUND_FILEPATH);

		//Fonts
		data->assets.loadFont("Font", FONT_FILEPATH);

		//-------------------------------------------------------------------------------------

		data->state = new GameState(data);
		data->state->init();

		this->run();
	}

	void Game::run() {
		float newTime, frameTime;

		float currentTime = clock.getElapsedTime().asSeconds();

		float accumulator = dt;


		while (this->data->window.isOpen()) {

			newTime = clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			currentTime = newTime;

			if (frameTime > 0.15f) {
				frameTime = 0.15f;
			}

			accumulator += frameTime;

			while (accumulator >= dt)
			{
				data->state->handleInput();
				data->state->update();

				data->state->draw();

				accumulator -= dt;
			}

		}


	}


}