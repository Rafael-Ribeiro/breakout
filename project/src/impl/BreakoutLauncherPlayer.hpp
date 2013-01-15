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
	
	this->cpu_strategy.insertItem(0, "Closest Ball");
	this->cpu_strategy.insertItem(1, "First Ball");

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
	{
		if (this->cpu_strategy.currentIndex() == 0)
			return new CPUPlayer(&CPUStrategyMultiton::get_closest_ball_cpu_strategy_instance());
		else
			return new CPUPlayer(&CPUStrategyMultiton::get_first_ball_cpu_strategy_instance());
	}
}