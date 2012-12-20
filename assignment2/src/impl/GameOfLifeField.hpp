#include "../GameOfLifeField.hpp"

const size_t GameOfLifeField::CELL_SIZE = 2;

GameOfLifeField::GameOfLifeField(QWidget *parent)
	: super(parent)
{
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->updateSize();
}

void GameOfLifeField::updateSize()
{
	QSize size = this->sizeHint();

	this->setMinimumSize(size);
	this->setMaximumSize(size);
	this->updateGeometry();
}

QSize GameOfLifeField::sizeHint() const
{
	return QSize(
		(GameOfLifeField::CELL_SIZE + 1) * this->engine.cols() + 1,
		(GameOfLifeField::CELL_SIZE + 1) * this->engine.rows() + 1
	);
}

void GameOfLifeField::paintEvent(QPaintEvent *event)
{
	super::paintEvent(event);

	QPainter painter(this);

	QColor black("black");
	QColor white("white");

	painter.setPen(black);

	for (size_t i = 0; i <= this->engine.rows(); i++)
		painter.drawLine
		(
			0,
			(GameOfLifeField::CELL_SIZE + 1) * i,
			(GameOfLifeField::CELL_SIZE + 1) * this->engine.cols() + 1,
			(GameOfLifeField::CELL_SIZE + 1) * i
		);

	for (size_t j = 0; j <= this->engine.cols(); j++)
		painter.drawLine
		(
			(GameOfLifeField::CELL_SIZE + 1) * j,
			0,
			(GameOfLifeField::CELL_SIZE + 1) * j,
			(GameOfLifeField::CELL_SIZE + 1) * this->engine.rows() + 1
		);


	for (size_t i = 0; i < this->engine.rows(); i++)
		for (size_t j = 0; j < this->engine.cols(); j++)
			painter.fillRect
			(
				(GameOfLifeField::CELL_SIZE + 1) * j + 1,
				(GameOfLifeField::CELL_SIZE + 1) * i + 1,
				GameOfLifeField::CELL_SIZE,
				GameOfLifeField::CELL_SIZE,
				this->engine[i][j] ? black : white
			);
}

void GameOfLifeField::mousePressEvent(QMouseEvent *e)
{
	QPoint pos = e->pos();

	size_t row = (pos.y() - 1) / (GameOfLifeField::CELL_SIZE + 1);
	size_t col = (pos.x() - 1) / (GameOfLifeField::CELL_SIZE + 1);

	this->engine.toggle(row, col);
	this->update();
}

void GameOfLifeField::step()
{
	this->engine.step();
	this->update();
}

void GameOfLifeField::clear()
{
	this->engine.clear();
	this->update();
}

void GameOfLifeField::random()
{
	this->engine.random();
	this->update();
}

void GameOfLifeField::setSize(const size_t &rows, const size_t &cols)
{
	this->engine.resize(rows, cols);

	this->updateSize();
	this->update();
}
