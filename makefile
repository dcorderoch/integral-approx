# \
-l -l'library' Search the library named library when linking. put always at the end \
-Ldir Add directory dir to the list of directories to be searched for -l. \
-I dir Add the directory dir to the list of directories to be searched for header files

SDIR := src
SOURCES := math.cpp
SOURCE := $(patsubst %,$(SDIR)/%,$(SOURCES))
ODIR := obj
_OBJ := $(SOURCES:.cpp=.o)
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))
EXE := integrals

CXX := g++
CFLAGS := -O2 -W -Wall -g

all : $(EXE)

$(EXE) : $(OBJ)
	$(CXX) $(OBJ) -o $(EXE) $(CFLAGS)
$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)
.PHONY : clean
clean:
	rm -f $(OBJ) $(EXE)
