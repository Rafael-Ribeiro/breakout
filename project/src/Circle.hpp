class Circle : Shape
{
	Point center;
	double radius;

public:
	Contact do_collision(Box& other);
	Contact do_collision(Circle& other);
};