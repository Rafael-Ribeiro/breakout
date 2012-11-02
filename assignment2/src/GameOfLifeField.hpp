#ifndef GAMEOFLIFEFIELD_HPP
#define GAMEOFLIFEFIELD_HPP

#include <QWidget>
#include <QFrame>
#include <QTimer>
#include <QSize>
#include <QPainter>

#include "GameOfLifeEngine.hpp"

class GameOfLifeField
	: public QFrame
{
	Q_OBJECT

public:
	typedef QFrame super;
	GameOfLifeField(QWidget *parent = NULL);

	const static size_t CELL_SIZE;

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void clear();
	void random();

protected:
	virtual void paintEvent(QPaintEvent *event);

private:
	GameOfLifeEngine engine;

public slots:
	void step();

};

#endif