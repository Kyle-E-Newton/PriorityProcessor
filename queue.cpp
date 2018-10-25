#include "queue.hpp"

/*
int main(void) {

    bool isRunning = true;
	bool showMenu = true;
    int choice;

    testLoader loader(15);

    while(isRunning) {
        std::string description;
        int processors, ticks;
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
				if (loader.checkValidity(processors)) {
					loader.insertJob(loader.getNumJobs(), description, processors, ticks);
					break;
				}
				else {
					break;
				}
				break;
			case 2:
				break;
			case 3:
				loader.printActiveJobs();
				cin.ignore().get();
				break;
			case 4:
				loader.printAllJobs(loader.getJobQueue());
				cin.ignore().get();
				break;
			case 5:
				showMenu = false;
				break;
			default:
				cout << "Invalid Option" << "\n";
			}
		}
		if (!loader.hasActiveJobs() && loader.getJobQueue().empty())
			isRunning = false;
        loader.decrementJobs();
        loader.activatejob();
    }
    return 0;
}
*/

//Creates a Loader with x amount of processors
testLoader::testLoader(int numProcessors) {
    this->totalProcessors = numProcessors;
    this->usedProcessors = 0;
}

//Inserts a job into the storage queue
bool testLoader::insertJob(int ID, std::string description, int processors, int ticks) {
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

	if (hasActiveJobs()) {
		for (; it != currentJobs.end(); ) {
			if (it->removeTick()) {
				cout << "Job #" << it->getID() << " is finished\n";
				usedProcessors -= it->getProcessorsNeeded();
				it = currentJobs.erase(it);
			}
			else
				++it;
		}
	}
}

//Returns true if the active jobs list is not empty
bool testLoader::hasActiveJobs() {
	return !currentJobs.empty();
}

//Prints Menu
void printMenu() {
    cout << "1. Insert New Job" << "\n";
    cout << "2. Do Not Insert a Job" << "\n";
    cout << "3. List Active Jobs" << "\n";
    cout << "4. List All Jobs" << "\n";
    cout << "5. Run Program Until All Jobs are Completed" << "\n";
}
