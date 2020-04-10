
CXX		= g++ -std=c++17 
INCLUDES	= 
CXXFLAGS  	= -g

LDFLAGS 	= -pthread -fopenmp
OPTFLAGS	= -O3 -finline-functions -fopt-info-vec-optimized -fopenmp-simd #-fno-tree-vectorize

OBJECTS = gol_main.o gol_omp.o gol_serial.o

TARGETS		= gol

.PHONY: all clean cleanall
.SUFFIXES: .cpp 

gol: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $< $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ -c $< $(LDFLAGS)

all		: $(TARGETS)

clean		: 
	rm -f $(TARGETS)

cleanall	: clean
	\rm -f *.o *~



