#include "../BreakoutGame.hpp"

BreakoutGame::BreakoutGame(string level_filename_path, Player *player_1, Player *player_2, QWidget *parent)
	: super(parent), world(level_filename_path, player_1, player_2), frame(&world)
{
	connect(&this->timer, SIGNAL(timeout()), this, SLOT(step()));
	this->timer.start(1000/60);

	gettimeofday(&this->last_step, NULL);

	this->frame.setFocusPolicy(Qt::StrongFocus);
	this->setCentralWidget(&this->frame);
	this->showFullScreen();
}

void BreakoutGame::step()
{
	struct timeval now;
	double dt;
	long secs, usecs;

	gettimeofday(&now, NULL);

	secs = now.tv_sec - this->last_step.tv_sec;
	usecs = now.tv_usec - this->last_step.tv_usec;
	dt = (secs + usecs/(1000.0 * 1000.0));

	this->world.step(dt);
	this->frame.update();

	this->last_step = now;
}