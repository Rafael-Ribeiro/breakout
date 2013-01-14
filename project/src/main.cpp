#include <QtGui>
#include <cstdlib>
#include <ctime>

#include "BreakoutApp.hpp"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	QApplication qapp(argc, argv);

	BreakoutApp app;
	app.show();

	return qapp.exec();
}