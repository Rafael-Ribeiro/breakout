#include "../BreakoutApp.hpp"

BreakoutApp::BreakoutApp(QWidget *parent)
	: super(parent), layout(this), frame(&world)
{
	this->layout.addWidget(&this->frame);

	this->layout.setSizeConstraint(QLayout::SetFixedSize);
	this->setLayout(&this->layout);

	connect(&this->timer, SIGNAL(timeout()), this, SLOT(step()));
	this->timer.start(1000/60);

	gettimeofday(&this->last_step, NULL);
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