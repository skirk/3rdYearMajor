CXX=g++
IDIR = ./include
CXXFLAGS=-g -Wall -I$(IDIR)

OBJECTS_DIR = obj

SOURCES= src/main.cpp \
	 src/Node.cpp \
	 src/NodeNetwork.cpp \
	 src/Slot.cpp \
	 src/Loader.cpp \
	 src/Database.cpp 

OBJECTS = obj/main.o \
	  obj/Node.o \
	  obj/NodeNetwork.o \
	  obj/DataBase.o \
	  obj/Loader.o \
	

DEPS = include/Node.h \
	include/NodeNetwork.h \
	include/Slot.h \
	include/DataBase.h \
	include/Loader.h \

TARGET = framework

$(OBJECTS_DIR)/%.o: src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm $(OBJECTS)
