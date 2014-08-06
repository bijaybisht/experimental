H := computer.hh job.hh resource.hh scheduler.hh user.hh
SRC := simulator.cc 

simulator: ${SRC} ${H}
	g++ ${SRC} -o simulator

clean:
	rm simulator
