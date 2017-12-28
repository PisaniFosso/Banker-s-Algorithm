/***************************************************************************************************************
Autor: Pisani Fosso                                                                                            *
****************************************************************************************************************
Description: Create a program that will solve the banker’s algorithm.                                          *	
			 This algorithm stops deadlocks from happening by not allowing processes						   *
			 to start if they don’t have access to the resources necessary to finish.						   *
			 A process is allocated certain resources from the start, and there are other available resources. *
			 In order for the process to end, it has to have the maximum resources in each slot.			   *
****************************************************************************************************************
*/
#include <iostream>
#include <fstream>
using namespace std;

//type will be use to keep runningTime and position of tasks.
struct task
{
	int runningTime;
	int Position;
};


/***************************************************************************************************************
class name: Banker                                                                                             *
****************************************************************************************************************
Description: This class take is used to solve our banker's algorithm if its possible or stop the process when  *
			 it's not possible.                                                                                *
****************************************************************************************************************
*/
class Banker
{
private:
	int sizeOfTable;
	int timeAvailable;
	task *order;
public:
	void swap (task&, task&);
	void orderTask (int*&, int*&);
	void showExecution (int[]);
	Banker(int, int);
	~Banker();
};

/***************************************************************************************************************
function name: swap                                                                                            *
****************************************************************************************************************
Description: This function take 2 taks and swap them                                                           *
****************************************************************************************************************
*/
void Banker::swap(task& elt1, task& elt2)
{
	task temp = elt1;
	elt1 = elt2;
	elt2 = temp;
}

/***************************************************************************************************************
function name: orderTask                                                                                       *
****************************************************************************************************************
Description: This function take time allocated and the max time for each task in the .txt file and order them  *
			 by runningTime from the less to the bigger                                                        *
****************************************************************************************************************
*/
void Banker::orderTask(int*& timeAllocated, int*& timeMax)
{
	for(int i = 0; i < sizeOfTable; i++)
	{
		//runningTime = max time - allocated time
		order[i].runningTime = timeMax[i] - timeAllocated[i];
		order[i].Position = i;

		//order task
		for(int j = 0; j < i; j++)
		{
			if(order[j].runningTime > order[i].runningTime)
				swap(order[j], order[i]);
		}
	}
}

/***************************************************************************************************************
function name: showExecution                                                                                   *
****************************************************************************************************************
Description: This function take time allocated for each task in the .txt file and show them by how the are
			 going to proceed in the buffer                                                                    *
****************************************************************************************************************
*/
void Banker:: showExecution(int timeAllocated[])
{
	for(int i = 0; i < sizeOfTable; i++)
	{
		//if the running time of a task is greater than the time available, the task won't proceed
		if(order[i].runningTime > timeAvailable)
		{
			cout<<endl;
			cout<<"Not enough space to complete de algorithm"<<endl;
			return;
		}
		else
		{
			cout<<"P"<<order[i].Position<<" ";
			timeAvailable += timeAllocated[i];
		}
	}
	cout<<endl;
}

Banker::Banker(int size, int available)
{
	sizeOfTable = size;
	timeAvailable = available;
	order = new task [size];
}

Banker::~Banker()
{
	delete [] order;
}

int main ()
{
	//Open the file to remove the inputs
	ifstream myFile;
	myFile.open("Bankers.txt");

	if(myFile)
	{
		//number of request
		int numberOfRequest;
		myFile>>numberOfRequest;

		//table of requests
		int available;
		myFile>>available;

		int *allocation  = new int [numberOfRequest];
		int *max = new int [numberOfRequest];
		
		//initialise table with requests
		for(int i = 0; i < numberOfRequest; i++)
		{
				myFile>>allocation[i];
				myFile>>max[i];
		}

		Banker Algorithm(numberOfRequest, available);
		Algorithm.orderTask(allocation, max);
		Algorithm.showExecution(allocation);
		delete []max;
		delete []allocation;
	}
	else cerr<<"Error"<<endl;

	return 0;
}