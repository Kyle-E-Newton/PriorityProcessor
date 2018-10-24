#include "main.hpp"

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
				//cout << "Option 2" << "\n";
				break;
			case 3:
				//cout << "Option 3" << "\n";
				loader.printActiveJobs();
				cin.ignore().get();
				break;
			case 4:
				//cout << "Option 4" << "\n";
				loader.printAllJobs(loader.getJobQueue());
				cin.ignore().get();
				break;
			case 5:
				//cout << "Option 5" << "\n";
				showMenu = false;
				if (loader.hasActiveJobs())
					isRunning = false;
				
				break;
			default:
				cout << "Invalid Option" << "\n";
			}
		}
        loader.decrementJobs();
        loader.activatejob();

    }
    return 0;
}

testLoader::testLoader(int numProcessors) {
    this->totalProcessors = numProcessors;
    this->usedProcessors = 0;
}

bool testLoader::insertJob(int ID, std::string description, int processors, int ticks) {
    Job newJob(ID, description, processors, ticks);
    this->totalJobs++;
    jobs.push(newJob);
	return true;
}

bool testLoader::checkValidity(int processorsNeeded) {
    if(processorsNeeded <= totalProcessors){
        return true;
    }
    else {
        cout << "Invalid Job\n";
        return false;
    }
}

int testLoader::getNumJobs() {
    return this->totalJobs;
}

void testLoader::printActiveJobs() {
    for(auto i = currentJobs.begin(); i != currentJobs.end(); ++i) {
		cout << *i << "\n";
    }
}

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

priority_queue<Job, vector<Job>, greater<Job>> testLoader::getJobQueue(){
    return this->jobs;
}

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

void testLoader::decrementJobs() {
	vector<Job>::iterator it = currentJobs.begin();

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

bool testLoader::hasActiveJobs() {
	return currentJobs.empty();
}

void printMenu() {
    cout << "1. Insert New Job" << "\n";
    cout << "2. Do Not Insert a Job" << "\n";
    cout << "3. List Active Jobs" << "\n";
    cout << "4. List All Jobs" << "\n";
    cout << "5. Run Program Until All Jobs are Completed" << "\n";
}

