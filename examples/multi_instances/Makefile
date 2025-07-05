FSM_NAME := multi_instances

all: fsm
	$(CC) main.c $(FSM_NAME)_fsm.c -o $(FSM_NAME)

fsm:
	$(F2C) $(FSM_NAME).fsm

clean:
	rm -f fsm.dot
	rm -f $(FSM_NAME)
	rm -f $(FSM_NAME)_fsm.*