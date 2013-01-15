#include "../BreakoutApp.hpp"

BreakoutApp::BreakoutApp(QWidget *parent)
	: super(parent), frame(&world)
{
	connect(&this->timer, SIGNAL(timeout()), this, SLOT(step()));
	this->timer.start(1000/60);

	gettimeofday(&this->last_step, NULL);

	this->frame.setFocusPolicy(Qt::StrongFocus);
	this->setCentralWidget(&this->frame);
	this->showFullScreen();
}

void BreakoutApp::step()
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