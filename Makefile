# Makefile
CXX_FLAG = --std=c++11 -g

all: testbst test_intbst

testbst: testbst.o intbst.o
	g++ $(CXX_FLAG) -o testbst testbst.o intbst.o

test_intbst: test_intbst.o intbst.o
	g++ $(CXX_FLAG) -o test_intbst test_intbst.o intbst.o

testbst.o: testbst.cpp intbst.h
	g++ -c $(CXX_FLAG) testbst.cpp

test_intbst.o: test_intbst.cpp intbst.h
	g++ -c $(CXX_FLAG) test_intbst.cpp

intbst.o: intbst.cpp intbst.h
	g++ -c $(CXX_FLAG) intbst.cpp

clean:
	rm -f testbst test_intbst *.o
