Simulator Project:

For simulating/testing specific scheduling algorithm.

1. User class generates the load. It restricts itself to generating upto a maximum (soft limit) load. The load is characterized by (resource, duration).

2. Computer class which has x resouces.

3. Resource class which bookeeps the duration for which it is loaded. The load is decremented at every tick. A value of 0 implies it is availble.

4. Job class which represents a job with the following attributes
	-	size (no of resources it needs on a computer)
	-	steps (the duration for which it needs it)

5. Scheduler class, this class takes a users job at every tick, and schedules them on the computers. It seeks jobs from the users based on max new jobs it wants to take,
and the capacity available (sum of all the resources on the computer). It then schedules them and moves the clock.

	-	It prints the following metrics at every tick 
'''
new load: 80
allocation done : 40| capacity available: 16| oldest: 20| total_age: 116
total: 86762| capacity available: 43| work done : 84| jobs_queue : 14| queue : 420
'''
	new load : The total of size * step of the new jobs submitted.

	allocation done: The portition of the new load that has been allocated resources.
	capacity available: The capacity (total resources) that is available after allocation.
	oldest: The oldest job in the queue. It is measured as the number of schedule events since the event was submitted.
	total_age: The total age of the jobs in the queue (unscheduled).

	total: This is the work done in the 1000 cycles of (10 x 10) total resources.
	capacity availabe: The capacity available after the latest cycle.
	work done: Total work done (resources utilized) in the last cycle.
	job_queue: Jobs in the queue.

	queue: Total worth of the jobs in the queue (resource * duration)

6. There are a few knobs avaialble to control the job generation and scheduling. (Not configurable though).

7. The scheduling algorithm aims to maximize the throughput while controlling the starvation.

8. Added a dynamic ui using curses.
