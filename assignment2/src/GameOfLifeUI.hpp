#ifndef GAMEOFLIFEUI_HPP
#define GAMEOFLIFEUI_HPP

#include <QWidget>

#include "GameOfLifeEngine.hpp"

// forward declaration
class GameOfLifeEngine;

class GameOfLifeUI
	: public QWidget
{
	Q_OBJECT

public:
	typedef QWidget super;
	GameOfLifeUI(QWidget *parent = NULL);

private:
	GameOfLifeEngine engine;
};

#endif