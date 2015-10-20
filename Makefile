########################################################################
# COSC1076 - Advanced Programming Techniques
# Semester 2 2014 Assignment #2
# Full Name        : EDIT HERE
# Student Number   : EDIT HERE
# Course Code      : EDIT HERE
# Program Code     : EDIT HERE
# Start up code provided by Paul Miller
########################################################################

SOURCES=ppd_main.c ppd_menu.c ppd_options.c ppd_utility.c ppd_stock.c \
ppd_coin.c
HEADERS=ppd_main.h ppd_menu.h ppd_options.h ppd_utility.h ppd_stock.h \
ppd_coin.h
README=ppd_readme
MAKEFILE=Makefile
OBJ=ppd_main.o ppd_menu.o ppd_options.o ppd_utility.o ppd_stock.o \
ppd_coin.o
########################################################################
# Move this target to the end of the Makefile to zip up your code
# when submitting. Do not submit your .dat files, or directories.
# We only want the files that are part of your implementation.
########################################################################
archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(README) $(MAKEFILE)

all:
	gcc -ansi -pedantic -Wall -g -c $(SOURCES)
	gcc -ansi -pedantic -Wall -g -lm -o ppd $(OBJ)

clean:
	rm *.o *.exe
