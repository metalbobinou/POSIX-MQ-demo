-include ../Makefile.rules
FILE=ansi.c mq_lib.c mq_example.c main.c
SRC=$(FILE)
OBJS=${SRC:.c=.o}
TARGET=MQTest

all: ${OBJS}
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)
	mv $(TARGET) ..

objet:
	$(CC) $(CFLAGS) -c $(SRC)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

${TARGET}: all

static: objet
	ar cr $(TARGET).a $(OBJS)
	mv $(TARGET).a ..

dynamic: objet
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -shared -o $(TARGET).so
	mv $(TARGET).so ..

clean:
	rm -f $(OBJS)
	rm -rf *~
	rm -rf *#*

distclean: clean
	rm -f ../$(TARGET)
	rm -f ../$(TARGET).a
	rm -f ../$(TARGET).so
