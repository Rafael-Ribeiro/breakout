#include "../Bonus.hpp"

const unsigned int Bonus::BASE_WIDTH = 16;
const unsigned int Bonus::BASE_HEIGHT = 16;

Bonus::Bonus(const Point &initial_position, const Vector& initial_velocity)
	: Box(Bonus::BASE_WIDTH, Bonus::BASE_HEIGHT), Movable(initial_velocity), Drawable()
{
	this->init(initial_position);
}

Bonus::~Bonus()
{
}

SpeedBonus::SpeedBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void SpeedBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0xEB, 0x22, 0x22);
	QColor pen_color = brush_color.darker(150);

	painter.setBrush(QBrush(brush_color));
	painter.setPen(pen_color);

	painter.drawRect
	(
		this->position().x() - this->hwidth() + 0.5,
		this->position().y() - this->hheight() + 0.5,
		this->width() - 1,
		this->height() -1
	);
}

void SpeedBonus::execute(BreakoutWorld& world, Player& player)
{
	cout << "BONUS HIT!" << endl;
}

Bonus* BonusFactory::make_random_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	/* TODO: random*/
	return BonusFactory::make_speed_bonus(initial_position, initial_velocity);
}

SpeedBonus* BonusFactory::make_speed_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new SpeedBonus(initial_position, initial_velocity);
}
