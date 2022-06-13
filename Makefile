CC = g++
CFLAGS = -g -Wall -Werror -std=c++14 -pedantic
DEPS = RandWriter.h 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework
LFLAGS = cpplint --filter=-runtime/references,-build/header_guard --extensions=cpp,h
LDEPS = RandWriter.h RandWriter.cpp TextWriter.cpp

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
	
all: TextWriter

TextWriter: RandWriter.o TextWriter.o
	$(CC) $(CLFAGS) -o $@ $^ $(LIBS)

test: test.o RandWriter.o
	$(CC) $(CLFAGS) -o $@ $^ $(LIBS)

lint:
	$(LFLAGS) $(LDEPS)

clean:
	rm -f *.o TextWriter