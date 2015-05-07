#--------------------------------------------------------------------------------
# Configuration:
#--------------------------------------------------------------------------------

CC      = g++
IDIR    = .
ODIR    = obj
FLAGS   = -I$(IDIR) -std=c++11
CFLAGS  = $(FLAGS) -c
LFLAGS  = $(FLAGS) -lpthread
SOURCES = main.cpp \
          boostimp.cpp \
          CoreManager.cpp \
          Options.cpp \
          Utility.cpp
_OBJS   = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJS))
OUTNAME = medusa

#--------------------------------------------------------------------------------
# Compilation:
#--------------------------------------------------------------------------------

all: $(OUTNAME)

initialize:
	mkdir -p $(ODIR)

$(ODIR)/%.o: %.cpp initialize
	$(CC) $(CFLAGS) -o $@ $<

$(OUTNAME): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $^

#--------------------------------------------------------------------------------
# Clean:
#--------------------------------------------------------------------------------

.PHONY: clean

clean:
	rm $(OUTNAME) $(OBJECTS)
