#include "../GameOfLifeResizeDialog.hpp"

GameOfLifeResizeDialog::GameOfLifeResizeDialog(QWidget *parent)
	: super(parent), layout(this), width(this), height(this), ok_btn("OK", this)
{
	this->width.setRange(5, 60);
	this->height.setRange(5, 60);

	this->width.setValue(GameOfLifeEngine::DEFAULT_ROWS);
	this->height.setValue(GameOfLifeEngine::DEFAULT_COLS);

	this->layout.addRow("Width", &this->width);
	this->layout.addRow("Height", &this->height);
	this->layout.addRow(&this->ok_btn);
	this->setLayout(&this->layout);

	this->setWindowTitle("Resize");

	connect(&this->ok_btn, SIGNAL(clicked()), this, SLOT(ok_clicked()));
}

void GameOfLifeResizeDialog::ok_clicked()
{
	emit done(0);
	emit ok(this->width.value(), this->height.value());
}