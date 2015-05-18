#--------------------------------------------------------------------------------
# Configuration:
#--------------------------------------------------------------------------------

CC      = g++
IDIR    = .
ODIR    = obj
FLAGS   = -I$(IDIR) -std=c++11
CFLAGS  = $(FLAGS) -c
LFLAGS  = $(FLAGS) -lpthread -ljpeg
SOURCES = main.cpp \
          boostimp.cpp \
          Connection.cpp \
          ConnectionPool.cpp \
          FragmentedFile.cpp \
          JobConnection.cpp \
          JobDescriptor.cpp \
          JobIdentifier.cpp \
          JobManager.cpp \
          ListenConnection.cpp \
          Message.cpp \
          Network.cpp \
          NetworkNode.cpp \
          Options.cpp \
          Server.cpp \
          TaskConnection.cpp \
          Texture.cpp \
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
