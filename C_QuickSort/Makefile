# ***********************************************************************
#
#  Kelsey style makefile                   Ralph Kelsey  OU EECS
#  v 4.2        10 03 20                   kelsey@ohio.edu
#                                          follows Juedes and Chelberg
#
#  To compile:  enter 'make'
#  To clean up: enter 'make clean'
#
#  The project name occurs in two places. 
#  Adjust the name as needed, e.g., prog1 to prog4.
#
#
# ***********************************************************************


C = gcc 

# ************************************************************************
#
# Optimizing and Debugging with gdb
#
# use only one of the CFLAGS lines below. Leave other three commented out
#
# Considerations:
#
# 1. If code is optimized, the source code is changed somewhat.
#      This obscures debugging, so usually it is a good idea to debug
#      without optimization.
# 2. Higher optimization levels catch more suspect code, so usually it
#      is a good idea to have a high optimization level (O3) unless debugging.
# 3. Debugging info makes the executable file about 8 or 10 times bigger,
#      and probably slows down compilation.
#
# 4. Always use Wall (Warnings all) unless you have a bad warning. Consider
#      warnings to be errors unless there is a good reason not to.
#
# Use one of these:
#
# CFLAGS = -Wall
# CFLAGS = -Wall -O3
# CFLAGS = -Wall -g
# CFLAGS = -Wall -O3 -g
#
# **************************************************************************

CFLAGS = -Wall -g -O2 -m64
LIBS = -lm -lpthread
#CFLAGS = -O2

all: qSort qGenUnsorted

qSort: qSort.o
	$(C) $(CFLAGS) $(LIBS) -o qSort qSort.c

qGenUnsorted: qSortGenerate.o
	$(C) $(CFLAGS) $(LIBS) -o qGenUnsorted qSortGenerate.c

clean:
	rm -f core qGenUnsorted qSort *~ *.0

