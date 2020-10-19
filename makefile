CC = gcc 
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps

all: main.o read_options.o process_list.o parse_files.o
	$(CC) -o $(EXE) main.o read_options.o process_list.o parse_files.o

main.o: main.c read_options.h
	$(CC) $(WARNING_FLAGS) -c main.c 

read_options.o: read_options.c read_options.h process_list.h
	$(CC) $(WARNING_FLAGS) -c read_options.c

process_list.o: process_list.c process_list.h parse_files.h
	$(CC) $(WARNING_FLAGS) -c process_list.c

parse_files.o: parse_files.c parse_files.h
	$(CC) $(WARNING_FLAGS) -c parse_files.c

clean:
	rm $(EXE) *.o
