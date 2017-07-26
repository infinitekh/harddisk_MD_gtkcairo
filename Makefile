.SUFFIXES : .c .o 
CC=gcc
CFLAGS=-O2 -march=native -c
#all: harddisk
#OBJS= harddisk.o mymath.o
LIBS= -lm

#harddisk.out:  harddisk.c  harddisk.h mymath.c mymath.h 
#	$(CC) $(CFLAGS) harddisk.c  mymath.c -o harddisk.out $(LIBS)
##harddisk.o: harddisk.c  harddisk.h mymath.c mymath.h 
#mymath.o: mymath.c mymath.h 



INC=$(shell pkg-config --cflags-only-I  gtk+-3.0)
.c.o : 
	                $(CC) $(INC) $(CFLAGS) $<
LIBS+= $(shell pkg-config --libs  gtk+-3.0) -lm
all: noslip slip ellastic
noslip: main.o harddisk_noslip.o  mymath.o 
	$(CC) -o $@ main.o harddisk_noslip.o  mymath.o $(LIBS)  
slip: main.o harddisk_slip.o  mymath.o 
	$(CC) -o $@ main.o harddisk_slip.o  mymath.o $(LIBS)  
ellastic: main.o harddisk_ellastic.o  mymath.o 
	$(CC) -o $@ main.o harddisk_ellastic.o  mymath.o $(LIBS)  
main.o: main.c harddisk.c
harddisk_slip.o: harddisk.c  harddisk.h mymath.c mymath.h 
	$(CC) -c $(CFLAGS) $(INC) -DMAIN -DWC_TYPE=1 $< -o $@
harddisk_noslip.o: harddisk.c  harddisk.h mymath.c mymath.h 
	$(CC) -c $(CFLAGS) $(INC) -DMAIN -DWC_TYPE=2 $< -o $@
harddisk_ellastic.o: harddisk.c  harddisk.h mymath.c mymath.h 
	$(CC)  $(CFLAGS) $(INC) -DMAIN -DWC_TYPE=3  $< -o $@


clean:
	rm -f *.o
package: main.c harddisk.c harddisk.h mymath.h mymath.c 
	tar cvfz harddisk_MD_gtkcairo.tar.gz main.c harddisk.c harddisk.h mymath.h mymath.c 




dep :
	$(CC) -M  $(INC) harddisk.c main.c mymath.c >.depend
