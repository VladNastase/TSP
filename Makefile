O_SRCS = tsp.o 
CPP_SRCS = algo_test.cpp tsp.cpp algo.cpp print.cpp util.cpp algo2.cpp
CFLAGS = -O2
OBJS = tsp.o print.o util.o
LIBS = -lm -L/usr/include -lpthread
	

algo.o: algo.cpp
	g++ algo.cpp -c $(CFLAGS)

algo2.o: algo2.cpp
	g++ algo2.cpp -c $(CFLAGS)

tsp.o: tsp.cpp
	g++ tsp.cpp -c $(CFLAGS)

util.o: util.cpp
	g++ util.cpp -c $(CFLAGS)

print.o: print.cpp
	g++ print.cpp -c $(CFLAGS) -o print.o

algo_test_best.o: algo_test.cpp
	g++ algo_test.cpp -c -D BEST $(CFLAGS) -o algo_test_best.o

algo_test.o: algo_test.cpp
	g++ algo_test.cpp -c $(CFLAGS)

tsp: $(OBJS) algo_test.o algo2.o
	g++ -o "tsp" $(OBJS) algo_test.o algo2.o $(LIBS) 

best: $(OBJS) algo_test_best.o algo.o
	g++ -o "tsp_best" $(OBJS) algo_test_best.o algo.o $(LIBS)

all: tsp

clean:
	rm -f tsp tsp_best *.o

