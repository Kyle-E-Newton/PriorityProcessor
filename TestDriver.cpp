#include "queue.hpp"

//Main class
int main(void) {

	//Read from file

	bool isRunning = true;

	testLoader loader(10);
	while (isRunning) {
		loader.tick();
		//Have 
		//No Jobs in Active Queue
		//No Jobs in Storage Queue
		if (!loader.getJobQueue().empty() && !loader.activeJobs()) {
			isRunning = false;
		}
		system("PAUSE");
		
	}
	
}