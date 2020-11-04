CXX = c++
CXXFLAGS = -g -ggdb3 -Wall -Wextra -std=c++14

TESTSRC = main.cpp
TEST = main.o

BENCHSRC = benchmark/main_benchmark.cpp
BENCHMARK = main_benchmark.o

BST = binary_search_tree/BinarySearchTree.h
BCK = benchmark/Benchmark.h

all: main_test clean

main_test: $(TEST)
	$(CXX) $(TEST) $(CXXFLAGS) -o main_test

$(TEST): $(TESTSRC) $(BST)
	$(CXX) -c $(TESTSRC)

############### BENCHMARK SECTION ################
# it is for the creators of this BST not for all
#
#main_benck: $(BENCHMARK)
#	$(CXX) $(BENCHMARK) $(CXXFLAGS) -o main_benck
#
#$(BENCHMARK): $(BENCHSRC) $(BST) $(BCK)
#	$(CXX) -c $(BENCHSRC)
##################################################

clean:
	rm -f  *.o *~

clean_all:
	rm main_test

.PHONY: clean main_test
