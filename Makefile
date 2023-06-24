INSTANCES := 3

tests: tests10-5 tests1000-5 tests100000-5 tests10-100 tests1000-100 tests100000-100 tests10-3000 tests1000-3000 tests100000-3000

performance: tests3600-5 tests3600-50 tests3600-100 tests3600-1000 tests3600-3000

serial: serial.c
	gcc -Wall serial.c -o serial.o

mpi: mpi.c
	mpicc -g -Wall mpi.c -o mpi.o -lm

mpiOrdered: mpi_ordered.c
	mpicc -g -Wall mpi_ordered.c -o mpi_ordered.o -lm
# mpiexec -n $(INSTANCES) ./mpi_ordered.o packets/file10.txt patterns/pattern10.txt > outs/outMOrdered10-10.txt

omp: omp.c
	gcc -g -Wall -fopenmp omp.c -o omp.o

all: serial mpi omp

clean:
	rm serial.o
	rm mpi.o
	rm omp.o

cleanouts:
	rm outs/*

.PHONY: clean, all, tests, cleantests, performance

tests10-5:
	$(info Currently executing 10 packets 5 patterns test)
	./serial.o packets/file10.txt patterns/pattern5.txt > outs/outS10-5.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file10.txt patterns/pattern5.txt > outs/outM10-5-$(INSTANCES).txt
	./omp.o packets/file10.txt patterns/pattern5.txt $(INSTANCES) > outs/outO10-5-$(INSTANCES).txt

tests1000-5:
	$(info Currently executing 1000 packets 5 patterns test)
	./serial.o packets/file1000.txt patterns/pattern5.txt > outs/outS1000-5.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file1000.txt patterns/pattern5.txt > outs/outM1000-5-$(INSTANCES).txt
	./omp.o packets/file1000.txt patterns/pattern5.txt $(INSTANCES) > outs/outO1000-5-$(INSTANCES).txt

tests100000-5:
	$(info Currently executing 100000 packets 5 patterns test)
	./serial.o packets/file100000.txt patterns/pattern5.txt > outs/outS100000-5.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file100000.txt patterns/pattern5.txt > outs/outM100000-5-$(INSTANCES).txt
	./omp.o packets/file100000.txt patterns/pattern5.txt $(INSTANCES) > outs/outO100000-5-$(INSTANCES).txt

tests10-100:
	$(info Currently executing 10 packets 100 patterns test)
	./serial.o packets/file10.txt patterns/pattern100.txt > outs/outS10-100.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file10.txt patterns/pattern100.txt > outs/outM10-100-$(INSTANCES).txt
	./omp.o packets/file10.txt patterns/pattern100.txt $(INSTANCES) > outs/outO10-100-$(INSTANCES).txt

tests1000-100:
	$(info Currently executing 1000 packets 100 patterns test)
	./serial.o packets/file1000.txt patterns/pattern100.txt > outs/outS1000-100.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file1000.txt patterns/pattern100.txt > outs/outM1000-100-$(INSTANCES).txt
	./omp.o packets/file1000.txt patterns/pattern100.txt $(INSTANCES) > outs/outO1000-100-$(INSTANCES).txt

tests100000-100:
	$(info Currently executing 100000 packets 100 patterns test)
	./serial.o packets/file100000.txt patterns/pattern100.txt > outs/outS100000-100.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file100000.txt patterns/pattern100.txt > outs/outM100000-100-$(INSTANCES).txt
	./omp.o packets/file100000.txt patterns/pattern100.txt $(INSTANCES) > outs/outO100000-100-$(INSTANCES).txt

tests10-3000:
	$(info Currently executing 10 packets 3000 patterns test)
	./serial.o packets/file10.txt patterns/pattern3000.txt > outs/outS10-3000.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file10.txt patterns/pattern3000.txt > outs/outM10-3000-$(INSTANCES).txt
	./omp.o packets/file10.txt patterns/pattern3000.txt $(INSTANCES) > outs/outO10-3000-$(INSTANCES).txt

tests1000-3000:
	$(info Currently executing 1000 packets 3000 patterns test)
	./serial.o packets/file1000.txt patterns/pattern3000.txt > outs/outS1000-3000.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file1000.txt patterns/pattern3000.txt > outs/outM1000-3000-$(INSTANCES).txt
	./omp.o packets/file1000.txt patterns/pattern3000.txt $(INSTANCES) > outs/outO1000-3000-$(INSTANCES).txt

tests100000-3000:
	$(info Currently executing 100000 packets 3000 patterns test)
	./serial.o packets/file100000.txt patterns/pattern3000.txt > outs/outS100000-3000.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/file100000.txt patterns/pattern3000.txt > outs/outM100000-3000-$(INSTANCES).txt
	./omp.o packets/file100000.txt patterns/pattern3000.txt $(INSTANCES) > outs/outO100000-3000-$(INSTANCES).txt

tests3600-5:
	$(info Currently executing 3600 packets 5 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern5.txt > outs/outS3600-5.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern5.txt > outs/outM3600-5-$(INSTANCES).txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern5.txt $(INSTANCES) > outs/outO3600-5-$(INSTANCES).txt

tests3600-50:
	$(info Currently executing 3600 packets 50 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern50.txt > outs/outS3600-50.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern50.txt > outs/outM3600-50-$(INSTANCES).txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern50.txt $(INSTANCES) > outs/outO3600-50-$(INSTANCES).txt

tests3600-100:
	$(info Currently executing 3600 packets 100 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern100.txt > outs/outS3600-100.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern100.txt > outs/outM3600-100-$(INSTANCES).txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern100.txt $(INSTANCES) > outs/outO3600-100-$(INSTANCES).txt

tests3600-1000:
	$(info Currently executing 3600 packets 1000 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern1000.txt > outs/outS3600-1000.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern1000.txt > outs/outM3600-1000-$(INSTANCES).txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern1000.txt $(INSTANCES) > outs/outO3600-1000-$(INSTANCES).txt

tests3600-3000:
	$(info Currently executing 3600 packets 3000 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern3000.txt > outs/outS3600-3000.txt
	mpiexec -n $(INSTANCES) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern3000.txt > outs/outM3600-3000-$(INSTANCES).txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern3000.txt $(INSTANCES) > outs/outO3600-3000-$(INSTANCES).txt

testsOrdered:
	$(info Currently executing 3600 packets ordered mpi tests)
	mpiexec -n $(INSTANCES) ./mpi_ordered.o packets/alice_in_wonderland.txt patterns/pattern5.txt > outs/outMOrd3600-5-$(INSTANCES).txt
	mpiexec -n $(INSTANCES) ./mpi_ordered.o packets/alice_in_wonderland.txt patterns/pattern50.txt > outs/outMOrd3600-50-$(INSTANCES).txt
	mpiexec -n $(INSTANCES) ./mpi_ordered.o packets/alice_in_wonderland.txt patterns/pattern100.txt > outs/outMOrd3600-100-$(INSTANCES).txt
	mpiexec -n $(INSTANCES) ./mpi_ordered.o packets/alice_in_wonderland.txt patterns/pattern1000.txt > outs/outMOrd3600-1000-$(INSTANCES).txt
	mpiexec -n $(INSTANCES) ./mpi_ordered.o packets/alice_in_wonderland.txt patterns/pattern3000.txt > outs/outMOrd3600-3000-$(INSTANCES).txt
