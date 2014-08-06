#pragma once

class Resource {
public:
    Resource(): 
        _steps(0)
        {}
    
    void load(unsigned steps) { _steps = steps; }
    unsigned load() { return _steps; }
    unsigned clock() {
        unsigned used = _steps ? 1 : 0;
        _steps ? --_steps : 0;
        return used;
    }

private:
    unsigned int _steps;
};
