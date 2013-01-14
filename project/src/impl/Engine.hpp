#include "../Engine.hpp"

#include "../Paddle.hpp"
#include "../Ball.hpp"
#include "../Brick.hpp"

Engine::Engine()
	: _bodies(), _movables()
{
	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			Brick* brick = BrickFactory::makeNormalBrick(Point(48 * i + 25, 16 * j + 100), 1);
			this->_bodies.insert(brick);
		}
	}

	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			Brick* brick = BrickFactory::makeNormalBrick(Point(48 * i + 25, 16 * j + 500), 1);
			this->_bodies.insert(brick);
		}
	}

	Ball* missile = BallFactory::makeNormalBall(Point(500, 400), Vector(3.0, -200));
	this->_bodies.insert(missile);
	this->_movables.insert(missile);
}

Engine::~Engine()
{
	set<Body*>::iterator it = this->_bodies.begin();
	set<Body*>::iterator end = this->_bodies.end();
	
	for (; it != end; it++)
		delete *it;
}

const set<Body*>& Engine::bodies() const
{
	return this->_bodies;
}

void Engine::step(const double& dt)
{
	set<Movable*>::iterator it, end;	
	set<Body*>::iterator itb, itb2, endb;

	vector<Contact> contacts;

	double toc = 0;

	for (double d = 0; d < dt; d = dt + toc)
	{
		it = this->_movables.begin();
		end = this->_movables.end();

		for (; it != end; it++)
			(*it)->step(dt - d);

		contacts.clear();

		itb = this->_bodies.begin();
		endb = this->_bodies.end();

		for (; itb != endb; itb++)
		{
			itb2 = ++itb;
			--itb;

			Movable* mb1 = dynamic_cast<Movable*>(*itb);

			for (; itb2 != endb; itb2++)
			{
				Movable* mb2 = dynamic_cast<Movable*>(*itb2);

				if (!mb1 && !mb2)
					continue;

				Contact contact = (*itb)->do_collision(**itb2, dt - d);

				if (contact)
					contacts.push_back(contact);

			}
		}

		sort(contacts.begin(), contacts.end(), greater<Contact>());

		// remove all that occured just now, or are in the future (infinite collision)
		while (!contacts.empty())
		{
			if (contacts.back().toc() < -numeric_limits<double>::epsilon())
				break;

			contacts.pop_back();
		}

		if (contacts.empty())
			break;

		for (int i = contacts.size() - 1; i >= 0; i--)
		{
			toc = contacts[i].toc();

			/* TODO: precolide

			if (!precolide)
				da = A.postcolide(B);
				db = B.postcolide(A);
				continue;
			*/

			it = this->_movables.begin();
			end = this->_movables.end();

			for (; it != end; it++)
				(*it)->step(toc);

			Body* a = contacts[i].body_a();
			Body* b = contacts[i].body_b();

			bool da = a->post_collision(contacts[i]);
			bool db = b->post_collision(contacts[i]);

			if (da)
			{
				this->_bodies.erase(a);
	
				Movable *ma = dynamic_cast<Movable*>(a);
				if (ma)
					this->_movables.erase(ma);

				delete a;
			}

			if (db)
			{
				this->_bodies.erase(b);

				Movable *mb = dynamic_cast<Movable*>(b);
				if (mb)
					this->_movables.erase(mb);

				delete b;
			}

			break;
		}

	}
}