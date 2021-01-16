#include <stdio.h>
#include "toy_decoder_fsm.h"

int main(int argc, char *argv[])
{
    int i = 0;

    /* reset fsm to the starting state */
    toy_decoder_fsm->reset();

    /* execute FSM to search for the TOY pattern in the input string */
    while(argv[1] != NULL && argv[1][i] != '\0') {
        toy_decoder_fsm->set_input_char(argv[1][i]);
        toy_decoder_fsm->exec();
        if (toy_decoder_fsm->is_in_final_state()) {
            printf("TOY found\n");
            return 0;
        }
        i++;
    }

    printf("TOY not found\n");
    return 1;
}
