#pragma once

class Resource {
public:
    Resource(): _steps(0) {
        static unsigned int i;
        id = ++i;
    }
    
    void load(unsigned steps) { _steps = steps; }
    unsigned load() { return _steps; }
    unsigned clock() {
        unsigned used = _steps ? 1 : 0;
        _steps ? --_steps : 0;
        return used;
    }
    unsigned int id;
private:
    unsigned int _steps;
};
