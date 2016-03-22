
#pragma once 

class Path
{
public:
	bool direction; // O is up, 1 is down
	short int callFloor;
	short int destFloor;

	Path(bool direction, short int callFloor)
	{
		this->direction = direction;
		this->callFloor = callFloor;
		this->destFloor = -1;
	}
};