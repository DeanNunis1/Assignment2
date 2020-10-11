#make file - this is a comment section
 
CC=g++	#compiler
TARGET=gameoflife	#target file name
 
all:
	$(CC) gameoflife.cpp -o $(TARGET)
 
clean:
	rm $(TARGET)
