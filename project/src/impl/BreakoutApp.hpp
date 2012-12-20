#include "../BreakoutApp.hpp"

BreakoutApp::BreakoutApp(QWidget *parent)
	: super(parent), layout(this), frame(&engine)
{
	this->layout.addWidget(&this->frame);

	this->layout.setSizeConstraint(QLayout::SetFixedSize);
	this->setLayout(&this->layout);
}