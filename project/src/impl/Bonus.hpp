#include "../Bonus.hpp"

#include "../BreakoutWorld.hpp"
#include "../BallState.hpp"
#include "../common.hpp"

const unsigned int Bonus::BASE_WIDTH = 16;
const unsigned int Bonus::BASE_HEIGHT = 16;
const double Bonus::BASE_VELOCITY = 200.0;

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
	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();
	
	for (; it != end; it++)
		(*it)->velocity() *= 1.3;
}

RadiusBonus::RadiusBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void RadiusBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0x22, 0xEB, 0x22);
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

void RadiusBonus::execute(BreakoutWorld& world, Player& player)
{
	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();
	
	for (; it != end; it++)
		(*it)->grow();
}


BallBonus::BallBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void BallBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0x22, 0x22, 0xEB);
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

void BallBonus::execute(BreakoutWorld& world, Player& player)
{
	Ball *ball = BallFactory::make_normal_ball
	(
		Point(BreakoutWorld::WIDTH / 2, BreakoutWorld::HEIGHT / 2),
		Vector::random_unitary() * Ball::BASE_VELOCITY
	);

	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();
	
	for (; it != end; it++)
	{
		if (ball->get_collision_contact(**it, 0))
		{
			delete ball;
			return;
		}
	}

	world.add(ball);
}


PhantomBonus::PhantomBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void PhantomBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0x55, 0x55, 0x55);
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

void PhantomBonus::execute(BreakoutWorld& world, Player& player)
{
	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();
	
	for (; it != end; it++)
		(*it)->set_state(new PhantomBallState());
}


FireBonus::FireBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void FireBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0x55, 0x55, 0x55);
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

void FireBonus::execute(BreakoutWorld& world, Player& player)
{
	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();
	
	for (; it != end; it++)
		(*it)->set_state(new FireBallState());
}

GlassBonus::GlassBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void GlassBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0x55, 0x55, 0xff);
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

void GlassBonus::execute(BreakoutWorld& world, Player& player)
{
	set<Brick*>::iterator it = world.bricks().begin();
	set<Brick*>::iterator end = world.bricks().end();
	
	for (; it != end; ++it)
		if (!dynamic_cast<ConcreteBrickState*>((*it)->state()))
			(*it)->set_state(new GlassBrickState());
}

WidthBonus::WidthBonus(const Point &initial_position, const Vector& initial_velocity)
	: Bonus(initial_position, initial_velocity)
{
}

void WidthBonus::draw(QPainter& painter) const
{
	QColor brush_color = QColor(0xEB, 0x22, 0xEB);
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

void WidthBonus::execute(BreakoutWorld& world, Player& player)
{
	player.paddle()->hwidth() += 10;
}

Bonus* BonusFactory::make_random_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	int choice = random_int(0, 6);

	switch (choice)
	{
		case 0:
			return BonusFactory::make_speed_bonus(initial_position, initial_velocity);
			break;

		case 1:
			return BonusFactory::make_radius_bonus(initial_position, initial_velocity);
			break;
		
		case 2:
			return BonusFactory::make_ball_bonus(initial_position, initial_velocity);
			break;
		
		case 3:
			return BonusFactory::make_phantom_bonus(initial_position, initial_velocity);
			break;

		case 4:
			return BonusFactory::make_fire_bonus(initial_position, initial_velocity);
			break;

		case 5:
			return BonusFactory::make_glass_bonus(initial_position, initial_velocity);
			break;

		default:
			return BonusFactory::make_width_bonus(initial_position, initial_velocity);
			break;	
	}
}

SpeedBonus* BonusFactory::make_speed_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new SpeedBonus(initial_position, initial_velocity);
}

RadiusBonus* BonusFactory::make_radius_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new RadiusBonus(initial_position, initial_velocity);
}

BallBonus* BonusFactory::make_ball_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new BallBonus(initial_position, initial_velocity);
}

PhantomBonus* BonusFactory::make_phantom_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new PhantomBonus(initial_position, initial_velocity);
}

FireBonus* BonusFactory::make_fire_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new FireBonus(initial_position, initial_velocity);
}

GlassBonus* BonusFactory::make_glass_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new GlassBonus(initial_position, initial_velocity);
}

WidthBonus* BonusFactory::make_width_bonus(const Point &initial_position, const Vector& initial_velocity)
{
	return new WidthBonus(initial_position, initial_velocity);
}
