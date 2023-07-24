-include ../Makefile.rules
FILE=ansi.c mq_lib.c main.c						      \
  ex1/mq_example1.c ex1/pre_work_ex1.c ex1/sender_ex1.c ex1/receiver_ex1.c    \
  ex2/mq_example2.c ex2/pre_work_ex2.c ex2/sender_ex2.c ex2/receiver_ex2.c    \
 ex2/simulator_ex2.c ex2/notify_signal_ex2.c ex2/notify_thread_ex2.c
INCLUDE=-I./ -I./ex1/ -I./ex2/
SRC=$(FILE)
OBJS=${SRC:.c=.o}
TARGET=MQTest

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)
	mv $(TARGET) ..

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

${TARGET}: all

static: $(OBJS)
	ar cr $(TARGET).a $(OBJS)
	mv $(TARGET).a ..

dynamic: $(OBJS)
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
