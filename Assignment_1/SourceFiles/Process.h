// Process.h
// Andrew Ribeiro
// November 12, 2009

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;


struct Process
{

	Process(string name, unsigned short int priority, unsigned short int arival, unsigned short int burstTime)
	{
		this->name = name;
		this->priority = priority;
		this->arival = arival;
		this->burstTime = burstTime; 
		this->workDone = 0;
	}

	unsigned short int workDone; 
	string name;
	unsigned short int burstTime;
	unsigned short int priority;
	unsigned short int arival;
};



#endif 