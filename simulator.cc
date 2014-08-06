#include <iostream>
#include <list>



typedef unsigned int uint;
class Job {
public:
	Job(uint size_, uint steps_): size(size_), steps(steps_), scheduled(0), submitted(0) {}
//private:
	uint size;
	uint steps;
	uint submitted;
	uint scheduled;
};

class Resource {
public:
	Resource(): load(0){ }
	~Resource() {}
	uint clock() {
		uint used = load ? 1: 0;
		load ? --load: load;
		return used;
	}
	uint load;
private:
};

class Computer {
public:
	
	Computer(int num_resources): _num_resources(num_resources), _id(++sequence) { _resources = new Resource[_num_resources]; longest = 0; }
	uint clock() {
		available = 0;
		uint used = 0;
		for (int i=0; i<_num_resources; i++) {
			used += _resources[i].clock();
			longest --;
			if (_resources[i].load == 0) available++;
		}
		return used;
	}

	void add(Job *j) {
		uint remaining = j->size;
		for(int i=0;  remaining; i++) {
			if (_resources[i].load == 0) {
				--remaining;
				_resources[i].load +=j->steps;
			}
		}

		longest = longest > j->steps ? longest: j->steps;
	}

	static uint total;
	uint longest;
	uint available;
private:
	static uint sequence;
	uint _id;
	uint _num_resources;
	Resource *_resources;
};


class Jobs {
public:
	Jobs(signed int units_, uint max_size_, uint max_steps_): units(units_), max_size(max_size_), max_steps(max_steps_) {}
	Job *generate() {
		if (units <= 0) return NULL;

		int size  = rand() % max_size;
		int steps = rand() % max_steps;
		units -= (size * steps);
		return new Job(size, steps);
	}

	void addUnits(uint units_) {
		units += units_;
	}

//private:
	signed int units;
	uint max_size;
	uint max_steps;
};

uint Computer::sequence = 0;
uint Computer::total = 0;



class Scheduler {
public:
	Scheduler(Jobs *jobs_, Computer *computers_[]): jobs(jobs_), computers(computers_) {};
	void add() {
		Job *job = NULL ;
		while ((job=jobs->generate())) {
			jlist.push_back(job);
		}
	}
	void schedule() {
		jlist.sort(compare);
		std::list<Job*>::iterator itr = jlist.begin();
		while( itr != jlist.end())
		{
			Computer *theone = NULL;
			for (int i=0; i< Computer::total; i++) {
				Computer *c = computers[i];
				if (c->available > (*itr)->size) {
					theone = theone ? (theone->longest > c->longest ? theone: c): c;
				}
			}
			if (theone) {
				theone->add(*itr);
				jlist.erase(itr++);
			}
			else {
				++itr;
			}
		}
		uint useful_work = 0;
		for (int i=0; i< Computer::total; i++) {
			Computer *c = computers[i];
			useful_work += c->clock();
		}

		jobs->addUnits(useful_work);
		std::cout << "Useful Work : " << useful_work << std::endl;
	}
private:
	static bool compare(Job* &j1, Job* &j2) {
		if (j1->size > j2->size) return true;
		return (j1->steps > j2->steps);
	}

	Jobs *jobs;
	Computer **computers;
	std::list<Job*> jlist;
};

int main (int argc, char **argv)
{
	uint no_of_computers = 10;
	uint no_of_resources = 10;
	uint max_steps = 10;
	uint duration = 1000;
	Computer::total = no_of_computers;
	Computer *computers[no_of_computers];

	std::cout << "Simulator Output: " << std::endl;

	for (int i=0; i < no_of_computers; i++) {
		computers[i] = new Computer(no_of_resources);
	}

	Jobs *jobs = new Jobs(no_of_computers * no_of_resources, no_of_resources, max_steps);

	Scheduler scheduler(jobs,computers);

	while (--duration) {
		scheduler.add();
		scheduler.schedule();
	}

}
