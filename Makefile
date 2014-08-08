H := computer.hh job.hh resource.hh scheduler.hh user.hh window.hh
SRC := simulator.cc 

simulator: ${SRC} ${H}
	g++ ${SRC} -o simulator -lncurses

clean:
	rm simulator
