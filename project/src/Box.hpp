class Box : Shape
{
	double width;
	double height;

public:
	Contact do_collision(Box& other);
	Contact do_collision(Circle& other);
};