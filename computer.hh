#pragma once

#include <list>

#include "resource.hh"
#include "job.hh"

class Computer {
public:
	
	Computer(unsigned int num_resources): _longest(0), _available(num_resources) {
        unsigned int num = num_resources;
        while (num--) _resources.push_back(new Resource());
    }

	unsigned int clock() {
		_available = 0;
		unsigned int used = 0;
        std::list<Resource*>::iterator it;
		for (it = _resources.begin(); it != _resources.end(); it++) {
            Resource *r = *it;
			used += r->clock();
			if (r->load() == 0) ++_available;
		}
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

private:
	unsigned int _longest;
	unsigned int _available;
    std::list<Resource*> _resources;
};
