all: fsm
	$(CC) main.c toy_decoder_fsm.c -o toy_decoder

fsm:
	$(F2C) toy_decoder.fsm

clean:
	rm -f fsm.dot
	rm -f toy_decoder
	rm -f toy_decoder_fsm.*