gpp: main.cc password_solver.h
	g++ main.cc password_solver.h -lcrypt -fopenmp -O2
mpi: main.cc password_solver.h
	mpic++ main.cc password_solver.h -lcrypt