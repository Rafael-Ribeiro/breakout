#include "../GameOfLifeApp.hpp"

GameOfLifeApp::GameOfLifeApp(QWidget *parent)
	:
		super(parent),
		resize_dialog(this),
		layout(this),
		toolbar(this),
		field(this),
		timer(this),
		playing(false)
{
	this->action_play_pause = this->toolbar.addAction(QIcon::fromTheme("media-playback-start"), "Play");
	this->action_step = this->toolbar.addAction(QIcon::fromTheme("media-skip-forward"), "Step");
	this->action_resize = this->toolbar.addAction(QIcon::fromTheme("zoom-fit-best"), "Resize");
	this->action_random = this->toolbar.addAction(QIcon::fromTheme("view-refresh"), "Random");
	this->action_clear = this->toolbar.addAction(QIcon::fromTheme("edit-clear"), "Clear");

	connect(this->action_play_pause, SIGNAL(triggered()), this, SLOT(play_pause()));
	connect(this->action_step, SIGNAL(triggered()), this, SLOT(step()));
	connect(this->action_resize, SIGNAL(triggered()), this, SLOT(resize()));
	connect(this->action_random, SIGNAL(triggered()), this, SLOT(random()));
	connect(this->action_clear, SIGNAL(triggered()), this, SLOT(clear()));

	this->layout.addWidget(&this->toolbar);
	this->layout.addWidget(&this->field);

	this->toolbar.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->layout.setSizeConstraint(QLayout::SetFixedSize);

	this->setLayout(&this->layout);

	connect(&this->timer, SIGNAL(timeout()), &this->field, SLOT(step()));
	connect
	(
		&this->resize_dialog, SIGNAL(ok(const size_t&, const size_t&)),
		this, SLOT(resize_ok(const size_t&, const size_t&))
	);

	this->setWindowTitle("Game of Life");
}

void GameOfLifeApp::play_pause()
{
	if (this->playing)
	{
		this->timer.stop();
		this->playing = false;
		this->action_play_pause->setText("Play");
		this->action_play_pause->setIcon(QIcon::fromTheme("media-playback-start"));
		this->action_step->setEnabled(true);

		this->action_resize->setEnabled(true);
		this->action_random->setEnabled(true);
		this->action_clear->setEnabled(true);

	} else
	{
		this->timer.start(1000 / 60);
		this->playing = true;
		this->action_play_pause->setText("Pause");
		this->action_play_pause->setIcon(QIcon::fromTheme("media-playback-pause"));

		this->action_step->setEnabled(false);
		this->action_resize->setEnabled(false);
		this->action_random->setEnabled(false);
		this->action_clear->setEnabled(false);
	}
}

void GameOfLifeApp::step()
{
	this->field.step();
}

void GameOfLifeApp::resize()
{
	this->resize_dialog.exec();
}

void GameOfLifeApp::resize_ok(const size_t &rows, const size_t &cols)
{
	this->field.setSize(rows, cols);
	this->layout.activate(); // force update of sizeHints
	super::resize(this->sizeHint());
}

void GameOfLifeApp::clear()
{
	this->field.clear();
}

void GameOfLifeApp::random()
{
	this->field.random();
}

