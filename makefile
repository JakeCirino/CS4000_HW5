gpp: main.cc password_solver.h
	g++ main.cc password_solver.h -lcrypt -fopenmp
mpi: main.cc password_solver.h
	mpic++ main.cc password_solver.h -lcrypt
run: main.cc password_solver.h
	time mpiexec -np 1 -host jcirino@odd31.cs.ohio.edu a.out