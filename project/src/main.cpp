#include <QtGui>
#include <cstdlib>
#include <ctime>

#include "BreakoutLauncher.hpp"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	QApplication qapp(argc, argv);

	BreakoutLauncher laucher;
	laucher.show();

	return qapp.exec();
}