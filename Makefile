NAME=fbalsatray
CC=gcc
CFLAGS=-Wall
GTKLIBS=`pkg-config --cflags --libs gtk+-2.0 alsa`
SOURCE=volume.c $(NAME).c

all: fbalsatray

fbalsatray:
	$(CC) $(CFLAGS) $(GTKLIBS) $(SOURCE) -o $(NAME)

clean:
	rm $(NAME)
