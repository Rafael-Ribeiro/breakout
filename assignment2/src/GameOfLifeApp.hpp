#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QToolBar>
#include <QTimer>
#include <QAction>
#include <QIcon>

#include "GameOfLifeField.hpp"

class GameOfLifeApp
	: public QWidget
{
	Q_OBJECT

public:
	typedef QWidget super;
	GameOfLifeApp(QWidget *parent = NULL);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

private:
	QDialog resize_dialog;
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
};
