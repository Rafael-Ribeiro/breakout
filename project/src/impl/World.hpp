#include "../World.hpp"

#include "../Bonus.hpp"

const unsigned int World::MAX_STEP_ITERATIONS = 3;

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
	unsigned int iterations = 0;

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
				if (!this->collision_filter(**itb, **itb2))
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

		int i;
		for (i = contacts.size() - 1; i >= 0; i--)
		{
			toc = contacts[i].toc();

			Body* a = contacts[i].body_a();
			Body* b = contacts[i].body_b();

			bool updates = this->collision_updates_physics(*a, *b);

			if (updates)
			{
				it = this->_movables.begin();
				end = this->_movables.end();

				for (; it != end; it++)
					(*it)->step(toc);
			}
			
			this->collision_handle(contacts[i]);

			if (updates)
				break;
		}

		if (i < 0 || iterations >= World::MAX_STEP_ITERATIONS)
			break;

		iterations++;
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