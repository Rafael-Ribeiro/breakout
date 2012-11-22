#include <QtGui>
#include <cstdlib>
#include <ctime>

#include "BreakoutApp.hpp"
#include "Paddle.hpp"

int main(int argc, char *argv[])
{
/*	srand(time(NULL));

	QApplication qapp(argc, argv);

	BreakoutApp app;
	app.show();

	return qapp.exec();
*/
	Paddle b(Vector(0, 0), Vector(3, 0));
	b.step(0.5);

	cout << b.position() << endl;

	b.velocity() = Vector(0, 1);
	b.step(0.5);

	cout << b.position() << endl;

	return 0;
}