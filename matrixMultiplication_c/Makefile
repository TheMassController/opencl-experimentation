CC=gcc
SRCDIR=./
CFILES=$(wildcard $(SRCDIR)*.c)
_OFILES=$(patsubst %.c,%.o,$(CFILES))
INC= -I inc/
LIB=
LIBDIR= -L lib/
LDFLAGS= -lOpenCL
CFLAGS=-Wall -std=gnu11 $(INC)
ODIR=obj/
OFILES = $(patsubst $(SRCDIR)%,$(ODIR)%,$(_OFILES))
TARGET=final

.PHONY: all clean debug

all: CFLAGS += -O3 -march=native
all: LDFLAGS += -s
all: $(TARGET)

debug: CFLAGS +=-DDEBUG -Og -ggdb -march=native
debug: LDFLAGS +=-ggdb
debug: $(TARGET)

$(ODIR) :
	@mkdir -p $(ODIR)

$(ODIR)%.o: $(SRCDIR)%.c $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(ODIR)
	@rm $(TARGET)
