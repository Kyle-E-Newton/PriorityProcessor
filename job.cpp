#include "main.hpp"

Job::Job(int ID, string Description, int processorsNeeded, int TicksToComplete){
    this->ID = ID;
    this->description = Description;
    this->processors = processorsNeeded;
    this->timeToComplete = TicksToComplete;
}

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

int Job::getTicksRemaining() {
    return this->timeToComplete;
}

int Job::getID(){
    return this->ID;
}

string Job::getDescription() {
    return this->description;
}

void Job::setDescription(string newDescription) {
    this->description = newDescription;
}

void Job::setTicks(int newTicks) {
    this->timeToComplete = newTicks;
}