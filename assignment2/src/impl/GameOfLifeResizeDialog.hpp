#include "../GameOfLifeResizeDialog.hpp"

GameOfLifeResizeDialog::GameOfLifeResizeDialog(QWidget *parent)
	: super(parent), layout(this), rows(this), cols(this), ok_btn("OK", this)
{
	this->rows.setRange(5, 60);
	this->cols.setRange(5, 60);

	this->rows.setValue(GameOfLifeEngine::DEFAULT_ROWS);
	this->cols.setValue(GameOfLifeEngine::DEFAULT_COLS);

	this->layout.addRow("Rows", &this->rows);
	this->layout.addRow("Cols", &this->cols);
	this->layout.addRow(&this->ok_btn);
	this->setLayout(&this->layout);

	this->setWindowTitle("Resize");

	connect(&this->ok_btn, SIGNAL(clicked()), this, SLOT(ok_clicked()));
}

void GameOfLifeResizeDialog::ok_clicked()
{
	emit done(0);
	emit ok(this->rows.value(), this->cols.value());
}