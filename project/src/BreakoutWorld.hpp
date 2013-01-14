#pragma once

#include "World.hpp"

class BreakoutWorld : public World
{
	typedef World super;

public:
	BreakoutWorld();

	void add(Body *body);
	void remove(Body *body);

	bool load_level(string level_filename_path);
};