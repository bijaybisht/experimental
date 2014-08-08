#pragma once

#include <list>
#include <string>

#include "resource.hh"
#include "job.hh"
#include "window.hh"

class Computer {
public:
    
    Computer(unsigned int num_resources): _longest(0), _available(num_resources), _resources() {
        static unsigned int id;
        _id = ++id;
        //std::cout << "id " << _id << std::endl;
        unsigned int num = num_resources;
        while (num--) _resources.push_back(new Resource());
    }

    unsigned int clock() {
        _available = 0;
        unsigned int used = 0;
        std::list<Resource*>::iterator it;

        Window::coloron(_id);

        for (it = _resources.begin(); it != _resources.end(); it++) {
            Resource *r = *it;

            Window::plot( _id + r->id , r->load());

            used += r->clock();
            if (r->load() == 0) ++_available;
        }

        Window::coloroff(_id);

        _longest?--_longest:0;
        return used;
    }

    void add(Job *j) {
        //std::cout << "Adding job " << std::endl;
        //std::cout << "Available " << _available << std::endl;

        unsigned int remaining = j->size();
        std::list<Resource*>::iterator it;
        for (it = _resources.begin(); remaining; it++) {
            Resource *r = *it;
            if (r->load() == 0) {
                --remaining;
                --_available;
                r->load(j->steps());
            }
        }

        //std::cout << "Available " << _available << std::endl;

        _longest = _longest > j->steps() ? _longest: j->steps();
    }

    unsigned int longest() { return _longest; }
    unsigned int available() { return _available; }

    unsigned int _id;
private:
    unsigned int _longest;
    unsigned int _available;
    std::list<Resource*> _resources;
};
