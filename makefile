MAIN:= RayTracer
CPP:=g++
CPPVER:= -std=c++17

LDFLAGS = -lm
FLAGS:= #-O3

SRCS:=$(wildcard src/*.cpp)
HEADERS:=$(wildcard src/*.h)
OBJECTS:=$(patsubst src/%.cpp,bin/%.o,$(SRCS))


.PHONY: all run clean
all: bin/$(MAIN)

# $< are the names of all prerequisites (the object files)
# $@ is the name of the target (bin/myprogram in this case)
bin/$(MAIN): $(OBJECTS)
	$(CPP) $^ $(FLAGS) -o $@ $(LDFLAGS) $(CPPVER)

# but now we have to tell make how to build the object files
# -c option tells g++ to only compile one source file at a time
#  $< is the name of the first prerequisite (the cpp file in this case)
bin/%.o: src/%.cpp $(HEADERS)
	$(CPP) $< $(FLAGS) -c -o $@ $(LDFLAGS) $(CPPVER) 

clean:
	rm -f bin/$(OBJECTS) bin/$(MAIN)

run:
	./bin/$(MAIN)