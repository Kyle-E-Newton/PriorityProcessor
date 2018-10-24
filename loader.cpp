#include "main.hpp"

int main(void) {

    bool isRunning = true;
    int choice;

    testLoader loader(15);

    while(isRunning) {
        std::string description;
        int processors, ticks;
        printMenu();
        cin >> choice;

        switch(choice) {
            case 1:
                //cout << "Option 1" << "\n";
                cout << "Enter Job Description: ";
                cin >> description;
                cout << "Enter the Number of Processors Needed: ";
                cin >> processors;
                cout << "Enter the Number of Ticks Needed: ";
                cin >> ticks;
                if(loader.checkValidity(processors)){
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
                isRunning = false;
                break;
            default:
                cout << "Invalid Option" << "\n";
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
    cout << this->totalJobs << "\n";
    jobs.push(newJob);
}

bool testLoader::checkValidity(int processorsNeeded) {
    if(processorsNeeded <= totalProcessors && processorsNeeded <= totalProcessors-usedProcessors){
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
        cout << "Job #" << i->getID() << "\n";
        cout << "Description: " << i->getDescription() << "\n";
        cout << "Processors: " << i->getProcessorsNeeded() << "\t" << "Ticks: " << i->getTicksRemaining() << "\n";
    }
}

void testLoader::printAllJobs(const priority_queue<Job, vector<Job>, greater<Job>> &pq) {
    priority_queue<Job, vector<Job>, greater<Job>> q = pq;
    cout << "Total Jobs: " << q.size() << "\n";
    for(int i = 0; i < totalJobs - 1; i++) {
        cout << q.top() << "\n";
        q.pop();
    }
}

priority_queue<Job, vector<Job>, greater<Job>> testLoader::getJobQueue(){
    return this->jobs;
}

void testLoader::activatejob() {
    bool canAdd;

    while(canAdd) {
        Job toAdd = this->getJobQueue().top();
        if(toAdd.getProcessorsNeeded() < totalProcessors-usedProcessors) {
            currentJobs.push_back(toAdd);
            this->getJobQueue().pop();
        }
        else
            canAdd = false;
    }
}

void testLoader::decrementJobs() {

}
void printMenu() {
    cout << "1. Insert New Job" << "\n";
    cout << "2. Do Not Insert a Job" << "\n";
    cout << "3. List Active Jobs" << "\n";
    cout << "4. List All Jobs" << "\n";
    cout << "5. Run Program Until All Jobs are Completed" << "\n";
}

