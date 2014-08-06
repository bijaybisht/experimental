#pragma once
#include <iostream>

class Job {
public:
    Job(unsigned int size, unsigned int steps): 
        _size(size), 
        _steps(steps),
        _age(0) 
    {
        //std::cout << "Job[size: " << size << ", steps: " << steps << "]" << std::endl;
    }
    unsigned int size() { return _size; }
    unsigned int steps() { return _steps; }
    void age() { _age++; }
    unsigned int getAge() { return _age; }

private:
    unsigned int _size;
    unsigned int _steps;
    unsigned int _age;
};
