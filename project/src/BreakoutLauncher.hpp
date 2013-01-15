#pragma once

#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>

#include "BreakoutLauncherPlayer.hpp"

class BreakoutGame;

class BreakoutLauncher
	: public QDialog
{
	Q_OBJECT

public:
	typedef QDialog super;

	BreakoutLauncher(QWidget *parent = NULL);
	~BreakoutLauncher();

private:
	QFormLayout layout;
	QComboBox level;
	QPushButton ok_btn;
	BreakoutLauncherPlayer player_1;
	BreakoutLauncherPlayer player_2;

	BreakoutGame *game;

private slots:
	void ok_clicked();
};