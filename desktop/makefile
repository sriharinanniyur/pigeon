CC = cc
OBJS = mail.o gui.o pigeon.o
CFLAGS = `pkg-config gtk+-3.0 gtksourceview-3.0 --cflags --libs gtk+-3.0 gtksourceview-3.0` -lcurl

clarion: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o pigeon
clean:
	rm $(OBJS)
