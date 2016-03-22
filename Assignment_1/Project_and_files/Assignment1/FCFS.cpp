// FCFS.cpp
// Andrew Ribeiro
// November 12, 2009
// First Come First Served (FCFS) scheduling algorithm


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



void FCFS(vector<Process> data, string file , string & sumaryOutPut)
{
	// Write log to file.
	ofstream fileOut;

	if(file.size() != 0)
	{
		fileOut.open(file.c_str());

		cout<<endl
			<<"Writing result log to file. Please wait.."<<endl;
	}

	vector<Process> readyQueue;
    
	int time = 0; 
	
	int totalNumberOfProcesses = data.size();
	int totalWaitTime = 0;
	int totalBurst = 0;
	int totalPriority = 0;
	
	// While we have processes to work on.
	while(readyQueue.size() != 0 || data.size() != 0)
	{
		// Load processes with arival time equal to time. 
		// Note: Sort data to optimise this.
		for(unsigned int i = 0; i < data.size(); i++)
		{
			if(data[i].arival <= time)
			{
				
				readyQueue.push_back(data[i]);
				data.erase(data.begin() + i);
			}
		}
		

		// If there are still items in the ready queue
		if(readyQueue.size() > 0)
		{
			// Calculate the wait time,average priority, and average burst time.
			if(readyQueue[0].workDone == 0)
			{
				totalWaitTime += (time - readyQueue[0].arival);
				totalBurst += readyQueue[0].burstTime;
				totalPriority += readyQueue[0].priority;
			}

			// Increment work done. 
			readyQueue[0].workDone++;

			// Write to file.
			if(file.size() != 0)
			{
				fileOut<<"Cycle("<<time<<"): "<<readyQueue[0].name<<"("<<readyQueue[0].workDone<<" of "<<readyQueue[0].burstTime<<")"<<endl;
			}
			

			// Check if the work has been completed.
			if(readyQueue[0].workDone >= readyQueue[0].burstTime)
			{
				//Remove from ready queue.
				readyQueue.erase(readyQueue.begin());
			}
		}
	
		// Next cycle 
		time++;
	}



	fileOut<<endl<<endl
		<<"*** FCFS RESULTS ****"<<endl
		<<"* Number of processes: "<<totalNumberOfProcesses<<endl
		<<"* Average wait time: "<< (totalWaitTime/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average burst time: "<<(totalBurst/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average priority: "<<(totalPriority/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Total cycles: "<<time<<endl
		<<"********************"<<endl<<endl;



	if(sumaryOutPut.size() != 0)
	{
		stringstream sumOut;

		sumOut<<endl<<endl
		<<"*** FCFS RESULTS ****"<<endl
		<<"* Number of processes: "<<totalNumberOfProcesses<<endl
		<<"* Average wait time: "<< (totalWaitTime/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average burst time: "<<(totalBurst/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average priority: "<<(totalPriority/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Total cycles: "<<time<<endl
		<<"********************"<<endl<<endl;

		sumaryOutPut = sumOut.str();
	}


	// Close out file.
	if(file.size() != 0)
	{
		fileOut.close();
	}

	// Display the results
	cout<<endl<<endl
		<<"*** FCFS RESULTS ****"<<endl
		<<"* Number of processes: "<<totalNumberOfProcesses<<endl
		<<"* Average wait time: "<< (totalWaitTime/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average burst time: "<<(totalBurst/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average priority: "<<(totalPriority/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Total cycles: "<<time<<endl
		<<"********************"<<endl<<endl;
}
