#pragma once

#include <QGroupBox>
#include <QGridLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QComboBox>

#include "Player.hpp"

class BreakoutLauncherPlayer
	: public QGroupBox
{
	Q_OBJECT

	QGridLayout layout;

	QButtonGroup group;
	QRadioButton human;
	QRadioButton cpu;

	QComboBox human_keys;
	QComboBox cpu_strategy;

public:
	BreakoutLauncherPlayer(bool first, QWidget *parent = NULL);
	~BreakoutLauncherPlayer();

	Player* player();
};