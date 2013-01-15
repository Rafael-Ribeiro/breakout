#include "../BreakoutLauncher.hpp"

#include "../BreakoutGame.hpp"
#include "../common.hpp"

BreakoutLauncher::BreakoutLauncher(QWidget *parent)
	: super(parent), layout(this), level(this),	ok_btn("OK", this), player_1(true, this), player_2(false, this), game(NULL)
{
	vector<string> levels_list = list_dir("../levels");
	vector<string>::iterator it = levels_list.begin();
	vector<string>::iterator end = levels_list.end();

	for (; it != end; it++)
		this->level.insertItem(numeric_limits<int>::max(), it->c_str());

	this->layout.addRow("Level", &this->level);
	this->layout.addRow(&this->player_1);
	this->layout.addRow(&this->player_2);
	this->layout.addRow(&this->ok_btn);
	this->setLayout(&this->layout);

	this->setWindowTitle("Breakout");

	connect(&this->ok_btn, SIGNAL(clicked()), this, SLOT(ok_clicked()));
}

BreakoutLauncher::~BreakoutLauncher()
{
	delete this->game;
}

void BreakoutLauncher::ok_clicked()
{
	emit done(0);

	this->game = new BreakoutGame
	(
		this->level.currentText().toUtf8().constData(),
		this->player_1.player(),
		this->player_2.player()
	);

	this->game->show();
}
