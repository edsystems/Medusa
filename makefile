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
          Connection.cpp \
          ConnectionPool.cpp \
          JobManager.cpp \
          ListenConnection.cpp \
          Message.cpp \
          Network.cpp \
          NetworkNode.cpp \
          Options.cpp \
          Server.cpp \
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
