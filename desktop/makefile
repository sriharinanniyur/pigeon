CC = cc
OBJS = mail.o analyze.o gui.o actionable.o
CFLAGS = `pkg-config gtk+-3.0 gtksourceview-3.0 --cflags --libs gtk+-3.0 gtksourceview-3.0` -lcurl
actionable: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o Actionable
clean:
	rm $(OBJS)
