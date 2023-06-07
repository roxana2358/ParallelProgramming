PROC_NUM := 4
THREAD_NUM := 4


tests: tests10-10 tests10-3000 tests100-10 tests1000-50 tests3600-100 tests3600-1000 tests5000-3000 tests10000-3000 tests100000-3000 tests100000-5


serial: serial.c
	gcc -Wall serial.c -o serial.o

mpi: mpi.c
	mpicc -g -Wall mpi.c -o mpi.o -lm

omp: omp.c
	gcc -g -Wall -fopenmp omp.c -o omp.o

all: serial mpi omp

clean:
	rm serial.o
	rm mpi.o
	rm omp.o

cleantests:
	rm outs/*

.PHONY: clean, all, tests, cleantests

tests10-10:
	$(info Currently executing 10 packets 10 patterns test)
	./serial.o packets/file10.txt patterns/pattern10.txt > outs/outS10-10.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file10.txt patterns/pattern10.txt > outs/outM10-10.txt
	./omp.o packets/file10.txt patterns/pattern10.txt $(THREAD_NUM) > outs/outO10-10.txt

tests100-10:
	$(info Currently executing 100 packets 10 patterns test)
	./serial.o packets/file100.txt patterns/pattern10.txt > outs/outS100-10.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file100.txt patterns/pattern10.txt > outs/outM100-10.txt
	./omp.o packets/file100.txt patterns/pattern10.txt $(THREAD_NUM) > outs/outO100-10.txt

tests1000-50:
	$(info Currently executing 1000 packets 50 patterns test)
	./serial.o packets/file1000.txt patterns/pattern50.txt > outs/outS1000-50.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file1000.txt patterns/pattern50.txt > outs/outM1000-50.txt
	./omp.o packets/file1000.txt patterns/pattern50.txt $(THREAD_NUM) > outs/outO1000-50.txt

tests3600-50:
	$(info Currently executing 3600 packets 50 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern50.txt > outs/outS3600-50.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern50.txt > outs/outM3600-50.txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern50.txt $(THREAD_NUM) > outs/outO3600-50.txt

tests3600-100:
	$(info Currently executing 3600 packets 100 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern100.txt > outs/outS3600-100.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern100.txt > outs/outM3600-100.txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern100.txt $(THREAD_NUM) > outs/outO3600-100.txt

tests3600-1000:
	$(info Currently executing 3600 packets 1000 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern1000.txt > outs/outS3600-1000.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern1000.txt > outs/outM3600-1000.txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern1000.txt $(THREAD_NUM) > outs/outO3600-1000.txt

tests3600-3000:
	$(info Currently executing 3600 packets 3000 patterns test)
	./serial.o packets/alice_in_wonderland.txt patterns/pattern3000.txt > outs/outS3600-3000.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/alice_in_wonderland.txt patterns/pattern3000.txt > outs/outM3600-3000.txt
	./omp.o packets/alice_in_wonderland.txt patterns/pattern3000.txt $(THREAD_NUM) > outs/outO3600-3000.txt

tests5000-100:
	$(info Currently executing 5000 packets 100 patterns test)
	./serial.o packets/file5000.txt patterns/pattern100.txt > outs/outS5000-100.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file5000.txt patterns/pattern100.txt > outs/outM5000-100.txt
	./omp.o packets/file5000.txt patterns/pattern100.txt $(THREAD_NUM) > outs/outO5000-100.txt

tests5000-3000:
	$(info Currently executing 5000 packets 3000 patterns test)
	./serial.o packets/file5000.txt patterns/pattern3000.txt > outs/outS5000-3000.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file5000.txt patterns/pattern3000.txt > outs/outM5000-3000.txt
	./omp.o packets/file5000.txt patterns/pattern3000.txt $(THREAD_NUM) > outs/outO5000-3000.txt

tests10000-3000:
	$(info Currently executing 10000 packets 3000 patterns test)
	./serial.o packets/file10000.txt patterns/pattern3000.txt > outs/outS10000-3000.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file10000.txt patterns/pattern3000.txt > outs/outM10000-3000.txt
	./omp.o packets/file10000.txt patterns/pattern3000.txt $(THREAD_NUM) > outs/outO10000-3000.txt

tests100000-3000:
	$(info Currently executing 100000 packets 3000 patterns test)
	./serial.o packets/file100000.txt patterns/pattern3000.txt > outs/outS100000-3000.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file100000.txt patterns/pattern3000.txt > outs/outM100000-3000.txt
	./omp.o packets/file100000.txt patterns/pattern3000.txt $(THREAD_NUM) > outs/outO100000-3000.txt

tests100000-5:
	$(info Currently executing 100000 packets 5 patterns test)
	./serial.o packets/file100000.txt patterns/pattern5.txt > outs/outS100000-5.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file100000.txt patterns/pattern5.txt > outs/outM100000-5.txt
	./omp.o packets/file100000.txt patterns/pattern5.txt $(THREAD_NUM) > outs/outO100000-5.txt

tests10-3000:
	$(info Currently executing 10 packets 3000 patterns test)
	./serial.o packets/file10.txt patterns/pattern3000.txt > outs/outS10-3000.txt
	mpiexec -n $(PROC_NUM) ./mpi.o packets/file10.txt patterns/pattern3000.txt > outs/outM10-3000.txt
	./omp.o packets/file10.txt patterns/pattern3000.txt $(THREAD_NUM) > outs/outO10-3000.txt