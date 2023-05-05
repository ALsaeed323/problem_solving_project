#pragma once

#include "Level.h"

class LevelOne : public Level
{
public:
	LevelOne();
	~LevelOne() {}
private:
	void loadScreen();
};