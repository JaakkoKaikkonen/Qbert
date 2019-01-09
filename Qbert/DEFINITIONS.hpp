#pragma once

#define WINDOW_TITLE "Q*bert"

#define SCREEN_WIDTH 550
#define SCREEN_HEIGHT 550

#define TOP_ICON_FILEPATH "Resources/Images/Qbert_icon.png"

#define FONT_FILEPATH "Resources/Fonts/font.ttf"

#define BOX_TEXTURE_FILEPATH "Resources/Images/Boxes.png"
#define QBERT_TEXTURE_FILEPATH "Resources/Images/Qbert.png"
#define ENEMY_TEXTURE_FILEPATH "Resources/Images/Enemy.png"
#define PLAYER_TEXT_TEXTURE_FILEPATH "Resources/Images/Player_text.png"
#define HUD_ELEMENTS_FILEPATH "Resources/Images/HUD_elements.png"
#define SWEARING_TEXTURE_FILEPATH "Resources/Images/Swearing.png"
#define FLYING_DISC_TEXTURE_FILEPATH "Resources/Images/Flying_disc.png"

#define JUMP_SOUND_FILEPATH "Resources/Sounds/Jump1.ogg"
#define SWEAR_SOUND_FILEPATH "Resources/Sounds/Swear1.ogg"
#define LIFT_SOUND_FILEPATH "Resources/Sounds/Lift.ogg"
#define FALL_SOUND_FILEPATH "Resources/Sounds/Fall.ogg"
#define WIN_SOUND_FILEPATH "Resources/Sounds/Win.ogg"
#define SNAKE_JUMP_SOUND_FILEPATH "Resources/Sounds/Jump4.ogg"
#define SNAKE_FALL_SOUND_FILEPATH "Resources/Sounds/Snake_fall.ogg"
#define START_SOUND_FILEPATH "Resources/Sounds/Tune.ogg"
#define RED_BALL_JUMP_SOUND_FILEPATH "Resources/Sounds/Jump3.ogg"
#define SNAKE_EGG_JUMP_SOUND_FILEPATH "Resources/Sounds/Jump2.ogg"

#define PI 3.1415926

#define TILESIZE 64 

#define AMOUNT_OF_BOXES 28

#define AMOUNT_OF_RED_BALLS 2

#define QBERT_START_POS sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.21f)

#define SNAKE_START_POS sf::Vector2f(SCREEN_WIDTH / 2 - TILESIZE / 2, SCREEN_HEIGHT * 0.05f)
#define RED_BALL_START_POS sf::Vector2f(SCREEN_WIDTH / 2 + TILESIZE / 2, SCREEN_HEIGHT * 0.05f)

#define FLYING_DISC_GOAL sf::Vector2f(SCREEN_WIDTH / 2, 65)

#define FLYING_DISC_POSITION_01 sf::Vector2f(110, 295)
#define FLYING_DISC_POSITION_02 sf::Vector2f(438, 295)

#define FALL_SPEED 6.0f

enum class Dir { Down, Right, Up, Left };

#define RED_BOX sf::IntRect(0, 0, 32, 32)
#define YELLOW_BOX sf::IntRect(0, 32, 32, 32)
#define BLUE_BOX sf::IntRect(0, 64, 32, 32)

#define CHANGE_TO_BOX_RED sf::IntRect(65, 4, 14, 12)
#define CHANGE_TO_BOX_YELLOW sf::IntRect(65, 36, 14, 12)
#define CHANGE_TO_BOX_BLUE sf::IntRect(65, 68, 14, 12)



#define QBERT_BACK_RIGHT sf::IntRect(0, 0, 16, 16)
#define QBERT_BACK_RIGHT_JUMP sf::IntRect(16, 0, 16, 16)

#define QBERT_BACK_LEFT sf::IntRect(32, 0, 16, 16)
#define QBERT_BACK_LEFT_JUMP sf::IntRect(48, 0, 16, 16)

#define QBERT_FRONT_RIGHT sf::IntRect(64, 0, 16, 16)
#define QBERT_FRONT_RIGHT_JUMP sf::IntRect(80, 0, 16, 16)

#define QBERT_FRONT_LEFT sf::IntRect(96, 0, 16, 16)
#define QBERT_FRONT_LEFT_JUMP sf::IntRect(112, 0, 16, 16)


#define SNAKE_EGG sf::IntRect(64, 0, 16, 13)
#define SNAKE_EGG_JUMP sf::IntRect(80, 0, 16, 13)

#define SNAKE_BACK_RIGHT sf::IntRect(0, 13, 16, 32)
#define SNAKE_BACK_RIGHT_JUMP sf::IntRect(16, 13, 16, 32)

#define SNAKE_BACK_LEFT sf::IntRect(32, 13, 16, 32)
#define SNAKE_BACK_LEFT_JUMP sf::IntRect(48, 13, 16, 32)

#define SNAKE_FRONT_RIGHT sf::IntRect(64, 13, 16, 32)
#define SNAKE_FRONT_RIGHT_JUMP sf::IntRect(80, 13, 16, 32)

#define SNAKE_FRONT_LEFT sf::IntRect(96, 13, 16, 32)
#define SNAKE_FRONT_LEFT_JUMP sf::IntRect(112, 13, 16, 32)


#define RED_BALL sf::IntRect(2, 3, 13, 10)
#define RED_BALL_JUMP sf::IntRect(18, 3, 13, 10)


#define PLAYER_TEXT_01 sf::IntRect(0, 0, 51, 7)
#define PLAYER_TEXT_02 sf::IntRect(0, 8, 51, 7)
#define PLAYER_TEXT_03 sf::IntRect(0, 16, 51, 7)
#define PLAYER_TEXT_04 sf::IntRect(0, 24, 51, 7)
#define PLAYER_TEXT_05 sf::IntRect(0, 32, 51, 7)
#define PLAYER_TEXT_06 sf::IntRect(0, 40, 51, 7)

#define PLAYER_INDEX_YELLOW sf::IntRect(0, 0, 8, 11)
#define PLAYER_INDEX_BLUE sf::IntRect(8, 0, 8, 11)
#define PLAYER_INDEX_RED sf::IntRect(16, 0, 8, 11)

#define ARROW_RIGHT sf::IntRect(24, 1, 7, 7)
#define ARROW_LEFT sf::IntRect(33, 1, 7, 7)


#define FLYING_DISC_01 sf::IntRect(0, 0, 16, 10)
#define FLYING_DISC_02 sf::IntRect(16, 0, 16, 10)
#define FLYING_DISC_03 sf::IntRect(32, 0, 16, 10)
#define FLYING_DISC_04 sf::IntRect(48, 0, 16, 10)