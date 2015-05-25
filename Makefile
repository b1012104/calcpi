OBJS = calcpi.o pthreadcalcpi.o ompcalcpi.o
PROGRAM = single pthread omp
CC=gcc

.PHONY: all
all: $(PROGRAM)

single: calcpi.o
	$(CC) $< -o $@

omp: ompcalcpi.o
	$(CC) -fopenmp $< -o $@

pthread: pthreadcalcpi.o
	$(CC) -lpthread $< -o $@

$(OJBS): %.o: %.c
	$(CC) -c $^

.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROGRAM)
