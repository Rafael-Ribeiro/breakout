#include <QtGui>

#include "GameOfLifeUI.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	GameOfLifeUI ui;
	ui.show();

	return app.exec();
}