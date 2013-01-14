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

/*	Paddle b(Vector(0, 0), Vector(3, 0));
	Paddle c(Vector(0, 0), Vector(3, 0));

	b.do_collision(c);
*/
	return 0;
}