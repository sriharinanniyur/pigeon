CC = cc
OBJS = mail.o gui.o pigeon.o
CFLAGS = `pkg-config gtk+-3.0 --cflags --libs gtk+-3.0` -lcurl -o Pigeon
pigeon: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)
clean:
	rm $(OBJS)
