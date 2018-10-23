#include "main.hpp"

int main(void) {

    bool isRunning;
    int choice;

    testLoader loader();

    while(isRunning) {
        printMenu();
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Option 1" << "\n";
                break;
            case 2:
                cout << "Option 2" << "\n";
                break;
            case 3:
                cout << "Option 3" << "\n";
                break;
            default:
                cout << "Invalid Option" << "\n";
        }

    }

    return 0;
}

testLoader::testLoader(int numProcessors) {
    this->totalProcessors = numProcessors;
}

bool testLoader::insertJob(int ID, string description, int processors, int ticks) {

}

void printMenu() {
    cout << "1. Insert New Job" << "\n";
    cout << "2. Do Not Insert a Job" << "\n";
    cout << "Run Program Until All Jobs are Completed" << "\n";
}

