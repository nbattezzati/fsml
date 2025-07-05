#include <stdio.h>
#include <assert.h>
#include "multi_instances_fsm.h"


int main(int argc, char *argv[])
{
    multi_instances_fsm_t inst_1 = multi_instances_fsm__create();
    multi_instances_fsm_t inst_2 = multi_instances_fsm__create();

    /* test: I can create two different instances of the FSM */
    printf("TEST: I can create two different instances of the FSM... ");
    assert(inst_1 != NULL);
    assert(inst_2 != NULL);
    assert(inst_1 != inst_2);
    printf("pass\n");

    /* test: The two instances are initialized with the same reset state */
    printf("TEST: The two instances are initialized with the same reset state... ");
    assert(multi_instances_fsm__state(inst_1) == multi_instances_fsm__state(inst_2));
    printf("pass\n");

    /* test: I move the state of one instance and the other remains in the reset state */
    printf("TEST: I move the state of one instance and the other remains in the reset state... ");
    multi_instances_fsm__set_cmd(inst_1, 1);
    multi_instances_fsm__exec(inst_1);
    multi_instances_fsm__exec(inst_2);
    assert(multi_instances_fsm__state(inst_1) != multi_instances_fsm__state(inst_2));
    printf("pass\n");

    /* TODO test: I move the state of the second instance and both of them are in the final state */

    /* TODO test: I destroy the instances and the pointers return to be NULL */

    /* TODO test: if malloc is provided from the extern that address is used */
}
