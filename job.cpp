#include "main.hpp"

//Main constructor. Takes in an ID, Description, How many processors needed and how many Ticks are needed to complete the 
//Process. This is just a basic constructore and doesn't do anything else
Job::Job(int ID, std::string Description, int processorsNeeded, int TicksToComplete){
    this->ID = ID;
    this->description = Description;
    this->processors = processorsNeeded;
    this->timeToComplete = TicksToComplete;
}

//This removes one processor tick from the job
//Returns true if the job is not finished and false if it is
bool Job::removeTick() {
    if(timeToComplete - 1 != 0){
        timeToComplete--;
        return false;
    }
    else {
        timeToComplete--;
        return true;
    }
}

//Returns how many ticks are remaining until the job is finished
int Job::getTicksRemaining() {
    return this->timeToComplete;
}

//Returns the Job ID
int Job::getID(){
    return this->ID;
}

//Returns the Description
std::string Job::getDescription() {
    return this->description;
}

//Returns how many processors are necessary for the Job
int Job::getProcessorsNeeded() {
    return this->processors;
}