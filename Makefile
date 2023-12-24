CC = g++
CFLAGS = -std=c++11 -Wall

SOURCES = src/Arithmetic.cpp src/Logical.cpp src/Load_and_Store.cpp src/Branching.cpp src/main.cpp src/Debugger.cpp src/Utils/Utils.cpp
HEADERS = src/Arithmetic.h src/Logical.h src/Load_and_Store.h src/Branching.h src/Debugger.h src/Essentials.h src/Utils/Utils.h

OBJECTS = $(addprefix build/, $(notdir $(SOURCES:.cpp=.o)))

EXECUTABLE = build/8085_cpp

$(shell mkdir build)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

build/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/Utils/%.cpp src/Utils/Utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist build\*.o del /Q build\*.o