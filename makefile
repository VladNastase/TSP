RM = rm -rf
O_SRCS = tsp.o 
CPP_SRCS = algo_test.cpp tsp.cpp algo.cpp print.cpp util.cpp algo2.cpp
OBJS = algo_test.o tsp.o algo.o print.o util.o algo2.o
CPP_DEPS = algo_test.d tsp.d algo.d print.d util.d algo2.d
LIBS = -lm -L/usr/include -lpthread


%.o: %.cpp
	g++ -g -Wall -c -D SYMMETRICAL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

tsp: $(OBJS)
	g++  -o "tsp" $(OBJS) $(LIBS) 

all: tsp





clean:
	rm tsp *.o *.d
	rm -f *.tour

