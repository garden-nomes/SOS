CXX=g++
CFLAGS=-gdwarf-2 -O -c -Wall -std=c++0x
LDFLAGS=-gdwarf-2
SOURCES=driver.cpp scheduler.cpp waitqueue.cpp runqueue.cpp job.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
