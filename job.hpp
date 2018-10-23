#pragma once
#include "main.hpp"

class Job {
    public:
        Job(int ID, string Description, int processorsNeeded, int TicksToComplete);
        bool removeTick();
        int getTicksRemaining();
        int getID();
        string getDescription();
        void setDescription(string newDescription);
        void setTicks(int newTicks);
    private:
        string description;
        int processors;
        int timeToComplete;
        int ID;
};