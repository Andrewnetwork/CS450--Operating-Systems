#include <iostream>
#include <Windows.h>
#include <vector>
#include "Path.h"
using namespace std;


DWORD WINAPI StartThread(LPVOID iValue);

class Elevator
{
public:
	const int weightCapacity; // In lbs.
	const int highestFloor;
	short int currentFloor;

	HANDLE serviceProcessor;
    DWORD dwGenericThread;

	vector<Path> upPaths;
	vector<Path> downPaths;

	void requestService(bool direction, short int startFloor)
	{
		if(direction)
		{
			// Down
			cout<<"Person requested to go down from floor "<<startFloor<<endl;
			Path servicePath(direction,startFloor);
			downPaths.push_back(servicePath);
		}
		else
		{
			// Up
			cout<<"Person requested to go up from floor "<<startFloor<<endl;
			Path servicePath(direction,startFloor);
			upPaths.push_back(servicePath);
		}
	}
	
	void move(bool direction)
	{
		if(direction)
		{
			//Down
			currentFloor--;
			cout<<"Floor: "<<currentFloor<<endl;
		}
		else
		{
			//Up
			currentFloor++;
			cout<<"Floor: "<<currentFloor<<endl;
		}
	}

	Elevator():weightCapacity(3000),highestFloor(10)
	{
		currentFloor = 1;
	}

	HANDLE turnOn()
	{
     
      serviceProcessor = CreateThread(NULL,0,StartThread,this,0,&dwGenericThread);
	  Sleep(2000); // Wait for the elevator to turn on.
	  return serviceProcessor;
	}

};

DWORD WINAPI StartThread(LPVOID iValue)
{
	  Elevator * pElevator  = (Elevator *)iValue;
	  int waitCounter = 0;
	  cout<<endl<<"Elevator Processor Online"<<endl;
	
	  while(true)
	  {
		  Sleep(2000);
		  if(pElevator->upPaths.size() == 0 && pElevator->downPaths.size() == 0)
		  {
			 cout<<"Resting at floor: "<<pElevator->currentFloor<<endl;
		  }
		  else
		  {
			  if(pElevator->currentFloor <= 5 && pElevator->downPaths.size() != 0)
			  {
				 // Process down vector.
				 if(pElevator->downPaths[0].destFloor != -1)
				 {
					 pElevator->move(1);
					 cout<<"Moving elevator down, floor: "<<pElevator->currentFloor<<endl;
				 }
				 else
				 {
					 waitCounter++;
					
					 if(waitCounter >= 10)
					 {
						 // Person is taking to long to pick a floor. Remove his request from the vector.
						 cout<<"Time exceeded for the user to pick a floor"<<endl;
						 pElevator->downPaths.erase( pElevator->downPaths.begin());
						 waitCounter = 0;
					 }
				 }
			  }
			  else
			  {
				 
				  // Process up vector.
				 if(pElevator->upPaths[0].destFloor != -1)
				 {
					 pElevator->move(0);
					 cout<<"Moving elevator up, floor: "<<pElevator->currentFloor<<endl;
				 }
				 else
				 {
					 waitCounter++;
					 
					 if(waitCounter >= 10)
					 {
						 // Person is taking to long to pick a floor. Remove his request from the vector.
						 cout<<"Time exceeded for the user to pick a floor"<<endl;
						 pElevator->upPaths.erase( pElevator->upPaths.begin());
						 waitCounter = 0;
					 }
				 }
			  }
		  }
	  }
	
	  return 0;
}
