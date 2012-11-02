#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QToolBar>
#include <QTimer>
#include <QAction>
#include <QIcon>
#include <QSpinBox>
#include <QPushButton>
#include <QSizePolicy>

#include "GameOfLifeField.hpp"
#include "GameOfLifeResizeDialog.hpp"

class GameOfLifeApp
	: public QWidget
{
	Q_OBJECT

public:
	typedef QWidget super;
	GameOfLifeApp(QWidget *parent = NULL);

private:
	GameOfLifeResizeDialog resize_dialog;

	QVBoxLayout layout;
	QToolBar toolbar;
	GameOfLifeField field;
	QTimer timer;
	bool playing;

	QAction *action_play_pause;
	QAction *action_step;
	QAction *action_resize;
	QAction *action_random;
	QAction *action_clear;

private slots:
	void play_pause();
	void step();
	void resize();
	void clear();
	void random();

public slots:
	void resize_ok(const size_t &rows, const size_t &cols);
};
