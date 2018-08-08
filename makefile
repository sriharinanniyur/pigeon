CC = cc
OBJS = mail.o analyze.o gui.o pigeon.o
CFLAGS = `pkg-config gtk+-3.0 --cflags --libs gtk+-3.0` -lcurl
pigeon: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o Pigeon
clean:
	rm $(OBJS)
