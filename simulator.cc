#include <iostream>

#include "job.hh"
#include "user.hh"
#include "computer.hh"
#include "scheduler.hh"

int main (int argc, char **argv)
{
    uint no_of_computers = 10;
    uint no_of_resources = 10;
    uint max_steps = 10;
    uint duration = 1000;
    Computer *computers[no_of_computers];

    std::cout << "Simulator Output: " << std::endl;

    for (int i=0; i < no_of_computers; i++) {
        computers[i] = new Computer(no_of_resources);
    }

    User *user = new User(no_of_computers * no_of_resources * 5, no_of_resources, max_steps);

    Scheduler scheduler(user, no_of_computers, computers);

    while (--duration) {
        scheduler.recieve();
        scheduler.schedule();
    }
}
