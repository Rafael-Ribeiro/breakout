#pragma once

#include <map>

#include <QKeyEvent>

class Keyboard
{
	static Keyboard single_instance;

	map<Qt::Key, bool> _is_down;

	Keyboard();

public:
	static Keyboard& get_instance();

	void handle_event(QKeyEvent *event, bool press);
	bool operator [] (Qt::Key key) const;
};