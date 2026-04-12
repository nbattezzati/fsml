#include <stdio.h>
#include <assert.h>
#include "toy_decoder_fsm.h"

int main(int argc, char *argv[])
{
    int i = 0;

    toy_decoder_fsm_t toy_decoder_fsm = toy_decoder_fsm__create();
    assert(toy_decoder_fsm != NULL);

    /* reset fsm to the starting state */
    toy_decoder_fsm__reset(toy_decoder_fsm);

    /* execute FSM to search for the TOY pattern in the input string */
    while(argv[1] != NULL && argv[1][i] != '\0') {
        toy_decoder_fsm__set_input_char(toy_decoder_fsm, argv[1][i]);
        toy_decoder_fsm__exec(toy_decoder_fsm);
        if (toy_decoder_fsm__is_in_final_state(toy_decoder_fsm)) {
            printf("TOY found\n");
            return 0;
        }
        i++;
    }

    printf("TOY not found\n");
    return 1;
}
