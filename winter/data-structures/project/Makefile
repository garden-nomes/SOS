CXX=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=driver.cpp scheduler.cpp waitqueue.cpp runqueue.cpp job.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
