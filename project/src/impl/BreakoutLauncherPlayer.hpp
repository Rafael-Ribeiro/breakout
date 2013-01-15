#include "../BreakoutLauncherPlayer.hpp"

#include "../HumanPlayer.hpp"
#include "../CPUPlayer.hpp"
#include "../CPUStrategyMultiton.hpp"

BreakoutLauncherPlayer::BreakoutLauncherPlayer(bool first, QWidget *parent)
	: QGroupBox(first ? "Player 1" : "Player 2", parent), layout(this), human("Human"), cpu("CPU")
{
	this->group.addButton(&this->human);
	this->layout.addWidget(&this->human, 0, 0);

	this->human_keys.insertItem(0, "Left and Right");
	this->human_keys.insertItem(1, "A and D");

	this->layout.addWidget(&this->human_keys, 0, 1);

	this->group.addButton(&this->cpu);
	this->layout.addWidget(&this->cpu, 1, 0);
	
	CPUStrategyMultiton::map_t::const_iterator it = CPUStrategyMultiton::strategies().begin();
	CPUStrategyMultiton::map_t::const_iterator end = CPUStrategyMultiton::strategies().end();

	for (; it != end; ++it)
		this->cpu_strategy.insertItem(numeric_limits<int>::max(), QString(it->first.c_str()));

	this->layout.addWidget(&this->cpu_strategy, 1, 1);

	this->setLayout(&this->layout);

	if (first)
		this->human.setChecked(true);
	else
		this->cpu.setChecked(true);
}

BreakoutLauncherPlayer::~BreakoutLauncherPlayer()
{
}

Player* BreakoutLauncherPlayer::player()
{
	if (this->human.isChecked())
	{
		if (this->human_keys.currentIndex() == 0)
			return new HumanPlayer();
		else
			return new HumanPlayer(Qt::Key::Key_A, Qt::Key::Key_D);

	} else
		return new CPUPlayer(CPUStrategyMultiton::get(this->cpu_strategy.currentText().toUtf8().constData()));
}