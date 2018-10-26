#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <list>
#include <functional>
#include <fstream>
#include <sstream>

#include "job.hpp"

using namespace std;

void printMenu();

//This is the loader class. Originally built as a test, but ultimatley turned into the entire build
class testLoader {
    public:
        testLoader(int numProcessors);
        bool insertJob(int ID, std::string description, int processors, int ticks);
        bool checkValidity(int processorsNeeded);
        int getNumJobs();
        priority_queue<Job, vector<Job>, greater<Job>> getJobQueue();
        void printActiveJobs();
        void printAllJobs(const priority_queue<Job, vector<Job>, greater<Job>> &pq);
        void decrementJobs();
        void activatejob();
		bool hasActiveJobs();
		void tick();
    private:
        priority_queue<Job, vector<Job>, greater<Job>> jobs;
        vector<Job> currentJobs;

    int totalProcessors;
    int usedProcessors;
    int totalJobs;
	int totalTicks;
	int allJobs;
	bool canReadFromFile;
};