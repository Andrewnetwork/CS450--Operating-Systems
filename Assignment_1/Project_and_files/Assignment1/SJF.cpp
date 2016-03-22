// SJF.cpp
// Andrew Ribeiro 
// November 12, 2009
// Shortest Job First Non-Preemptive & Preemptive

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "Process.h"
#include "Constants.h"


bool compare (const Process & a, const Process & b)
{
	return ( a.burstTime <  b.burstTime);
}

// Shortest Job First Preemptive
void SJFP(vector<Process> data, string file, string & sumaryOutPut)
{

	// Write log to file.
	ofstream fileOut;
	stringstream queueData;

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

		// Sort every time, even if a job is runing, preempt it.
	
		sort(readyQueue.begin(),readyQueue.end(),compare);
		
		queueData<<endl;
		for(int f = 0; f < readyQueue.size(); f++)
		{
			queueData<<"  "<<readyQueue[f].burstTime;
		}
		queueData<<endl;
	

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
				
				fileOut<<"Cycle("<<time<<"): "<<readyQueue[0].name<<"("<<readyQueue[0].workDone<<" of "<<readyQueue[0].burstTime<<")";
                
				fileOut.flags(ios::right);

				fileOut<<setw(30)<< readyQueue[0].arival<<endl;
			}
			

			// Check if the work has been completed.
			if(readyQueue[0].workDone >= readyQueue[0].burstTime)
			{
				//Remove from ready queue.
				readyQueue.erase(readyQueue.begin());

				// Show a new line for new process group.
				fileOut<<endl;
			}
		}
	
		// Next cycle 
		time++;
	}
	// We processed all of the jobs! 


	fileOut<<"*** Printout of ready queue contents over time(in respect to burst time) ***"
		   <<queueData.str()<<endl;


	fileOut<<endl<<endl
		<<"*** SJF(Preemptive) RESULTS ****"<<endl
		<<"* Number of processes: "<<totalNumberOfProcesses<<endl
		<<"* Average wait time: "<< (totalWaitTime/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average burst time: "<<(totalBurst/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average priority: "<<(totalPriority/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Total cycles: "<<time<<endl
		<<"********************"<<endl<<endl;

	
	// Return the sumary 
	if(sumaryOutPut.size() != 0)
	{
		stringstream sumOut;

		sumOut<<endl<<endl
		<<"*** SJF(Preemptive) RESULTS ****"<<endl
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
		<<"*** SJF(Preemptive) RESULTS ****"<<endl
		<<"* Number of processes: "<<totalNumberOfProcesses<<endl
		<<"* Average wait time: "<< (totalWaitTime/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average burst time: "<<(totalBurst/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average priority: "<<(totalPriority/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Total cycles: "<<time<<endl
		<<"********************"<<endl<<endl;

}

// Shortest Job First Non-Preemptive
void SJFNP(vector<Process> data, string file, string & sumaryOutPut)
{
	// Write log to file.
	ofstream fileOut;
	stringstream queueData;

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
	bool processingJob = false; 
	
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

		// If the cpu is not processing a job, sort data to make lowest birst size first. 
		if(!processingJob)
		{
			
			sort(readyQueue.begin(),readyQueue.end(),compare);
			
			queueData<<endl;
			for(int f = 0; f < readyQueue.size(); f++)
			{
				queueData<<"  "<<readyQueue[f].burstTime;
			}
			queueData<<endl;
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

				// Job begins.
				processingJob = true;
			}

			// Increment work done. 
			readyQueue[0].workDone++;

			// Write to file.
			if(file.size() != 0)
			{
				
				fileOut<<"Cycle("<<time<<"): "<<readyQueue[0].name<<"("<<readyQueue[0].workDone<<" of "<<readyQueue[0].burstTime<<")";
                
				fileOut.flags(ios::right);

				fileOut<<setw(30)<< readyQueue[0].arival<<endl;
			}
			

			// Check if the work has been completed.
			if(readyQueue[0].workDone >= readyQueue[0].burstTime)
			{
				//Remove from ready queue.
				readyQueue.erase(readyQueue.begin());

				// Show a new line for new process group.
				fileOut<<endl;

				// Job ended. 
				processingJob = false;
			}
		}
	
		// Next cycle 
		time++;
	}
	// We processed all of the jobs! 


	fileOut<<"*** Printout of ready queue contents over time(in respect to burst time) ***"
		   <<queueData.str()<<endl;


	fileOut<<endl<<endl
		<<"*** SJF(Non-Preemptive) RESULTS ****"<<endl
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
		<<"*** SJF(Non-Preemptive) RESULTS ****"<<endl
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
		<<"*** SJF(Non-Preemptive) RESULTS ****"<<endl
		<<"* Number of processes: "<<totalNumberOfProcesses<<endl
		<<"* Average wait time: "<< (totalWaitTime/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average burst time: "<<(totalBurst/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Average priority: "<<(totalPriority/totalNumberOfProcesses)<<" cycles"<<endl
		<<"* Total cycles: "<<time<<endl
		<<"********************"<<endl<<endl;
}
