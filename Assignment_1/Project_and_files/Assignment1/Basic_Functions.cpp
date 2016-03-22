// Basic_Functions.cpp
// Andrew Ribeiro
// November 12, 2009


#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "Process.h"
#include "Constants.h"


void resetData(vector<Process> & data)
{
	// Seting work done to 0.
	for(int i = 0; i < data.size(); i++)
	{
		data[i].workDone = 0;
	}
}
void generateData(vector<Process> & data)
{
	srand((unsigned)time(0));

   
	
	// Populate the vector. 
	for(int i = 0; i < NUMBER_OF_PROCESSES; i++)
	{
		// Name
		stringstream sstream;
        
		sstream<<(i + 1);

		string name = "Process"+sstream.str();

		//Burst time

		unsigned short int burstTime = (rand() % MAX_BURST_TIME) + MIN_BURST_TIME;
		
		// Priority 

		unsigned short int priority = (rand() % MIN_PRIORITY ) + 1;

		// Arival 

		unsigned short int arival = (rand() % MAX_ARIVAL );

		// New process

		Process temp(name,priority,arival,burstTime);

		// Put into the vector
		data.push_back(temp);
	}

}
