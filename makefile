gpp: main.cc password_solver.h
	g++ main.cc password_solver.h -lcrypt -fopenmp
mpi: main.cc password_solver.h
	mpic++ main.cc password_solver.h -lcrypt
run: main.cc password_solver.h
	time mpiexec -np 1 -host jcirino@odd31.cs.ohio.edu a.out
ssh:
	ssh jcirino@sp-015.cs.ohio.edu
	ssh jcirino@sp-001.cs.ohio.edu
	ssh jcirino@sp-002.cs.ohio.edu
	ssh jcirino@sp-003.cs.ohio.edu
	ssh jcirino@sp-004.cs.ohio.edu
	ssh jcirino@sp-005.cs.ohio.edu
	ssh jcirino@sp-006.cs.ohio.edu
	ssh jcirino@sp-017.cs.ohio.edu
	ssh jcirino@sp-018.cs.ohio.edu
	ssh jcirino@odd31.cs.ohio.edu