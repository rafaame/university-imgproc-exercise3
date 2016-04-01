##### Variables

ifeq ($(OS),Windows_NT)

	SRCDIR = src
	OBJDIR = obj
	INCDIR = -Isrc -Iinclude
	LIBDIR =
	CPPFLAGS = -g -Wall $(INCDIR)
	LFLAGS =
	CC = g++ -mwin32

else

	SRCDIR = src
	OBJDIR = obj
	INCDIR = -Isrc -Iinclude
	LIBDIR =
	CPPFLAGS = -g -Wall $(INCDIR)
	LFLAGS =
	CC = g++

endif

##### Files

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SRCFILES = $(patsubst $(SRCDIR)/%,%,$(SOURCES))
DEPENDENCIES = $(patsubst %.cpp,%.o,$(SOURCES))
OBJTEMP = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES))
OBJECTS = $(patsubst %.cpp,%.o,$(OBJTEMP))
TARGET = bin/main

##### Build rules
all: depend $(DEPENDENCIES)
	$(CC) $(CPPFLAGS) $(LIBDIR) $(OBJECTS) $(LFLAGS) -o $(TARGET)

.cpp.o:
	$(CC) $(CPPFLAGS) -c -o $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$*).o $*.cpp

depend:
	makedepend -fMakefile $(INCDIR) $(SOURCES)

clean:
	@rm -rf $(TARGET) $(TARGET).exe $(OBJDIR)/*.o *.bak *~ *%

memtest:
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./$(TARGET)
# DO NOT DELETE

src/Image.o: include/Image.h include/common.h
src/Operation.o: include/Operation.h include/common.h include/Pixel.h
src/Operation.o: include/Image.h
src/Pixel.o: include/Pixel.h include/common.h
src/main.o: include/common.h include/Pixel.h include/Image.h
src/main.o: include/Operation.h
