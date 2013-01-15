#include "../Keyboard.hpp"

Keyboard Keyboard::single_instance;

Keyboard::Keyboard()
{
}

Keyboard& Keyboard::get_instance()
{
	return Keyboard::single_instance;
}

void Keyboard::handle_event(QKeyEvent *event, bool press)
{
	this->_is_down[Qt::Key(event->key())] = press;
}

bool Keyboard::operator [] (Qt::Key key) const
{
	map<Qt::Key, bool>::const_iterator it_value = this->_is_down.find(key);
	return (it_value != this->_is_down.end()) && it_value->second;
}