class BreakoutFrame
{
	const Engine* engine;

public:
	BreakoutFrame(const Engine* engine)
		: engine(engine)
	{
	}

	/* TODO override Qt's draw*/
	void draw();
};