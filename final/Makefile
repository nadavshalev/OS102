# Makefile for the smash program
CC = g++
CFLAGS = -g -Wall -pthread
CCLINK = $(CC)
OBJS = bank.o atm.o account.o monitor.o Main.o
RM = rm -f
# Creating the  executable
Main: $(OBJS)
	$(CCLINK) -o Bank $(OBJS) $(CFLAGS)
# Creating the object files
Main.o: Main.cpp bank.cpp bank.h account.cpp account.h monitor.cpp monitor.h
bank.o: bank.cpp bank.h account.cpp account.h monitor.cpp monitor.h
atm.o: atm.cpp atm.h account.cpp account.h monitor.cpp monitor.h
account.o: account.cpp account.h monitor.cpp monitor.h
monitor.o: monitor.cpp monitor.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

