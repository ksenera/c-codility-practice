CC = gcc 
CXX = g++ 
CFLAGS = -Wall -Wextra -g 
CXXFLAGS = -Wall -Wextra -g 

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $

%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $

clean:
	find . -name "*.out" -delete 