CC=gcc
CFLAGS=-g -Wall
LFLAGS=-lm
OBJS1=hw0.o wrapper.o
OBJS2=hwdiff.o wrapper.o
OBJS3=showdata.o wrapper.o
TARGET1=hw0
TARGET2=hwdiff
TARGET3=showdata

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(OBJS1)
	$(CC) -o $@ $(OBJS1) $(LFLAGS)
$(TARGET2): $(OBJS2)
	$(CC) -o $@ $(OBJS2) $(LFLAGS)
$(TARGET3): $(OBJS3)
	$(CC) -o $@ $(OBJS3) $(LFLAGS)
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

hw0.o: wrapper.h
hwdiff.o: wrapper.h
showdata.o: wrapper.h
wrapper.o: wrapper.h

clean:
	rm $(TARGET1) $(OBJS1) $(OBJS2) $(OBJS3)

test: hw0
	bash test.sh $(ARG)
