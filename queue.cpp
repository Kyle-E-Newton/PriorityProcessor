#include "queue.hpp"


void testLoader::tick() {

	cout << "Tick Number: " << totalTicks << "\n";

	//Read from File
	ifstream stream;
	stream.open("Input.txt", ios::in);
	std::string readIn;
	std::string description = "";
	int processors = 0, ticks = 0, counter = 0;

	while (counter <= totalTicks) {
		if (counter == totalTicks) {
			stream >> description >> processors >> ticks;
		}
		counter++;
	}

	if(checkValidity(processors)) {
		insertJob(totalJobs, description, processors, ticks);
	}

	activatejob();
	decrementJobs();

	totalTicks++;
}
/*
void testLoader::tick() {

    bool isRunning = true;
	bool showMenu = true;
    int choice, tickTimer = 0;

    while(isRunning) {
        std::string description;
        int processors, ticks;

		cout << "\nTick Number :" << tickTimer << "\n";

		if (showMenu) {
			printMenu();
			cin >> choice;
			switch (choice) {
			case 1:
				//cout << "Option 1" << "\n";
				cout << "Enter Job Description: ";
				cin >> description;
				cout << "Enter the Number of Processors Needed: ";
				cin >> processors;
				cout << "Enter the Number of Ticks Needed: ";
				cin >> ticks;
				if (checkValidity(processors)) {
					insertJob(totalJobs, description, processors, ticks);
					break;
				}
				else {
					break;
				}
				break;
			case 2:
				break;
			case 3:
				printActiveJobs();
				cin.ignore().get();
				break;
			case 4:
				printAllJobs(jobs);
				cin.ignore().get();
				break;
			case 5:
				showMenu = false;
				break;
			default:
				cout << "Invalid Option" << "\n";
			}
		}
		if (!hasActiveJobs() && jobs.empty())
			isRunning = false;
        decrementJobs();
        activatejob();
    }
}
*/

//Creates a Loader with x amount of processors
testLoader::testLoader(int numProcessors) {
    this->totalProcessors = numProcessors;
    this->usedProcessors = 0;
	this->totalTicks = 0;
	this->allJobs = 0;
	this->canReadFromFile = true;
}

//Inserts a job into the storage queue
bool testLoader::insertJob(int ID, std::string description, int processors, int ticks) {
	cout << "Inserting Job #" << ID << " With Description " << description << "\n";
    Job newJob(ID, description, processors, ticks);
    this->totalJobs++;
    jobs.push(newJob);
	return true;
}

//Checks the validity of the Job to be processed by checking if there are enough total processors
bool testLoader::checkValidity(int processorsNeeded) {
    if(processorsNeeded <= totalProcessors){
        return true;
    }
    else {
        cout << "Invalid Job\n";
        return false;
    }
}

//Returns the number of total jobs in both queues
int testLoader::getNumJobs() {
    return this->totalJobs;
}

//This prints the jobs that are currently in the active queue
void testLoader::printActiveJobs() {
    for(auto i = currentJobs.begin(); i != currentJobs.end(); ++i) {
		cout << *i << "\n";
    }
}

//Prints all jobs that have not been completed
void testLoader::printAllJobs(const priority_queue<Job, vector<Job>, greater<Job>> &pq) {
	if (!currentJobs.empty()) {
		printActiveJobs();
	}
	if (!pq.empty()) {
		priority_queue<Job, vector<Job>, greater<Job>> q = pq;
		int size = q.size();
		for (int i = 0; i < size; i++) {
			cout << q.top() << "\n";
			q.pop();
		}
	}
}

//Returns the job Queue
priority_queue<Job, vector<Job>, greater<Job>> testLoader::getJobQueue(){
    return this->jobs;
}

//Adds any possible jobs to the active list
void testLoader::activatejob() {
    bool canAdd = true;

    while(canAdd && !jobs.empty()) {
        Job toAdd = jobs.top();
        if(toAdd.getProcessorsNeeded() <= totalProcessors-usedProcessors) {
            currentJobs.push_back(toAdd);
			usedProcessors += toAdd.getProcessorsNeeded();
			jobs.pop();
        }
        else
            canAdd = false;
    }
}

//Decrements the ticks remaining in any active jobs
void testLoader::decrementJobs() {
	vector<Job>::iterator it = currentJobs.begin();

	if (activeJobs()) {
		for (; it != currentJobs.end(); ) {
			if (it->removeTick()) {
				cout << "Job #" << it->getID() << " is finished\n";
				usedProcessors -= it->getProcessorsNeeded();
				it = currentJobs.erase(it);
				totalJobs--;
			}
			else
				++it;
		}
	}
}

//Returns true if there are no active jobs
bool testLoader::activeJobs() {
	return currentJobs.empty();
}

//Prints Menu
void printMenu() {
    cout << "1. Insert New Job" << "\n";
    cout << "2. Do Not Insert a Job" << "\n";
    cout << "3. List Active Jobs" << "\n";
    cout << "4. List All Jobs" << "\n";
    cout << "5. Run Program Until All Jobs are Completed" << "\n";
}

