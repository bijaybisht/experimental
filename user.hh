#pragma once
#include <iostream>

#include "job.hh"

class User {
public:
    User(signed int max_load, unsigned int max_size, unsigned int max_steps): 
        _max_load(max_load),
        _max_size(max_size), 
        _max_steps(max_steps) {}

    Job *job() {
        if (_max_load <= 0) return NULL;

        int size  = rand() % _max_size + 1;
        int steps = rand() % _max_steps + 1;

        _max_load -= (size * steps);

        return new Job(size, steps);
    }

    void update(unsigned int work_done) {
        _max_load += work_done;
    }

private:
    signed int _max_load;

    unsigned int _max_size;
    unsigned int _max_steps;
};
