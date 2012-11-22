class Contact
{
	vector<Point> points;
	Vector normal;

	bool operator() const
	{
		return this->points.size() != 0;
	}
};
