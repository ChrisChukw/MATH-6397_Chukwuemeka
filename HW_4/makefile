### Begin MACROS

CXX=g++
LD=g++

CXXFLAGS= -c -std=c++11 -Wall -Wextra
LDFLAGS=

# BLAS/LAPACK
LIBS= -llapack -lblas

# LIBS= -llapack -lopenblas

INCLUDE=.

SOURCES=main.cc my_matrix.cc
OBJECTS=$(SOURCES:.cc=.o)

EXEC=HW_4.exe

### End MACROS


### Begin targets

build: $(EXEC) $(SOURCES)

$(EXEC): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJECTS)

all: clean build

### End targets
