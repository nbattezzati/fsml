#include <stdio.h>
#include <unistd.h>
#include "test3_fsm.h"
#include "maneuver_lib.h"

int main (void) 
{
    quaternion_t q = {1.0, 0.0, 0.0, 0.0};

    test3_fsm->reset();
    printf("reset fatto\n"); fflush(stdout);
    test3_fsm->set_maneuver_duration(10);
    printf("maneuver_duration settato\n"); fflush(stdout);
    test3_fsm->set_q(&q);
    printf("q settato\n"); fflush(stdout);

    while(1) {
        test3_state_t fsm_state;
        fsm_state = test3_fsm->exec();
        printf("TEST3 FSM state: %d --> man state: %d\n", fsm_state, test3_fsm->get_man_state()); fflush(stdout);
        sleep(1);
    }

    return 0;
}