#Comments adapted from C Module Problem Solving Chapter

CC = gcc #define gcc as compiler
CFLAGS = -g  #define compiler flags, -g is debug, -Wall turns on all warnings
default: cars #name of program

# cars is dependent on main.o car.o
# If main.o or car.o have a date newer than cars, invoke rule
cars: main.o car.o
	$(CC) $(CFLAGS) -o cars main.o car.o

#main.o is dependent on main.c and car.h
#if main.c or car.h have a newer date than main.o, invoke rule
main.o: main.c car.h
	$(CC) $(CFLAGS) -c main.c

#car.o is dependent on car.c and car.h
#if car.c or car.h have a newer date than car.o, invoke rule
car.o: car.c car.h
	$(CC) $(CFLAGS) -c car.c

#enter $ make clean to delete par and all .o files
clean:
	rm -f cars *.o
