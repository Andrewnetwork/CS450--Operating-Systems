// DeterministicModeling_SchedulingAlgorithms.cpp
// Andrew Ribeiro
// November 12, 2009

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>


#include "Process.h"
#include "Constants.h"

using namespace std;

// Function Prototypes 
void generateData(vector<Process> & data);
void resetData(vector<Process> & data);

// First Come First Serve: FCFS.cpp
void FCFS(vector<Process> data, string file = "", string & sumaryOutPut = string(""));

//Shortest Job First Preemptive and non-preemptive: SJF.cpp
void SJFP(vector<Process> data, string file  = "", string & sumaryOutPut = string(""));
void SJFNP(vector<Process> data, string file  = "", string & sumaryOutPut = string(""));


void main()
{

	do
	{
		cout<<"******* Deterministic Modeling *********"<<endl
			<<"* This program compares the eficency of *"<<endl
			<<"* various scheduling algorithms.        *"<<endl
			<<"*****************************************"<<endl<<endl;

		cout<<"* Chose your mode:"<<endl
			<<"*  1.) Single algorithm performance evaluation."<<endl
			<<"*  2.) Algorithm comparing."<<endl
			<<"*"<<endl
			<<"*  Your choice(1,2): ";

		int userChoice = 0;

		cin>>userChoice;

		
		switch(userChoice)
		{
		case 1:
			{

				// Prepare storage structures. 
				int continueConditon = 1;
				vector<Process> data;

				generateData(data);

				while(continueConditon == 1)
				{
					cout<<endl<<endl
						<<"* Chose an algorithm:"<<endl
						<<"*  1.) FCFS"<<endl
						<<"*  2.) SJF(non-preemptive)"<<endl
						<<"*  3.) SJF(preemptive)"<<endl
						<<"*"<<endl
						<<"*  Your choice(1,2): ";

					cin>>userChoice;

					if(userChoice == 1)
					{
						// FCFS
						FCFS(data,"FCFS.txt");
					}
					else if(userChoice == 2)
					{
						//SJF(non-preemptive)
						SJFNP(data,"SJFNP.txt");
					}
					else
					{
						//SJF(preemptive)

						SJFP(data,"SJFP.txt");
					}
					
					resetData(data);

					cout<<"Would you like to try this again with another algorithm (1 = yes): ";
					cin>>continueConditon;
				}
			}

			break;
		case 2:
			cout<<endl<<endl
				<<"* Chose algorithms to compare:"<<endl
				<<"*  1.) FCFS"<<endl
				<<"*  2.) SJF(non-preemptive)"<<endl
				<<"*  3.) SJF(preemptive)"<<endl
				<<"*"<<endl
				<<"*  Your choices(seperate by spaces, press CTRL+Z to end): ";

			{
				int count = 0;

				int choices[3] = {-1,-1,-1};

				while(cin>>choices[count] && count < 3)
				{
					count++;
				}

				
				// Prepare storage structures. 
				vector<Process> data;

				generateData(data);

				cout<<"\nPlease wait.."<<endl;
				
				string fcfs("notnull"),sjfnp("notnull"),sjfp("notnull");

				for(int i = 0; i < count; i++)
				{
					if(choices[i] == 1)
					{
						FCFS(data,"FCFS.txt",fcfs);
					}
					else if(choices[i] == 2)
					{
						SJFNP(data,"SJFNP.txt",sjfnp);
					}
					else if(choices[i] == 3)
					{
						SJFP(data,"SJFP.txt",sjfp);
					}

					// Make it so all three algorithms can use the same data.
					resetData(data);
				}

				ofstream fileOut;

				fileOut.open("algcmp.txt");

				fileOut<<"******** RESULTS **********"<<endl;


				if(sjfp.size() != NULL)
				{

					fileOut<<sjfp<<endl;

				}

				if(sjfnp.size() != NULL)
				{

					fileOut<<sjfnp<<endl;

				}

				if(fcfs.size() != NULL)
				{

					fileOut<<fcfs<<endl;

				}

				fileOut.close();

				cout<<endl<<"These results will be stored in a file called algcmp.txt"<<endl<<endl<<endl;
				
			}

			break;
		default:
			break;
		}
		
		cin.clear();
		cin.ignore(1);

	}while(true);

}
