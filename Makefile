SRCS = \
	main.c

OBJS = $(subst .c,.o,$(SRCS))

CXXFLAGS = 
LIBS = -L. -lduckdb
TARGET = main
ifeq ($(OS),Windows_NT)
TARGET := $(TARGET).exe
endif

.SUFFIXES: .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -o $@ $(OBJS) $(LIBS)

.c.o :
	gcc -c $(CXXFLAGS) -I. $< -o $@
clean :
	rm -f *.o $(TARGET)
