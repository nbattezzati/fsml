all: fsm
	$(CC) main.c alarm_fsm.c -o alarm

fsm:
	$(F2C) alarm.fsm

clean:
	rm -f fsm.dot
	rm -f alarm
	rm -f alarm_fsm.*