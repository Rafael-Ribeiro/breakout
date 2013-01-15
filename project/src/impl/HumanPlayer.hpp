#include "../HumanPlayer.hpp"

#include "../Keyboard.hpp"

HumanPlayer::HumanPlayer(Paddle *paddle, Qt::Key left_key, Qt::Key right_key)
	: super(paddle), left_key(left_key), right_key(right_key)
{
}

void HumanPlayer::step(const double &dt)
{
	bool key_left = Keyboard::get_instance()[this->left_key];
	bool key_right = Keyboard::get_instance()[this->right_key];

	if (key_left && !key_right)
		this->left();

	else if (key_right && !key_left)
		this->right();

	else
		this->stop();

}