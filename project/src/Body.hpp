class Body
{
	Point position;

protected:
	Body(const Point& initial_position)
		: position(initial_position)
	{
	}

public:
	Contact do_collision(Body& other); 
	virtual void on_collision(Body &other, Contact& contact);
};

Contact do_collision(Box& b1, Box& b2);
Contact do_collision(Box& b, Circle& c);
Contact do_collision(Circle& c1, Circle& c2);
