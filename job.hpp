#pragma once
#include "queue.hpp"

//This Class is a container to contain the Jobs that are being inputted into either storage structure
class Job {
    public:
        Job(int ID, std::string Description, int processorsNeeded, int TicksToComplete);
        bool removeTick();
        int getTicksRemaining();
        int getID();
        int getProcessorsNeeded();
        std::string getDescription();
        friend std::ostream &operator<<(std::ostream &output, const Job &J1) {
            Job out = J1;
            output << "ID: " << out.getID() << " with description " << out.getDescription() << " with processors needed: " << out.getProcessorsNeeded() << " and " << out.getTicksRemaining() << " ticks remaining";
            return output;
        }
        friend bool operator<(const Job &J1, const Job &J2) {
            return J1.processors < J2.processors;
        }
        friend bool operator>(const Job &J1, const Job &J2) {
            return J1.processors > J2.processors;
        }
    private:
        std::string description;
        int processors;
        int timeToComplete;
        int ID;
};