# Makefile for the smash program
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = bank.o account.o atm.o
RM = rm -f
# Creating the  executable
Main: $(OBJS)
	$(CCLINK) -o Bank $(OBJS)
# Creating the object files
bank.o: bank.cpp bank.h account.cpp account.h
atm.o: atm.cpp atm.h account.cpp account.h
account.o: account.cpp account.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

