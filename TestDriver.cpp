#include "queue.hpp"

//Main class
int main(void) {

	//Read from file

	bool isRunning = true;

	testLoader loader(10);
	while (isRunning) {
		loader.tick();
		if (!loader.hasActiveJobs()) {
			isRunning = false;
		}
	}
}