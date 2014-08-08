#include <iostream>
#include <list>
#include <sstream>

#include "job.hh"
#include "resource.hh"
#include "user.hh"
#include "computer.hh"

class Scheduler {
public:
    Scheduler(User *user,unsigned int num_of_computers, Computer *computers[]): _user(user), queue(0), total_work(0) {
        int num = num_of_computers;
        capacity = 0;
        while (num) { 
            Computer *c = computers[--num];
            _computers.push_back(c);
            capacity += c->available();
        }
    };

    void recieve() {
        Job *job = NULL;
        unsigned int num = 8;
        unsigned int newload = 0 ;
        unsigned int c = capacity;
        while (c && num && (job=_user->job())) {
            num --;
            _jobs.push_back(job);
            newload += job->size() * job->steps();
            c -= job->size();
        }
        queue += newload;
        //std::cout << std::endl;
        //std::cout << "new load: " << newload << std::endl;
        os.clear();
        os.str("");
        os.seekp(0);
        oj.clear();
        oj.str("");
        oj.seekp(0);
        oj << "jobs > ";

        os << "new load: " << newload << "\n";
    }

    void recieve1() {
        Job *job = NULL;
        unsigned int newload = 0 ;
        while ((job=_user->job())) {
            _jobs.push_back(job);
            newload += job->size() * job->steps();
        }
        queue += newload;
        std::cout << "new load: " << newload << std::endl;
    }

    void schedule() {
        _jobs.sort(joborder);
        _computers.sort(comorder);

        std::list<Job*>::iterator jptr = _jobs.begin();

        //std::cout << "_jobs size: " << _jobs.size() << std::endl;
        unsigned int newallocation = 0;
        unsigned int oldest = 0;
        unsigned int total_age = 0;

        unsigned j = 0;

        while (jptr != _jobs.end())
        {
            //std::cout << "allocating : " << std::endl;
            //std::cout << ">>> jobs size: " << (*jptr)->size() << std::endl;
            //std::cout << ">>> jobs step: " << (*jptr)->steps() << std::endl;
            Computer *target = NULL;
            std::list<Computer*>::iterator cit = _computers.begin();
            
            /* 
             * For smaller guys dont go all the way.
             */
            unsigned int allowed = _computers.size() * ((*jptr)->size() > 7? 1: 0.9);

            for (; cit != _computers.end() && target == NULL; ++cit, --allowed) {
                Computer *c = *cit;
                //std::cout << "------available: " << c->available() << std::endl;
                //std::cout << "------longest: " << c->longest() << std::endl;
                if (c->available() >= (*jptr)->size()) {
                    if (allowed || (c->longest() > (*jptr)->steps())) target = c;
                }
            }

            if (target) {
                newallocation += (*jptr)->size() * (*jptr)->steps();
                target->add(*jptr);
                capacity -= (*jptr)->size();
                _jobs.erase(jptr);
                /* mark */
                _computers.sort(comorder);
                ++jptr;
            }
            else {
                (*jptr)->age();
                oj << "(" << (*jptr)->size() << "-"<< (*jptr)->steps() << ")"; 
                total_age += (*jptr)->getAge();
                oldest = oldest > (*jptr)->getAge() ? oldest : (*jptr)->getAge();
                ++jptr;
            }
        }

        Window::jout(oj.str());

        //std::cout << "allocation done : " << newallocation;
        //std::cout << "| capacity available: " << capacity;
        //std::cout << "| oldest: " << oldest;
        //std::cout << "| total_age: " << total_age << std::endl;


        os << " allocation done " << newallocation;
        os << "| capacity available: " << capacity;
        os << "| oldest: " << oldest;
        os << "| total_age: " << total_age << "\n";

        unsigned int work_done = 0;
        capacity = 0;
        std::list<Computer*>::iterator cit = _computers.begin();

        Window::initdraw();

        for (; cit != _computers.end(); ++cit) {
            //os << (*cit)->_id;
            work_done += (*cit)->clock();
            capacity += (*cit)->available();
            //std::cout << "clocking - work_done: " << work_done << std::endl;
        }

        _user->update(work_done);
        queue -= work_done;
        total_work += work_done;

        //std::cout << "total: " << total_work;
        //std::cout << "| capacity available: " << capacity; 
        //std::cout << "| work done : " << work_done;
        //std::cout << "| jobs_queue : " << _jobs.size();
        //std::cout << "| queue : " << queue << std::endl;

        os << " total: " << total_work;
        os << "| capacity available: " << capacity;
        os << "| work done : " << work_done;
        os << "| jobs_queue : " << _jobs.size();
        os << "| queue : " << queue << "\n";

        Window::out(os.str());
        Window::wait();
    }

private:
    std::ostringstream os;
    std::ostringstream oj;
    static bool joborder(Job* &j1, Job* &j2) {

        if (j1->getAge() > (j2->getAge()<<5)) return true;

        if (j1->size() == j2->size()) {
            return (j1->steps() > j2->steps());
        }
        else {
            return (j1->size() > j2->size());
        }
    }

    static bool comorder(Computer* &c1, Computer* &c2) {
        if (c1->available() == c2->available()) {
            return (c1->longest() > c2->longest());
        }
        else {
            return (c1->available() < c2->available());
        }
    }
    
    unsigned int queue;
    unsigned int capacity;
    unsigned int total_work;

    User *_user;

    std::list<Computer*> _computers;
    std::list<Job*> _jobs;
};
