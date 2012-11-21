#include <QtGui>
#include <cstdlib>
#include <ctime>

#include "GameOfLifeApp.hpp"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	QApplication qapp(argc, argv);

	GameOfLifeApp app;
	app.show();

	return qapp.exec();
}
