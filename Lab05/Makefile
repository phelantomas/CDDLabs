EXE=producer_consumer
CC=g++
#Tomas Phelan 10/10/2017
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.

CC=g++
CFLAGS= -std=c++11 -pthread
HFILES=Semaphore.h SafeBuffer.h
CPPFILES=SafeBuffer.cpp Semaphore.cpp Prodcon.cpp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CPPFILES)
	$(CC) -o prod_con $(CFLAGS) $(CPPFILES) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

doc:ALL
	if [ -e "Doxyfile" ] ; then  rm 'Doxyfile';  fi
	if [ -d "docs" ] ; then  rm -rf 'docs';  fi
	mkdir docs
	echo "PROJECT_NAME = \"$L\"" >> Doxyfile
	echo "PROJECT_BRIEF = \"$B\"" >> Doxyfile
	echo "PROJECT_NUMBER = 0.8" >> Doxyfile
	echo "OUTPUT_DIRECTORY = ./docs"  >> Doxyfile
	echo "EXTRACT_ALL = YES" >> Doxyfile
	echo "RECURSIVE = YES" >> Doxyfile
	echo "SOURCE_BROWSER = YES" >> Doxyfile
	echo "GENERATE_LATEX = NO" >> Doxyfile
	echo "DOT_IMAGE_FORMAT = svg" >> Doxyfile
	echo "INPUT = ." >> Doxyfile
	doxygen Doxyfile

#this is customary and just deletes all .o files
CLEAN:
	rm *.o

