#include "../World.hpp"

#include "../Paddle.hpp"
#include "../Ball.hpp"
#include "../Brick.hpp"

World::World()
	: _bodies(), _movables()
{
}

World::~World()
{
	set<Body*>::iterator it = this->_bodies.begin();
	set<Body*>::iterator end = this->_bodies.end();
	
	for (; it != end; it++)
		delete *it;
}

const set<Body*>& World::bodies() const
{
	return this->_bodies;
}

void World::step(const double& dt)
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

			for (; itb2 != endb; itb2++)
			{
				if (!(*itb)->collision_filter(**itb2))
					continue;

				Contact contact = (*itb)->get_collision_contact(**itb2, dt - d);

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

			bool da = a->collision_handle(contacts[i]);
			bool db = b->collision_handle(contacts[i]);

			if (da)
			{
				this->remove(a);
				delete a;
			}

			if (db)
			{
				this->remove(b);
				delete b;
			}

			break;
		}

	}
}

void World::add(Body *body)
{
	this->_bodies.insert(body);

	Movable *m = dynamic_cast<Movable*>(body);

	if (m)
		this->_movables.insert(m);

}

void World::remove(Body *body)
{
	this->_bodies.erase(body);

	Movable *m = dynamic_cast<Movable*>(body);

	if (m)
		this->_movables.erase(m);

}