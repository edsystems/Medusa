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
          states/InitialState.cpp \
          states/ChooseLeaderState.cpp \
          states/LeaderState.cpp \
          states/WorkerState.cpp \
          tests/boosttest.cpp \
          tests/cpp11test.cpp
_SRCS   = $(notdir $(SOURCES))
_OBJS   = $(_SRCS:.cpp=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJ))
OUTNAME = medusa

#--------------------------------------------------------------------------------
# Compilation:
#--------------------------------------------------------------------------------

$(OUTNAME): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $^

$(ODIR)/%.o:
    $(CC) $(CFLAGS) $< -o $@

#--------------------------------------------------------------------------------
# Clean:
#--------------------------------------------------------------------------------

.PHONY: clean

clean:
    rm $(OUTNAME) $(OBJECTS)
