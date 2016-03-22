#include <iostream>
#include <Windows.h>
#include <vector>
#include "Path.h"
#include "Elevator.h"
using namespace std;



void main()
{
	Elevator e;

	int userIn;

	HANDLE serviceProcessor = e.turnOn();

	cout<<endl<<"You are on floor one, do you want to go up: "<<"Press any key to request the elevator."<<endl;
	cin>>userIn;

	e.requestService(0,1);

	WaitForSingleObject(serviceProcessor,INFINITE);
}

