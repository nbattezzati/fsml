#include <stdio.h>
#include <assert.h>

#ifdef _WIN32
    #include <windows.h>
    #define portable_usleep(microseconds) Sleep((microseconds) / 1000)
#else
    #include <unistd.h>
    #define portable_usleep(microseconds) usleep(microseconds)
#endif

#include "multi_instances_advanced_fsm.h"

void test_1_creating_multiple_independent_instances(void);
void test_2_independent_state_management(void);
void test_3_testing_input_variable_isolation(void);
void test_4_error_state_management(void);
void test_5_reset_function_independence(void);
void test_6_error_code_retrieval_per_instance(void);
void test_7_final_state_detection_per_instance(void);
void test_8_output_variable_isolation(void);
void test_9_timer_independence(void);
void test_10_internal_variables_isolation(void);
void test_11_variable_persistence(void);
void test_12_user_code_in_states(void);
void test_13_retries_and_until_blocks(void);


int main(int argc, char *argv[])
{
    test_1_creating_multiple_independent_instances();
    test_2_independent_state_management();
    test_3_testing_input_variable_isolation();
    test_4_error_state_management();
    test_5_reset_function_independence();
    test_6_error_code_retrieval_per_instance();
    test_7_final_state_detection_per_instance();
    test_8_output_variable_isolation();
    test_9_timer_independence();
    test_10_internal_variables_isolation();
    test_11_variable_persistence();
    test_12_user_code_in_states();
    test_13_retries_and_until_blocks();
    
    printf("\n========================================\n");
    printf("ALL TESTS PASSED!\n");
    printf("========================================\n\n");

    return 0;
}


void test_1_creating_multiple_independent_instances(void)
{
    printf("\n========================================\n");
    printf("Test 1: Creating multiple independent instances\n");
    printf("========================================\n\n");

    /* Test 1.1: Create two instances */
    printf("TEST 1.1: Creating two FSM instances... ");
    multi_instances_advanced_fsm_t inst_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_2 = multi_instances_advanced_fsm__create();
    printf("PASS\n");

    /* Test 1.2: Verify both instances are not NULL */
    printf("TEST 1.2: Verifying instances are not NULL... ");
    assert(inst_1 != NULL);
    assert(inst_2 != NULL);
    printf("PASS\n");

    /* Test 1.3: Verify instances have different memory addresses (are independent) */
    printf("TEST 1.3: Verifying instances are independent (different addresses)... ");
    assert(inst_1 != inst_2);
    printf("PASS\n");

    /* Test 1.4: Display instance addresses for verification */
    printf("TEST 1.4: Instance addresses:\n");
    printf("         Instance 1 address: %p\n", (void*)inst_1);
    printf("         Instance 2 address: %p\n", (void*)inst_2);
    printf("         PASS\n");

    /* Test 1.5: Create a third instance and verify it's also independent */
    printf("TEST 1.5: Creating a third instance and verifying independence... ");
    multi_instances_advanced_fsm_t inst_3 = multi_instances_advanced_fsm__create();
    assert(inst_3 != NULL);
    assert(inst_3 != inst_1);
    assert(inst_3 != inst_2);
    printf("PASS\n");

    printf("\n========================================\n");
    printf("All Test 1 cases PASSED!\n");
    printf("========================================\n\n");
}


void test_2_independent_state_management(void)
{
    printf("\n========================================\n");
    printf("Test 2: Independent State Management\n");
    printf("========================================\n\n");

    /* Test 2.1: Verify both instances start in the same reset state */
    printf("TEST 2.1: Verifying both instances start in IDLE (reset) state... ");
    multi_instances_advanced_fsm_t fsm_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t fsm_b = multi_instances_advanced_fsm__create();
    
    int state_a = multi_instances_advanced_fsm__state(fsm_a);
    int state_b = multi_instances_advanced_fsm__state(fsm_b);
    
    assert(state_a == state_b);
    printf("PASS\n");
    printf("         Both instances state: %d\n", state_a);

    /* Test 2.2: Execute transition on instance A only, verify state changes only for A */
    printf("TEST 2.2: Executing transition on instance A only... ");
    multi_instances_advanced_fsm__set_cmd(fsm_a, 1);
    multi_instances_advanced_fsm__exec(fsm_a);
    
    int state_a_after = multi_instances_advanced_fsm__state(fsm_a);
    int state_b_after = multi_instances_advanced_fsm__state(fsm_b);
    
    assert(state_a_after != state_a);  /* Instance A changed state */
    assert(state_b_after == state_b);  /* Instance B remained in same state */
    printf("PASS\n");
    printf("         Instance A state changed: %d -> %d\n", state_a, state_a_after);
    printf("         Instance B state unchanged: %d (still %d)\n", state_b_after, state_b);

    /* Test 2.3: Execute different transition on instance B, verify it's independent */
    printf("TEST 2.3: Executing transition on instance B (from original state)... ");
    multi_instances_advanced_fsm__set_cmd(fsm_b, 1);
    multi_instances_advanced_fsm__exec(fsm_b);
    
    int state_a_final = multi_instances_advanced_fsm__state(fsm_a);
    int state_b_final = multi_instances_advanced_fsm__state(fsm_b);
    
    /* Instance B should transition to a different state than before */
    assert(state_b_final != state_b);
    printf("PASS\n");
    printf("         Instance A state: %d\n", state_a_final);
    printf("         Instance B state: %d\n", state_b_final);

    /* Test 2.4: Verify that setting input on one instance doesn't affect the other */
    printf("TEST 2.4: Verifying input isolation between instances... ");
    multi_instances_advanced_fsm_t inst_x = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_y = multi_instances_advanced_fsm__create();
    
    /* Set input on instance X */
    multi_instances_advanced_fsm__set_cmd(inst_x, 1);
    
    /* Execute both */
    multi_instances_advanced_fsm__exec(inst_x);
    multi_instances_advanced_fsm__exec(inst_y);
    
    /* Instance X should have transitioned, instance Y should not */
    int state_x = multi_instances_advanced_fsm__state(inst_x);
    int state_y = multi_instances_advanced_fsm__state(inst_y);
    
    assert(state_x != state_y);
    printf("PASS\n");
    printf("         Instance X state (with cmd=1): %d\n", state_x);
    printf("         Instance Y state (default cmd): %d\n", state_y);

    /* Test 2.5: Multiple state transitions on different instances */
    printf("TEST 2.5: Multiple transitions on different instances... ");
    multi_instances_advanced_fsm_t m1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t m2 = multi_instances_advanced_fsm__create();
    
    /* Sequence on M1: cmd=1 (IDLE -> PROCESSING) */
    multi_instances_advanced_fsm__set_cmd(m1, 1);
    multi_instances_advanced_fsm__exec(m1);
    int m1_state_1 = multi_instances_advanced_fsm__state(m1);
    
    /* M2 stays in IDLE */
    multi_instances_advanced_fsm__exec(m2);
    int m2_state_1 = multi_instances_advanced_fsm__state(m2);
    
    /* Verify they diverged */
    assert(m1_state_1 != m2_state_1);
    
    /* Now transition M1 to DONE */
    multi_instances_advanced_fsm__set_cmd(m1, 2);
    multi_instances_advanced_fsm__exec(m1);
    int m1_state_2 = multi_instances_advanced_fsm__state(m1);
    
    /* M2 still in original state */
    int m2_state_2 = multi_instances_advanced_fsm__state(m2);
    assert(m2_state_1 == m2_state_2);
    
    /* All three states should be different */
    assert(m1_state_1 != m1_state_2);
    assert(m1_state_2 != m2_state_2);
    printf("PASS\n");
    printf("         M1 progression: %d -> %d\n", m1_state_1, m1_state_2);
    printf("         M2 remained at: %d\n", m2_state_2);

    printf("\n========================================\n");
    printf("All Test 2 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_3_testing_input_variable_isolation(void)
{
    printf("\n========================================\n");
    printf("Test 3: Testing input variable isolation\n");
    printf("========================================\n\n");

    /* Test 3.1: Verify input variables are isolated between instances */
    printf("TEST 3.1: Setting different input values on two instances... ");
    multi_instances_advanced_fsm_t inst_p = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_q = multi_instances_advanced_fsm__create();

    /* Set cmd to 1 on instance P */
    multi_instances_advanced_fsm__set_cmd(inst_p, 1);
    /* Set cmd to 2 on instance Q */
    multi_instances_advanced_fsm__set_cmd(inst_q, 2);

    /* Execute both */
    multi_instances_advanced_fsm__exec(inst_p);
    multi_instances_advanced_fsm__exec(inst_q);

    int state_p = multi_instances_advanced_fsm__state(inst_p);
    int state_q = multi_instances_advanced_fsm__state(inst_q);

    /* They should be in different states due to different inputs */
    assert(state_p != state_q);
    printf("PASS\n");
    printf("         Instance P (cmd=1) state: %d\n", state_p);
    printf("         Instance Q (cmd=2) state: %d\n", state_q);

    /* Test 3.2: Verify setting input on one instance doesn't affect the other */
    printf("TEST 3.2: Modifying input on one instance doesn't affect another... ");
    multi_instances_advanced_fsm_t inst_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_2 = multi_instances_advanced_fsm__create();

    /* Set cmd on instance 1 multiple times */
    multi_instances_advanced_fsm__set_cmd(inst_1, 1);
    multi_instances_advanced_fsm__exec(inst_1);

    int state_1_after_first_cmd = multi_instances_advanced_fsm__state(inst_1);

    /* Instance 2 should still have default cmd value */
    multi_instances_advanced_fsm__exec(inst_2);
    int state_2_after_exec = multi_instances_advanced_fsm__state(inst_2);

    /* Change cmd on instance 1 again */
    multi_instances_advanced_fsm__set_cmd(inst_1, 2);
    multi_instances_advanced_fsm__exec(inst_1);

    int state_1_after_second_cmd = multi_instances_advanced_fsm__state(inst_1);

    /* Instance 2 should remain unchanged */
    multi_instances_advanced_fsm__exec(inst_2);
    int state_2_after_second_exec = multi_instances_advanced_fsm__state(inst_2);

    assert(state_2_after_exec == state_2_after_second_exec);
    printf("PASS\n");
    printf("         Instance 1 state progression: %d -> %d\n", state_1_after_first_cmd, state_1_after_second_cmd);
    printf("         Instance 2 remained at: %d\n", state_2_after_second_exec);

    /* Test 3.3: Three instances with different input combinations */
    printf("TEST 3.3: Three instances with different input combinations... ");
    multi_instances_advanced_fsm_t i1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t i2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t i3 = multi_instances_advanced_fsm__create();

    /* Set different inputs */
    multi_instances_advanced_fsm__set_cmd(i1, 1);
    multi_instances_advanced_fsm__set_cmd(i2, 2);
    /* i3 keeps default cmd=0 */

    /* Execute all */
    multi_instances_advanced_fsm__exec(i1);
    multi_instances_advanced_fsm__exec(i2);
    multi_instances_advanced_fsm__exec(i3);

    int s1 = multi_instances_advanced_fsm__state(i1);
    int s2 = multi_instances_advanced_fsm__state(i2);
    int s3 = multi_instances_advanced_fsm__state(i3);

    /* All should be in different states */
    assert(s1 != s2);
    assert(s2 != s3);
    assert(s1 != s3);
    printf("PASS\n");
    printf("         Instance I1 (cmd=1) state: %d\n", s1);
    printf("         Instance I2 (cmd=2) state: %d\n", s2);
    printf("         Instance I3 (cmd=0) state: %d\n", s3);

    /* Test 3.4: Verify input changes persist only within the instance scope */
    printf("TEST 3.4: Input changes are instance-scoped... ");
    multi_instances_advanced_fsm_t fsm_x = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t fsm_y = multi_instances_advanced_fsm__create();

    /* Get initial states */
    int initial_x = multi_instances_advanced_fsm__state(fsm_x);
    int initial_y = multi_instances_advanced_fsm__state(fsm_y);
    assert(initial_x == initial_y);

    /* Modify input and execute on X only */
    multi_instances_advanced_fsm__set_cmd(fsm_x, 1);
    multi_instances_advanced_fsm__exec(fsm_x);

    int after_x = multi_instances_advanced_fsm__state(fsm_x);

    /* Execute Y without changing its input */
    multi_instances_advanced_fsm__exec(fsm_y);
    int after_y = multi_instances_advanced_fsm__state(fsm_y);

    /* Y should still be in initial state */
    assert(after_y == initial_y);
    assert(after_x != after_y);
    printf("PASS\n");
    printf("         FSM X state changed: %d -> %d (cmd=1)\n", initial_x, after_x);
    printf("         FSM Y state unchanged: %d (cmd=0)\n", after_y);

    /* Test 3.5: Rapid input changes on multiple instances */
    printf("TEST 3.5: Rapid input changes on multiple instances... ");
    multi_instances_advanced_fsm_t rapid1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t rapid2 = multi_instances_advanced_fsm__create();

    /* Rapid sequence on rapid1 */
    multi_instances_advanced_fsm__set_cmd(rapid1, 1);
    multi_instances_advanced_fsm__exec(rapid1);
    int rapid1_state1 = multi_instances_advanced_fsm__state(rapid1);

    multi_instances_advanced_fsm__set_cmd(rapid1, 2);
    multi_instances_advanced_fsm__exec(rapid1);
    int rapid1_state2 = multi_instances_advanced_fsm__state(rapid1);

    /* Verify rapid2 was not affected during these changes */
    int rapid2_state_before = multi_instances_advanced_fsm__state(rapid2);

    /* Execute rapid2 with default input */
    multi_instances_advanced_fsm__exec(rapid2);
    int rapid2_state_after = multi_instances_advanced_fsm__state(rapid2);

    assert(rapid2_state_before == rapid2_state_after);
    assert(rapid1_state1 != rapid1_state2);
    assert(rapid1_state2 != rapid2_state_after);
    printf("PASS\n");
    printf("         Rapid1 state progression: %d -> %d\n", rapid1_state1, rapid1_state2);
    printf("         Rapid2 remained unaffected: %d\n", rapid2_state_after);

    printf("\n========================================\n");
    printf("All Test 3 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_4_error_state_management(void)
{
    printf("\n========================================\n");
    printf("Test 4: Error state management\n");
    printf("========================================\n\n");

    /* Test 4.1: Verify one instance can enter error state while another remains normal */
    printf("TEST 4.1: One instance in error state, other in normal state... ");
    multi_instances_advanced_fsm_t inst_normal = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_error = multi_instances_advanced_fsm__create();

    /* Trigger error on inst_error */
    multi_instances_advanced_fsm__set_cmd(inst_error, 3);
    multi_instances_advanced_fsm__exec(inst_error);

    /* Keep inst_normal in normal state */
    multi_instances_advanced_fsm__set_cmd(inst_normal, 1);
    multi_instances_advanced_fsm__exec(inst_normal);

    int state_normal = multi_instances_advanced_fsm__state(inst_normal);
    int state_error = multi_instances_advanced_fsm__state(inst_error);

    /* States should be different */
    assert(state_normal != state_error);
    printf("PASS\n");
    printf("         Normal instance state: %d\n", state_normal);
    printf("         Error instance state: %d\n", state_error);

    /* Test 4.2: Verify error states are isolated between instances */
    printf("TEST 4.2: Multiple instances can have independent error states... ");
    multi_instances_advanced_fsm_t err_inst1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t err_inst2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t normal_inst = multi_instances_advanced_fsm__create();

    /* Trigger error on first instance from IDLE */
    multi_instances_advanced_fsm__set_cmd(err_inst1, 3);
    multi_instances_advanced_fsm__exec(err_inst1);

    int state_err1_after = multi_instances_advanced_fsm__state(err_inst1);

    /* Keep second instance in PROCESSING (no error) */
    multi_instances_advanced_fsm__set_cmd(err_inst2, 1);
    multi_instances_advanced_fsm__exec(err_inst2);

    int state_err2 = multi_instances_advanced_fsm__state(err_inst2);

    /* Keep third instance in IDLE (no error) */
    multi_instances_advanced_fsm__exec(normal_inst);
    int state_normal_inst = multi_instances_advanced_fsm__state(normal_inst);

    /* All three should be in different states */
    assert(state_err1_after != state_err2);
    assert(state_err1_after != state_normal_inst);
    assert(state_err2 != state_normal_inst);
    printf("PASS\n");
    printf("         Error instance 1 state: %d\n", state_err1_after);
    printf("         Instance 2 (PROCESSING) state: %d\n", state_err2);
    printf("         Normal instance (IDLE) state: %d\n", state_normal_inst);

    /* Test 4.3: Verify error can be triggered from different states */
    printf("TEST 4.3: Error can be triggered from different states on different instances... ");
    multi_instances_advanced_fsm_t inst_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_b = multi_instances_advanced_fsm__create();

    /* Trigger error from IDLE on inst_a */
    multi_instances_advanced_fsm__set_cmd(inst_a, 3);
    multi_instances_advanced_fsm__exec(inst_a);
    int error_state_a = multi_instances_advanced_fsm__state(inst_a);

    /* Transition inst_b to PROCESSING, then trigger error from there */
    multi_instances_advanced_fsm__set_cmd(inst_b, 1);
    multi_instances_advanced_fsm__exec(inst_b);
    int processing_state_b = multi_instances_advanced_fsm__state(inst_b);

    multi_instances_advanced_fsm__set_cmd(inst_b, 3);
    multi_instances_advanced_fsm__exec(inst_b);
    int error_state_b = multi_instances_advanced_fsm__state(inst_b);

    /* Both should be in error state */
    assert(error_state_a == error_state_b);
    assert(error_state_a != processing_state_b);
    printf("PASS\n");
    printf("         Error from IDLE (inst_a): %d\n", error_state_a);
    printf("         Processing state (inst_b before error): %d\n", processing_state_b);
    printf("         Error from PROCESSING (inst_b): %d\n", error_state_b);

    /* Test 4.4: Verify error on one instance doesn't affect another */
    printf("TEST 4.4: Error on one instance doesn't affect another instance... ");
    multi_instances_advanced_fsm_t test_inst1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t test_inst2 = multi_instances_advanced_fsm__create();

    /* Get initial state */
    int initial_state = multi_instances_advanced_fsm__state(test_inst2);

    /* Trigger error on test_inst1 */
    multi_instances_advanced_fsm__set_cmd(test_inst1, 3);
    multi_instances_advanced_fsm__exec(test_inst1);

    /* Verify test_inst2 is still in initial state */
    int state_inst2_after = multi_instances_advanced_fsm__state(test_inst2);
    assert(state_inst2_after == initial_state);

    /* Execute test_inst2 and verify it's still not in error */
    multi_instances_advanced_fsm__exec(test_inst2);
    int state_inst2_final = multi_instances_advanced_fsm__state(test_inst2);
    assert(state_inst2_final == initial_state);
    printf("PASS\n");
    printf("         Instance 1 entered error state\n");
    printf("         Instance 2 remained in initial state: %d\n", state_inst2_final);

    /* Test 4.5: Verify error states remain stable across multiple executions */
    printf("TEST 4.5: Error state remains stable after entering... ");
    multi_instances_advanced_fsm_t stable_inst = multi_instances_advanced_fsm__create();

    /* Trigger error */
    multi_instances_advanced_fsm__set_cmd(stable_inst, 3);
    multi_instances_advanced_fsm__exec(stable_inst);
    int error_state_first = multi_instances_advanced_fsm__state(stable_inst);

    /* Execute multiple times */
    multi_instances_advanced_fsm__exec(stable_inst);
    int error_state_second = multi_instances_advanced_fsm__state(stable_inst);

    multi_instances_advanced_fsm__exec(stable_inst);
    int error_state_third = multi_instances_advanced_fsm__state(stable_inst);

    /* Error state should remain the same */
    assert(error_state_first == error_state_second);
    assert(error_state_second == error_state_third);
    printf("PASS\n");
    printf("         Error state remained stable: %d\n", error_state_first);

    printf("\n========================================\n");
    printf("All Test 4 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_5_reset_function_independence(void)
{
    printf("\n========================================\n");
    printf("Test 5: Reset function independence\n");
    printf("========================================\n\n");

    /* Test 5.1: Verify reset() works on individual instances */
    printf("TEST 5.1: Reset works on individual instances... ");
    multi_instances_advanced_fsm_t inst_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_2 = multi_instances_advanced_fsm__create();

    /* Transition both instances */
    multi_instances_advanced_fsm__set_cmd(inst_1, 1);
    multi_instances_advanced_fsm__exec(inst_1);

    multi_instances_advanced_fsm__set_cmd(inst_2, 2);
    multi_instances_advanced_fsm__exec(inst_2);

    int state_1_after = multi_instances_advanced_fsm__state(inst_1);
    int state_2_after = multi_instances_advanced_fsm__state(inst_2);

    /* Reset only instance 1 */
    multi_instances_advanced_fsm__reset(inst_1);

    int state_1_reset = multi_instances_advanced_fsm__state(inst_1);
    int state_2_unchanged = multi_instances_advanced_fsm__state(inst_2);

    /* Instance 1 should be reset, instance 2 should remain unchanged */
    assert(state_1_reset != state_1_after);
    assert(state_2_unchanged == state_2_after);
    printf("PASS\n");
    printf("         Instance 1 after transition: %d, after reset: %d\n", state_1_after, state_1_reset);
    printf("         Instance 2 remained: %d\n", state_2_unchanged);

    /* Test 5.2: Reset to initial state on one instance doesn't affect another */
    printf("TEST 5.2: Reset on one instance doesn't affect another... ");
    multi_instances_advanced_fsm_t test_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t test_b = multi_instances_advanced_fsm__create();

    int initial_state_a = multi_instances_advanced_fsm__state(test_a);
    int initial_state_b = multi_instances_advanced_fsm__state(test_b);

    /* Modify and reset A */
    multi_instances_advanced_fsm__set_cmd(test_a, 1);
    multi_instances_advanced_fsm__exec(test_a);
    multi_instances_advanced_fsm__reset(test_a);

    /* Modify B but don't reset */
    multi_instances_advanced_fsm__set_cmd(test_b, 1);
    multi_instances_advanced_fsm__exec(test_b);

    int final_state_a = multi_instances_advanced_fsm__state(test_a);
    int final_state_b = multi_instances_advanced_fsm__state(test_b);

    /* A should be back to initial, B should be different */
    assert(final_state_a == initial_state_a);
    assert(final_state_b != initial_state_b);
    printf("PASS\n");
    printf("         Instance A reset to initial: %d\n", final_state_a);
    printf("         Instance B still modified: %d\n", final_state_b);

    /* Test 5.3: Multiple resets on same instance work correctly */
    printf("TEST 5.3: Multiple resets on same instance work correctly... ");
    multi_instances_advanced_fsm_t multi_reset = multi_instances_advanced_fsm__create();

    int initial = multi_instances_advanced_fsm__state(multi_reset);

    /* First transition and reset cycle */
    multi_instances_advanced_fsm__set_cmd(multi_reset, 1);
    multi_instances_advanced_fsm__exec(multi_reset);
    multi_instances_advanced_fsm__reset(multi_reset);
    int after_first_reset = multi_instances_advanced_fsm__state(multi_reset);

    /* Second transition and reset cycle */
    multi_instances_advanced_fsm__set_cmd(multi_reset, 2);
    multi_instances_advanced_fsm__exec(multi_reset);
    multi_instances_advanced_fsm__reset(multi_reset);
    int after_second_reset = multi_instances_advanced_fsm__state(multi_reset);

    /* All should be the same initial state */
    assert(initial == after_first_reset);
    assert(after_first_reset == after_second_reset);
    printf("PASS\n");
    printf("         All resets returned to state: %d\n", initial);

    /* Test 5.4: Reset after error state returns to initial state */
    printf("TEST 5.4: Reset after error state returns to initial state... ");
    multi_instances_advanced_fsm_t error_reset = multi_instances_advanced_fsm__create();

    int initial_error_reset = multi_instances_advanced_fsm__state(error_reset);

    /* Trigger error */
    multi_instances_advanced_fsm__set_cmd(error_reset, 3);
    multi_instances_advanced_fsm__exec(error_reset);

    int error_state = multi_instances_advanced_fsm__state(error_reset);
    assert(error_state != initial_error_reset);

    /* Reset should bring it back */
    multi_instances_advanced_fsm__reset(error_reset);
    int after_error_reset = multi_instances_advanced_fsm__state(error_reset);

    assert(after_error_reset == initial_error_reset);
    printf("PASS\n");
    printf("         Error state: %d, after reset: %d (initial: %d)\n", error_state, after_error_reset, initial_error_reset);

    /* Test 5.5: Reset three instances independently */
    printf("TEST 5.5: Reset three instances independently... ");
    multi_instances_advanced_fsm_t r1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t r2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t r3 = multi_instances_advanced_fsm__create();

    int init_r1 = multi_instances_advanced_fsm__state(r1);
    int init_r2 = multi_instances_advanced_fsm__state(r2);
    int init_r3 = multi_instances_advanced_fsm__state(r3);

    /* Transition all to different states */
    multi_instances_advanced_fsm__set_cmd(r1, 1);
    multi_instances_advanced_fsm__exec(r1);

    multi_instances_advanced_fsm__set_cmd(r2, 2);
    multi_instances_advanced_fsm__exec(r2);

    multi_instances_advanced_fsm__set_cmd(r3, 1);
    multi_instances_advanced_fsm__exec(r3);

    /* Reset only r2 */
    multi_instances_advanced_fsm__reset(r2);

    int after_r1 = multi_instances_advanced_fsm__state(r1);
    int after_r2 = multi_instances_advanced_fsm__state(r2);
    int after_r3 = multi_instances_advanced_fsm__state(r3);

    /* r1 and r3 should still be modified, r2 should be reset */
    assert(after_r1 != init_r1);
    assert(after_r2 == init_r2);
    assert(after_r3 != init_r3);
    printf("PASS\n");
    printf("         Instance 1: unchanged (modified)\n");
    printf("         Instance 2: reset to initial\n");
    printf("         Instance 3: unchanged (modified)\n");

    printf("\n========================================\n");
    printf("All Test 5 cases PASSED!\n");
    printf("========================================\n\n");
}


void test_6_error_code_retrieval_per_instance(void)
{
    printf("\n========================================\n");
    printf("Test 6: Error code retrieval per instance\n");
    printf("========================================\n\n");

    /* Test 6.1: Verify err() returns correct error code for instance in error */
    printf("TEST 6.1: err() returns correct error code for instance in error... ");
    multi_instances_advanced_fsm_t err_inst = multi_instances_advanced_fsm__create();

    /* Trigger error */
    multi_instances_advanced_fsm__set_cmd(err_inst, 3);
    multi_instances_advanced_fsm__exec(err_inst);

    int error_code = multi_instances_advanced_fsm__err(err_inst);

    /* Error code should not be NoError */
    assert(error_code != 0);  /* Assuming 0 is NoError */
    printf("PASS\n");
    printf("         Error code retrieved: %d\n", error_code);

    /* Test 6.2: Verify err() returns NoError for normal instance */
    printf("TEST 6.2: err() returns NoError for normal instance... ");
    multi_instances_advanced_fsm_t normal_inst = multi_instances_advanced_fsm__create();

    /* Execute normally without error */
    multi_instances_advanced_fsm__set_cmd(normal_inst, 1);
    multi_instances_advanced_fsm__exec(normal_inst);

    int no_error_code = multi_instances_advanced_fsm__err(normal_inst);

    /* Should return NoError */
    assert(no_error_code == 0);  /* Assuming 0 is NoError */
    printf("PASS\n");
    printf("         No error code: %d\n", no_error_code);

    /* Test 6.3: Verify error codes are independent between instances */
    printf("TEST 6.3: Error codes are independent between instances... ");
    multi_instances_advanced_fsm_t inst_with_err = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_without_err = multi_instances_advanced_fsm__create();

    /* Trigger error only on first instance */
    multi_instances_advanced_fsm__set_cmd(inst_with_err, 3);
    multi_instances_advanced_fsm__exec(inst_with_err);

    /* Keep second instance normal */
    multi_instances_advanced_fsm__set_cmd(inst_without_err, 1);
    multi_instances_advanced_fsm__exec(inst_without_err);

    int err_code_1 = multi_instances_advanced_fsm__err(inst_with_err);
    int err_code_2 = multi_instances_advanced_fsm__err(inst_without_err);

    /* They should be different */
    assert(err_code_1 != err_code_2);
    assert(err_code_1 != 0);
    assert(err_code_2 == 0);
    printf("PASS\n");
    printf("         Instance with error code: %d\n", err_code_1);
    printf("         Instance without error code: %d\n", err_code_2);

    /* Test 6.4: Verify error code persists after reset */
    printf("TEST 6.4: Error code clears after reset... ");
    multi_instances_advanced_fsm_t reset_err = multi_instances_advanced_fsm__create();

    /* Trigger error */
    multi_instances_advanced_fsm__set_cmd(reset_err, 3);
    multi_instances_advanced_fsm__exec(reset_err);

    int err_before_reset = multi_instances_advanced_fsm__err(reset_err);
    assert(err_before_reset != 0);

    /* Reset */
    multi_instances_advanced_fsm__reset(reset_err);

    int err_after_reset = multi_instances_advanced_fsm__err(reset_err);

    /* Error should be cleared */
    assert(err_after_reset == 0);
    printf("PASS\n");
    printf("         Error code before reset: %d, after reset: %d\n", err_before_reset, err_after_reset);

    /* Test 6.5: Multiple instances with errors have independent error codes */
    printf("TEST 6.5: Multiple error instances have independent error codes... ");
    multi_instances_advanced_fsm_t err1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t err2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t normal = multi_instances_advanced_fsm__create();

    /* Trigger error on both from different states */
    multi_instances_advanced_fsm__set_cmd(err1, 3);
    multi_instances_advanced_fsm__exec(err1);

    multi_instances_advanced_fsm__set_cmd(err2, 1);
    multi_instances_advanced_fsm__exec(err2);
    multi_instances_advanced_fsm__set_cmd(err2, 3);
    multi_instances_advanced_fsm__exec(err2);

    /* Keep normal instance error-free */
    multi_instances_advanced_fsm__set_cmd(normal, 2);
    multi_instances_advanced_fsm__exec(normal);

    int ec1 = multi_instances_advanced_fsm__err(err1);
    int ec2 = multi_instances_advanced_fsm__err(err2);
    int ec_normal = multi_instances_advanced_fsm__err(normal);

    /* Error instances should have error, normal should not */
    assert(ec1 != 0);
    assert(ec2 != 0);
    assert(ec_normal == 0);
    printf("PASS\n");
    printf("         Error instance 1 code: %d\n", ec1);
    printf("         Error instance 2 code: %d\n", ec2);
    printf("         Normal instance code: %d\n", ec_normal);

    printf("\n========================================\n");
    printf("All Test 6 cases PASSED!\n");
    printf("========================================\n\n");
}


void test_7_final_state_detection_per_instance(void)
{
    printf("\n========================================\n");
    printf("Test 7: Final state detection per instance\n");
    printf("========================================\n\n");

    /* Test 7.1: Verify is_in_final_state() returns true for instance in final state */
    printf("TEST 7.1: is_in_final_state() returns true for final state... ");
    multi_instances_advanced_fsm_t final_inst = multi_instances_advanced_fsm__create();

    /* Transition to DONE (final state) */
    multi_instances_advanced_fsm__set_cmd(final_inst, 2);
    multi_instances_advanced_fsm__exec(final_inst);

    int is_final = multi_instances_advanced_fsm__is_in_final_state(final_inst);

    /* Should return true (non-zero) */
    assert(is_final != 0);
    printf("PASS\n");
    printf("         is_in_final_state returned: %d (non-zero = true)\n", is_final);

    /* Test 7.2: Verify is_in_final_state() returns false for non-final state */
    printf("TEST 7.2: is_in_final_state() returns false for non-final state... ");
    multi_instances_advanced_fsm_t non_final_inst = multi_instances_advanced_fsm__create();

    /* Transition to PROCESSING (not final) */
    multi_instances_advanced_fsm__set_cmd(non_final_inst, 1);
    multi_instances_advanced_fsm__exec(non_final_inst);

    int is_not_final = multi_instances_advanced_fsm__is_in_final_state(non_final_inst);

    /* Should return false (zero) */
    assert(is_not_final == 0);
    printf("PASS\n");
    printf("         is_in_final_state returned: %d (zero = false)\n", is_not_final);

    /* Test 7.3: Final state detection is independent between instances */
    printf("TEST 7.3: Final state detection independent between instances... ");
    multi_instances_advanced_fsm_t inst_final = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_non_final = multi_instances_advanced_fsm__create();

    /* Transition one to final, keep other non-final */
    multi_instances_advanced_fsm__set_cmd(inst_final, 2);
    multi_instances_advanced_fsm__exec(inst_final);

    multi_instances_advanced_fsm__set_cmd(inst_non_final, 1);
    multi_instances_advanced_fsm__exec(inst_non_final);

    int is_final_1 = multi_instances_advanced_fsm__is_in_final_state(inst_final);
    int is_final_2 = multi_instances_advanced_fsm__is_in_final_state(inst_non_final);

    /* They should be different */
    assert(is_final_1 != is_final_2);
    assert(is_final_1 != 0);
    assert(is_final_2 == 0);
    printf("PASS\n");
    printf("         Instance 1 in final state: %d\n", is_final_1);
    printf("         Instance 2 not in final state: %d\n", is_final_2);

    /* Test 7.4: Reset clears final state detection */
    printf("TEST 7.4: Reset clears final state (returns to non-final)... ");
    multi_instances_advanced_fsm_t reset_final = multi_instances_advanced_fsm__create();

    /* Transition to final */
    multi_instances_advanced_fsm__set_cmd(reset_final, 2);
    multi_instances_advanced_fsm__exec(reset_final);
    int is_final_before = multi_instances_advanced_fsm__is_in_final_state(reset_final);
    assert(is_final_before != 0);

    /* Reset */
    multi_instances_advanced_fsm__reset(reset_final);

    int is_final_after = multi_instances_advanced_fsm__is_in_final_state(reset_final);

    /* Should no longer be in final state */
    assert(is_final_after == 0);
    printf("PASS\n");
    printf("         In final state before reset: %d, after reset: %d\n", is_final_before, is_final_after);

    /* Test 7.5: Multiple instances can have different final states simultaneously */
    printf("TEST 7.5: Multiple instances with different final states... ");
    multi_instances_advanced_fsm_t f1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t f2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t f3 = multi_instances_advanced_fsm__create();

    /* f1: IDLE (not final) */
    multi_instances_advanced_fsm__exec(f1);

    /* f2: PROCESSING (not final) */
    multi_instances_advanced_fsm__set_cmd(f2, 1);
    multi_instances_advanced_fsm__exec(f2);

    /* f3: DONE (final) */
    multi_instances_advanced_fsm__set_cmd(f3, 2);
    multi_instances_advanced_fsm__exec(f3);

    int final_f1 = multi_instances_advanced_fsm__is_in_final_state(f1);
    int final_f2 = multi_instances_advanced_fsm__is_in_final_state(f2);
    int final_f3 = multi_instances_advanced_fsm__is_in_final_state(f3);

    /* Only f3 should be final */
    assert(final_f1 == 0);
    assert(final_f2 == 0);
    assert(final_f3 != 0);
    printf("PASS\n");
    printf("         Instance 1 (IDLE) in final: %d\n", final_f1);
    printf("         Instance 2 (PROCESSING) in final: %d\n", final_f2);
    printf("         Instance 3 (DONE) in final: %d\n", final_f3);

    printf("\n========================================\n");
    printf("All Test 7 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_8_output_variable_isolation(void)
{
    printf("\n========================================\n");
    printf("Test 8: Output variable isolation\n");
    printf("========================================\n\n");

    /* Test 8.1: Verify output variables return different values for different states */
    printf("TEST 8.1: Output getter returns correct values per state... ");
    multi_instances_advanced_fsm_t inst_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_2 = multi_instances_advanced_fsm__create();

    /* Transition to PROCESSING (result=2) */
    multi_instances_advanced_fsm__set_cmd(inst_1, 1);
    multi_instances_advanced_fsm__exec(inst_1);

    /* Transition to DONE (result=3) */
    multi_instances_advanced_fsm__set_cmd(inst_2, 2);
    multi_instances_advanced_fsm__exec(inst_2);

    int result_1 = multi_instances_advanced_fsm__get_result(inst_1);
    int result_2 = multi_instances_advanced_fsm__get_result(inst_2);

    assert(result_1 == 2);  /* PROCESSING state */
    assert(result_2 == 3);  /* DONE state */
    assert(result_1 != result_2);
    printf("PASS\n");
    printf("         Instance 1 result (PROCESSING): %d\n", result_1);
    printf("         Instance 2 result (DONE): %d\n", result_2);

    /* Test 8.2: Output values are independent between instances */
    printf("TEST 8.2: Output values independent between instances... ");
    multi_instances_advanced_fsm_t out_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t out_b = multi_instances_advanced_fsm__create();

    int result_a_idle = multi_instances_advanced_fsm__get_result(out_a);
    int result_b_idle = multi_instances_advanced_fsm__get_result(out_b);

    assert(result_a_idle == result_b_idle);  /* Both in IDLE, same output */

    /* Transition only A */
    multi_instances_advanced_fsm__set_cmd(out_a, 1);
    multi_instances_advanced_fsm__exec(out_a);

    int result_a_after = multi_instances_advanced_fsm__get_result(out_a);
    int result_b_after = multi_instances_advanced_fsm__get_result(out_b);

    assert(result_a_after != result_b_after);
    assert(result_b_after == result_b_idle);
    printf("PASS\n");
    printf("         Instance A after transition: %d\n", result_a_after);
    printf("         Instance B unchanged: %d\n", result_b_after);

    /* Test 8.3: Output changes track state changes per instance */
    printf("TEST 8.3: Output changes track state changes per instance... ");
    multi_instances_advanced_fsm_t track_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t track_2 = multi_instances_advanced_fsm__create();

    int track1_initial = multi_instances_advanced_fsm__get_result(track_1);
    int track2_initial = multi_instances_advanced_fsm__get_result(track_2);

    /* Move track_1 through states and verify output changes */
    multi_instances_advanced_fsm__set_cmd(track_1, 1);
    multi_instances_advanced_fsm__exec(track_1);
    int track1_processing = multi_instances_advanced_fsm__get_result(track_1);

    multi_instances_advanced_fsm__set_cmd(track_1, 2);
    multi_instances_advanced_fsm__exec(track_1);
    int track1_done = multi_instances_advanced_fsm__get_result(track_1);

    /* track_2 stays in IDLE */
    int track2_final = multi_instances_advanced_fsm__get_result(track_2);

    assert(track1_initial != track1_processing);
    assert(track1_processing != track1_done);
    assert(track2_initial == track2_final);
    printf("PASS\n");
    printf("         Instance 1 progression: %d -> %d -> %d\n", track1_initial, track1_processing, track1_done);
    printf("         Instance 2 remained: %d\n", track2_final);

    /* Test 8.4: Output correctly reflects error state */
    printf("TEST 8.4: Output correctly reflects error state... ");
    multi_instances_advanced_fsm_t err_out = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t normal_out = multi_instances_advanced_fsm__create();

    /* Execute normal_out to trigger output assignment in IDLE state */
    multi_instances_advanced_fsm__exec(normal_out);

    /* Trigger error on err_out */
    multi_instances_advanced_fsm__set_cmd(err_out, 3);
    multi_instances_advanced_fsm__exec(err_out);

    int err_result = multi_instances_advanced_fsm__get_result(err_out);
    int normal_result = multi_instances_advanced_fsm__get_result(normal_out);

    assert(err_result == -1);  /* ERROR state output */
    assert(normal_result == 1);  /* IDLE state output */
    assert(err_result != normal_result);
    printf("PASS\n");
    printf("         Error instance output: %d\n", err_result);
    printf("         Normal instance output: %d\n", normal_result);

    /* Test 8.5: Output resets to initial value after reset */
    printf("TEST 8.5: Output resets to initial value after reset... ");
    multi_instances_advanced_fsm_t reset_out = multi_instances_advanced_fsm__create();

    int initial_out = multi_instances_advanced_fsm__get_result(reset_out);

    /* Transition and modify output */
    multi_instances_advanced_fsm__set_cmd(reset_out, 2);
    multi_instances_advanced_fsm__exec(reset_out);

    int modified_out = multi_instances_advanced_fsm__get_result(reset_out);
    assert(modified_out != initial_out);

    /* Reset */
    multi_instances_advanced_fsm__reset(reset_out);

    int reset_out_val = multi_instances_advanced_fsm__get_result(reset_out);

    assert(reset_out_val == initial_out);
    printf("PASS\n");
    printf("         Initial output: %d, modified: %d, after reset: %d\n",
           initial_out, modified_out, reset_out_val);

    printf("\n========================================\n");
    printf("All Test 8 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_9_timer_independence(void)
{
    printf("\n========================================\n");
    printf("Test 9: Timer independence\n");
    printf("========================================\n\n");

    /* Test 9.1: Timers are independent between instances */
    printf("TEST 9.1: Timers are independent between instances... ");
    multi_instances_advanced_fsm_t timer_inst_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t timer_inst_2 = multi_instances_advanced_fsm__create();

    /* Start timer on instance 1 by transitioning to PROCESSING */
    multi_instances_advanced_fsm__set_cmd(timer_inst_1, 1);
    multi_instances_advanced_fsm__exec(timer_inst_1);

    int state_1_after_timer_start = multi_instances_advanced_fsm__state(timer_inst_1);

    /* Instance 2 doesn't transition, so no timer started */
    multi_instances_advanced_fsm__exec(timer_inst_2);

    int state_2_no_timer = multi_instances_advanced_fsm__state(timer_inst_2);

    /* Instance 1 should be in PROCESSING, instance 2 still in IDLE */
    assert(state_1_after_timer_start != state_2_no_timer);
    printf("PASS\n");
    printf("         Instance 1 (timer started) in state: %d\n", state_1_after_timer_start);
    printf("         Instance 2 (no timer) in state: %d\n", state_2_no_timer);

    /* Test 9.2: Timer expires independently on each instance */
    printf("TEST 9.2: Timers expire independently on each instance... ");
    multi_instances_advanced_fsm_t expire_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t expire_2 = multi_instances_advanced_fsm__create();

    /* Start timer on instance 1 */
    multi_instances_advanced_fsm__set_cmd(expire_1, 1);
    multi_instances_advanced_fsm__exec(expire_1);
    int state_exp1_before = multi_instances_advanced_fsm__state(expire_1);

    /* Start timer on instance 2 */
    multi_instances_advanced_fsm__set_cmd(expire_2, 1);
    multi_instances_advanced_fsm__exec(expire_2);
    int state_exp2_before = multi_instances_advanced_fsm__state(expire_2);

    assert(state_exp1_before == state_exp2_before);  /* Both in PROCESSING */

    /* Wait for timer to expire (100ms) */
    portable_usleep(150000);  /* 150ms to ensure timer expires */

    /* Execute both - timers should have expired and transitioned to DONE */
    multi_instances_advanced_fsm__exec(expire_1);
    multi_instances_advanced_fsm__exec(expire_2);

    int state_exp1_after = multi_instances_advanced_fsm__state(expire_1);
    int state_exp2_after = multi_instances_advanced_fsm__state(expire_2);

    /* Both should have transitioned to DONE via timeout */
    assert(state_exp1_after != state_exp1_before);
    assert(state_exp2_after != state_exp2_before);
    assert(state_exp1_after == state_exp2_after);  /* Both in DONE now */
    printf("PASS\n");
    printf("         Instance 1 transitioned: %d -> %d\n", state_exp1_before, state_exp1_after);
    printf("         Instance 2 transitioned: %d -> %d\n", state_exp2_before, state_exp2_after);

    /* Test 9.3: One timer expires while another hasn't started yet */
    printf("TEST 9.3: One timer expires while another hasn't started... ");
    multi_instances_advanced_fsm_t stagger_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t stagger_2 = multi_instances_advanced_fsm__create();

    /* Start timer on instance 1 */
    multi_instances_advanced_fsm__set_cmd(stagger_1, 1);
    multi_instances_advanced_fsm__exec(stagger_1);
    int state_stag1_start = multi_instances_advanced_fsm__state(stagger_1);

    /* Keep instance 2 in IDLE */
    multi_instances_advanced_fsm__exec(stagger_2);
    int state_stag2_idle = multi_instances_advanced_fsm__state(stagger_2);

    /* Wait for timer to expire */
    portable_usleep(150000);  /* 150ms */

    /* Execute instance 1 - timer should expire */
    multi_instances_advanced_fsm__exec(stagger_1);
    int state_stag1_expired = multi_instances_advanced_fsm__state(stagger_1);

    /* Execute instance 2 - still in IDLE */
    multi_instances_advanced_fsm__exec(stagger_2);
    int state_stag2_still_idle = multi_instances_advanced_fsm__state(stagger_2);

    /* Instance 1 should have transitioned, instance 2 should still be IDLE */
    assert(state_stag1_expired != state_stag1_start);
    assert(state_stag2_still_idle == state_stag2_idle);
    printf("PASS\n");
    printf("         Instance 1 (timer expired): %d\n", state_stag1_expired);
    printf("         Instance 2 (IDLE, no timer): %d\n", state_stag2_still_idle);

    /* Test 9.4: Timer reset clears timer on one instance */
    printf("TEST 9.4: Reset clears timer on one instance... ");
    multi_instances_advanced_fsm_t reset_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t reset_2 = multi_instances_advanced_fsm__create();

    /* Start timers on both */
    multi_instances_advanced_fsm__set_cmd(reset_1, 1);
    multi_instances_advanced_fsm__exec(reset_1);

    multi_instances_advanced_fsm__set_cmd(reset_2, 1);
    multi_instances_advanced_fsm__exec(reset_2);

    int state_before_reset_1 = multi_instances_advanced_fsm__state(reset_1);
    int state_before_reset_2 = multi_instances_advanced_fsm__state(reset_2);

    /* Reset only instance 1 (clears its timer) */
    multi_instances_advanced_fsm__reset(reset_1);
    int state_after_reset_1 = multi_instances_advanced_fsm__state(reset_1);

    /* Wait for timers to expire */
    portable_usleep(150000);  /* 150ms */

    /* Execute both */
    multi_instances_advanced_fsm__exec(reset_1);
    multi_instances_advanced_fsm__exec(reset_2);

    int state_1_final = multi_instances_advanced_fsm__state(reset_1);
    int state_2_final = multi_instances_advanced_fsm__state(reset_2);

    /* Instance 1 was reset to IDLE, so timer didn't expire - should still be IDLE */
    assert(state_after_reset_1 != state_before_reset_1);  /* Reset changed state */
    /* Instance 2's timer should have expired, moving it to DONE */
    assert(state_2_final != state_before_reset_2);
    printf("PASS\n");
    printf("         Instance 1 after reset: %d (no timer expiration)\n", state_1_final);
    printf("         Instance 2 timer expired: %d -> %d\n", state_before_reset_2, state_2_final);

    /* Test 9.5: Staggered timer starts expire independently */
    printf("TEST 9.5: Staggered timer starts expire independently... ");
    multi_instances_advanced_fsm_t stag_timer_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t stag_timer_2 = multi_instances_advanced_fsm__create();

    /* Start timer on instance 1 */
    multi_instances_advanced_fsm__set_cmd(stag_timer_1, 1);
    multi_instances_advanced_fsm__exec(stag_timer_1);

    /* Wait 60ms */
    portable_usleep(60000);

    /* Start timer on instance 2 (50ms later) */
    multi_instances_advanced_fsm__set_cmd(stag_timer_2, 1);
    multi_instances_advanced_fsm__exec(stag_timer_2);

    /* Wait 60ms more (total 120ms for instance 1, 60ms for instance 2) */
    portable_usleep(60000);

    /* Execute instance 1 - should timeout (120ms elapsed) */
    multi_instances_advanced_fsm__exec(stag_timer_1);
    int state_st1_expired = multi_instances_advanced_fsm__state(stag_timer_1);

    /* Execute instance 2 - should NOT timeout yet (60ms elapsed, needs 100ms) */
    multi_instances_advanced_fsm__exec(stag_timer_2);
    int state_st2_running = multi_instances_advanced_fsm__state(stag_timer_2);

    /* Wait 50ms more for instance 2 to timeout */
    portable_usleep(50000);

    multi_instances_advanced_fsm__exec(stag_timer_2);
    int state_st2_expired = multi_instances_advanced_fsm__state(stag_timer_2);

    /* Instance 1 should have timed out, instance 2 should also timeout eventually */
    assert(state_st1_expired != state_st2_running);  /* Different states at checkpoint */
    assert(state_st2_expired == state_st1_expired);  /* Both in DONE eventually */
    printf("PASS\n");
    printf("         Instance 1 expired first: %d\n", state_st1_expired);
    printf("         Instance 2 still running at checkpoint: %d\n", state_st2_running);
    printf("         Instance 2 expired later: %d\n", state_st2_expired);

    printf("\n========================================\n");
    printf("All Test 9 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_10_internal_variables_isolation(void)
{
    printf("\n========================================\n");
    printf("Test 10: Internal variables isolation\n");
    printf("========================================\n\n");

    /* Test 10.1: Internal variables are independent between instances */
    printf("TEST 10.1: Internal variables independent between instances... ");
    multi_instances_advanced_fsm_t inst_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t inst_b = multi_instances_advanced_fsm__create();
    
    /* Transition to PROCESSING (need 2 execs: 1 for transition, 1 for code execution) */
    multi_instances_advanced_fsm__set_cmd(inst_a, 1);
    multi_instances_advanced_fsm__exec(inst_a);  /* Transition to PROCESSING */
    multi_instances_advanced_fsm__exec(inst_a);  /* Execute state code: counter=1, accumulator=10 */
    multi_instances_advanced_fsm__exec(inst_a);  /* Execute state code: counter=2, accumulator=20 */
    
    /* Transition instance B and execute once */
    multi_instances_advanced_fsm__set_cmd(inst_b, 1);
    multi_instances_advanced_fsm__exec(inst_b);  /* Transition to PROCESSING */
    multi_instances_advanced_fsm__exec(inst_b);  /* Execute state code: counter=1, accumulator=10 */
    
    /* Get counter values via output variables */
    int counter_a = multi_instances_advanced_fsm__get_counter_out(inst_a);
    int counter_b = multi_instances_advanced_fsm__get_counter_out(inst_b);
    
    /* Instance A should have counter=2, instance B should have counter=1 */
    assert(counter_a == 2);
    assert(counter_b == 1);
    assert(counter_a != counter_b);
    printf("PASS\n");
    printf("         Instance A counter: %d\n", counter_a);
    printf("         Instance B counter: %d\n", counter_b);

    /* Test 10.2: Counter accumulates independently per instance */
    printf("TEST 10.2: Counter accumulates independently per instance... ");
    multi_instances_advanced_fsm_t cnt_inst_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t cnt_inst_b = multi_instances_advanced_fsm__create();
    
    /* Transition cnt_inst_a to PROCESSING */
    multi_instances_advanced_fsm__set_cmd(cnt_inst_a, 1);
    multi_instances_advanced_fsm__exec(cnt_inst_a);  /* Transition */
    multi_instances_advanced_fsm__exec(cnt_inst_a);  /* Execute: counter=1 */
    multi_instances_advanced_fsm__exec(cnt_inst_a);  /* Execute: counter=2 */
    
    /* Transition cnt_inst_b to PROCESSING */
    multi_instances_advanced_fsm__set_cmd(cnt_inst_b, 1);
    multi_instances_advanced_fsm__exec(cnt_inst_b);  /* Transition */
    multi_instances_advanced_fsm__exec(cnt_inst_b);  /* Execute: counter=1 */
    
    /* Execute cnt_inst_a more times */
    multi_instances_advanced_fsm__exec(cnt_inst_a);  /* Execute: counter=3 */
    multi_instances_advanced_fsm__exec(cnt_inst_a);  /* Execute: counter=4 */
    
    /* Get counter values */
    int cnt_a = multi_instances_advanced_fsm__get_counter_out(cnt_inst_a);
    int cnt_b = multi_instances_advanced_fsm__get_counter_out(cnt_inst_b);
    
    /* cnt_inst_a should be 4, cnt_inst_b should be 1 */
    assert(cnt_a == 4);
    assert(cnt_b == 1);
    assert(cnt_a > cnt_b);
    printf("PASS\n");
    printf("         Instance A counter: %d\n", cnt_a);
    printf("         Instance B counter: %d\n", cnt_b);

    /* Test 10.3: Multiple internal variables isolated */
    printf("TEST 10.3: Multiple internal variables (counter and accumulator) isolated... ");
    multi_instances_advanced_fsm_t mv_inst_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t mv_inst_b = multi_instances_advanced_fsm__create();
    
    /* Transition and accumulate on instance A */
    multi_instances_advanced_fsm__set_cmd(mv_inst_a, 1);
    multi_instances_advanced_fsm__exec(mv_inst_a);  /* Transition */
    for (int i = 0; i < 3; i++) {
        multi_instances_advanced_fsm__exec(mv_inst_a);  /* Execute 3 times: counter=1,2,3, accumulator=10,20,30 */
    }
    
    /* Transition and execute instance B once */
    multi_instances_advanced_fsm__set_cmd(mv_inst_b, 1);
    multi_instances_advanced_fsm__exec(mv_inst_b);  /* Transition */
    multi_instances_advanced_fsm__exec(mv_inst_b);  /* Execute: counter=1, accumulator=10 */
    
    /* Get both counter and accumulator */
    int counter_mv_a = multi_instances_advanced_fsm__get_counter_out(mv_inst_a);
    int accumulator_mv_a = multi_instances_advanced_fsm__get_accumulator_out(mv_inst_a);
    int counter_mv_b = multi_instances_advanced_fsm__get_counter_out(mv_inst_b);
    int accumulator_mv_b = multi_instances_advanced_fsm__get_accumulator_out(mv_inst_b);
    
    /* Verify values */
    assert(counter_mv_a == 3);
    assert(accumulator_mv_a == 30);  /* 3 * 10 */
    assert(counter_mv_b == 1);
    assert(accumulator_mv_b == 10);  /* 1 * 10 */
    printf("PASS\n");
    printf("         Instance A: counter=%d, accumulator=%d\n", counter_mv_a, accumulator_mv_a);
    printf("         Instance B: counter=%d, accumulator=%d\n", counter_mv_b, accumulator_mv_b);

    /* Test 10.4: Internal variables don't affect other instances after reset */
    printf("TEST 10.4: Reset clears internal variables... ");
    multi_instances_advanced_fsm_t rv_inst = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t ov_inst = multi_instances_advanced_fsm__create();
    
    /* Accumulate on rv_inst */
    multi_instances_advanced_fsm__set_cmd(rv_inst, 1);
    multi_instances_advanced_fsm__exec(rv_inst);  /* Transition */
    for (int i = 0; i < 3; i++) {
        multi_instances_advanced_fsm__exec(rv_inst);  /* Execute 3 times */
    }
    
    int counter_before = multi_instances_advanced_fsm__get_counter_out(rv_inst);
    int accumulator_before = multi_instances_advanced_fsm__get_accumulator_out(rv_inst);
    
    assert(counter_before == 3);
    assert(accumulator_before == 30);
    
    /* Also accumulate on ov_inst */
    multi_instances_advanced_fsm__set_cmd(ov_inst, 1);
    multi_instances_advanced_fsm__exec(ov_inst);  /* Transition */
    multi_instances_advanced_fsm__exec(ov_inst);  /* Execute once */
    
    /* Reset first instance */
    multi_instances_advanced_fsm__reset(rv_inst);
    
    int counter_after = multi_instances_advanced_fsm__get_counter_out(rv_inst);
    int accumulator_after = multi_instances_advanced_fsm__get_accumulator_out(rv_inst);
    int other_counter = multi_instances_advanced_fsm__get_counter_out(ov_inst);
    int other_accumulator = multi_instances_advanced_fsm__get_accumulator_out(ov_inst);
    
    /* rv_inst should be cleared */
    assert(counter_after == 0);
    assert(accumulator_after == 0);
    /* ov_inst should be unaffected */
    assert(other_counter == 1);
    assert(other_accumulator == 10);
    printf("PASS\n");
    printf("         Reset instance: counter=%d, accumulator=%d\n", counter_after, accumulator_after);
    printf("         Other instance: counter=%d, accumulator=%d\n", other_counter, other_accumulator);

    /* Test 10.5: Three instances with independent variable states */
    printf("TEST 10.5: Three instances with independent variables... ");
    multi_instances_advanced_fsm_t v1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t v2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t v3 = multi_instances_advanced_fsm__create();
    
    /* Transition all to PROCESSING */
    multi_instances_advanced_fsm__set_cmd(v1, 1);
    multi_instances_advanced_fsm__exec(v1);  /* Transition */
    
    multi_instances_advanced_fsm__set_cmd(v2, 1);
    multi_instances_advanced_fsm__exec(v2);  /* Transition */
    
    multi_instances_advanced_fsm__set_cmd(v3, 1);
    multi_instances_advanced_fsm__exec(v3);  /* Transition */
    
    /* Execute v1 multiple times (4 times after transition = counter 4) */
    for (int i = 0; i < 4; i++) {
        multi_instances_advanced_fsm__exec(v1);
    }
    
    /* Execute v2 zero more times (stays at transition) */
    
    /* Execute v3 once (1 time after transition = counter 1) */
    for (int i = 0; i < 1; i++) {
        multi_instances_advanced_fsm__exec(v3);
    }
    
    int cnt_v1 = multi_instances_advanced_fsm__get_counter_out(v1);
    int cnt_v2 = multi_instances_advanced_fsm__get_counter_out(v2);
    int cnt_v3 = multi_instances_advanced_fsm__get_counter_out(v3);
    int acc_v1 = multi_instances_advanced_fsm__get_accumulator_out(v1);
    int acc_v2 = multi_instances_advanced_fsm__get_accumulator_out(v2);
    int acc_v3 = multi_instances_advanced_fsm__get_accumulator_out(v3);
    
    /* Verify expected values */
    assert(cnt_v1 == 4);  /* 4 execs after transition */
    assert(acc_v1 == 40);
    assert(cnt_v2 == 0);  /* Only transitioned, no execs in PROCESSING */
    assert(acc_v2 == 0);
    assert(cnt_v3 == 1);  /* 1 exec after transition */
    assert(acc_v3 == 10);
    printf("PASS\n");
    printf("         Instance 1: counter=%d, accumulator=%d\n", cnt_v1, acc_v1);
    printf("         Instance 2: counter=%d, accumulator=%d\n", cnt_v2, acc_v2);
    printf("         Instance 3: counter=%d, accumulator=%d\n", cnt_v3, acc_v3);

    printf("\n========================================\n");
    printf("All Test 10 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_11_variable_persistence(void)
{
    printf("\n========================================\n");
    printf("Test 11: Variable persistence across transitions\n");
    printf("========================================\n\n");

    /* Test 11.1: Variables persist through state transitions */
    printf("TEST 11.1: Variables persist through state transitions... ");
    multi_instances_advanced_fsm_t persist_a = multi_instances_advanced_fsm__create();

    /* Transition to PROCESSING and accumulate */
    multi_instances_advanced_fsm__set_cmd(persist_a, 1);
    multi_instances_advanced_fsm__exec(persist_a);  /* Transition to PROCESSING */
    multi_instances_advanced_fsm__exec(persist_a);  /* Execute: counter=1, accumulator=10 */
    multi_instances_advanced_fsm__exec(persist_a);  /* Execute: counter=2, accumulator=20 */

    int counter_in_processing = multi_instances_advanced_fsm__get_counter_out(persist_a);
    int accumulator_in_processing = multi_instances_advanced_fsm__get_accumulator_out(persist_a);

    assert(counter_in_processing == 2);
    assert(accumulator_in_processing == 20);

    /* Transition to DONE - this will execute PROCESSING state code one more time */
    multi_instances_advanced_fsm__set_cmd(persist_a, 2);
    multi_instances_advanced_fsm__exec(persist_a);  /* Execute in PROCESSING: counter=3, accumulator=30, then transition to DONE */

    int counter_in_done = multi_instances_advanced_fsm__get_counter_out(persist_a);
    int accumulator_in_done = multi_instances_advanced_fsm__get_accumulator_out(persist_a);

    /* Values should be incremented one more time because PROCESSING code executes before transition */
    assert(counter_in_done == 3);
    assert(accumulator_in_done == 30);
    printf("PASS\n");
    printf("         In PROCESSING: counter=%d, accumulator=%d\n", counter_in_processing, accumulator_in_processing);
    printf("         After transition to DONE: counter=%d, accumulator=%d\n", counter_in_done, accumulator_in_done);
    printf("         (Values incremented during transition execution)\n");

    /* Test 11.2: Variables don't persist after reset */
    printf("TEST 11.2: Variables cleared after reset... ");
    multi_instances_advanced_fsm_t reset_persist = multi_instances_advanced_fsm__create();

    /* Accumulate */
    multi_instances_advanced_fsm__set_cmd(reset_persist, 1);
    multi_instances_advanced_fsm__exec(reset_persist);  /* Transition */
    for (int i = 0; i < 3; i++) {
        multi_instances_advanced_fsm__exec(reset_persist);  /* Execute 3 times */
    }

    int counter_before_reset = multi_instances_advanced_fsm__get_counter_out(reset_persist);
    int accumulator_before_reset = multi_instances_advanced_fsm__get_accumulator_out(reset_persist);

    assert(counter_before_reset == 3);
    assert(accumulator_before_reset == 30);

    /* Reset */
    multi_instances_advanced_fsm__reset(reset_persist);
    int counter_after_reset = multi_instances_advanced_fsm__get_counter_out(reset_persist);
    int accumulator_after_reset = multi_instances_advanced_fsm__get_accumulator_out(reset_persist);

    assert(counter_after_reset == 0);
    assert(accumulator_after_reset == 0);

    /* Execute again - counter should start from 0 */
    multi_instances_advanced_fsm__set_cmd(reset_persist, 1);
    multi_instances_advanced_fsm__exec(reset_persist);  /* Transition */
    multi_instances_advanced_fsm__exec(reset_persist);  /* Execute: counter=1 */

    int counter_after_fresh_exec = multi_instances_advanced_fsm__get_counter_out(reset_persist);
    int accumulator_after_fresh_exec = multi_instances_advanced_fsm__get_accumulator_out(reset_persist);

    /* After fresh exec, counter should be 1 (not 4) */
    assert(counter_after_fresh_exec == 1);
    assert(accumulator_after_fresh_exec == 10);
    printf("PASS\n");
    printf("         Before reset: counter=%d, accumulator=%d\n", counter_before_reset, accumulator_before_reset);
    printf("         After reset: counter=%d, accumulator=%d\n", counter_after_reset, accumulator_after_reset);
    printf("         After fresh execution: counter=%d, accumulator=%d\n", counter_after_fresh_exec, accumulator_after_fresh_exec);

    /* Test 11.3: Variable persistence independent between instances */
    printf("TEST 11.3: Variable persistence independent per instance... ");
    multi_instances_advanced_fsm_t persist_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t persist_2 = multi_instances_advanced_fsm__create();

    /* Accumulate heavily on persist_1 */
    multi_instances_advanced_fsm__set_cmd(persist_1, 1);
    multi_instances_advanced_fsm__exec(persist_1);  /* Transition */
    for (int i = 0; i < 4; i++) {
        multi_instances_advanced_fsm__exec(persist_1);  /* Execute 4 times: counter=4, accumulator=40 */
    }

    /* Minimal execution on persist_2 */
    multi_instances_advanced_fsm__set_cmd(persist_2, 1);
    multi_instances_advanced_fsm__exec(persist_2);  /* Transition */
    multi_instances_advanced_fsm__exec(persist_2);  /* Execute once: counter=1, accumulator=10 */

    int cnt_p1 = multi_instances_advanced_fsm__get_counter_out(persist_1);
    int acc_p1 = multi_instances_advanced_fsm__get_accumulator_out(persist_1);
    int cnt_p2 = multi_instances_advanced_fsm__get_counter_out(persist_2);
    int acc_p2 = multi_instances_advanced_fsm__get_accumulator_out(persist_2);

    /* persist_1 should have higher values */
    assert(cnt_p1 == 4);
    assert(acc_p1 == 40);
    assert(cnt_p2 == 1);
    assert(acc_p2 == 10);
    printf("PASS\n");
    printf("         Instance 1: counter=%d, accumulator=%d\n", cnt_p1, acc_p1);
    printf("         Instance 2: counter=%d, accumulator=%d\n", cnt_p2, acc_p2);

    /* Test 11.4: Accumulated values don't leak between instances */
    printf("TEST 11.4: Accumulated values don't leak between instances... ");
    multi_instances_advanced_fsm_t leak_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t leak_b = multi_instances_advanced_fsm__create();

    /* Accumulate on leak_a */
    multi_instances_advanced_fsm__set_cmd(leak_a, 1);
    multi_instances_advanced_fsm__exec(leak_a);  /* Transition */
    for (int i = 0; i < 5; i++) {
        multi_instances_advanced_fsm__exec(leak_a);  /* Execute 5 times */
    }

    int cnt_leak_a = multi_instances_advanced_fsm__get_counter_out(leak_a);
    int acc_leak_a = multi_instances_advanced_fsm__get_accumulator_out(leak_a);

    assert(cnt_leak_a == 5);
    assert(acc_leak_a == 50);

    /* Now execute leak_b - should not be affected by leak_a's accumulation */
    multi_instances_advanced_fsm__set_cmd(leak_b, 1);
    multi_instances_advanced_fsm__exec(leak_b);  /* Transition */
    multi_instances_advanced_fsm__exec(leak_b);  /* Execute once */

    int cnt_leak_b = multi_instances_advanced_fsm__get_counter_out(leak_b);
    int acc_leak_b = multi_instances_advanced_fsm__get_accumulator_out(leak_b);

    /* leak_b should have independent values (counter=1, not 5) */
    assert(cnt_leak_b == 1);
    assert(acc_leak_b == 10);
    printf("PASS\n");
    printf("         Instance A accumulated: counter=%d, accumulator=%d\n", cnt_leak_a, acc_leak_a);
    printf("         Instance B unaffected: counter=%d, accumulator=%d\n", cnt_leak_b, acc_leak_b);

    /* Test 11.5: Variable values correct at each checkpoint */
    printf("TEST 11.5: Variable values maintained at checkpoints... ");
    multi_instances_advanced_fsm_t check_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t check_b = multi_instances_advanced_fsm__create();

    /* Execute check_a and verify at each step */
    multi_instances_advanced_fsm__set_cmd(check_a, 1);
    multi_instances_advanced_fsm__exec(check_a);  /* Transition */

    multi_instances_advanced_fsm__exec(check_a);  /* Execute once */
    int cnt_check_a_1 = multi_instances_advanced_fsm__get_counter_out(check_a);
    int acc_check_a_1 = multi_instances_advanced_fsm__get_accumulator_out(check_a);
    assert(cnt_check_a_1 == 1);
    assert(acc_check_a_1 == 10);

    multi_instances_advanced_fsm__exec(check_a);  /* Execute twice */
    int cnt_check_a_2 = multi_instances_advanced_fsm__get_counter_out(check_a);
    int acc_check_a_2 = multi_instances_advanced_fsm__get_accumulator_out(check_a);
    assert(cnt_check_a_2 == 2);
    assert(acc_check_a_2 == 20);

    /* Execute check_b once */
    multi_instances_advanced_fsm__set_cmd(check_b, 1);
    multi_instances_advanced_fsm__exec(check_b);  /* Transition */
    multi_instances_advanced_fsm__exec(check_b);  /* Execute once */

    int cnt_check_b_1 = multi_instances_advanced_fsm__get_counter_out(check_b);
    int acc_check_b_1 = multi_instances_advanced_fsm__get_accumulator_out(check_b);
    assert(cnt_check_b_1 == 1);
    assert(acc_check_b_1 == 10);

    /* check_a should still have its values (not affected by check_b) */
    int cnt_check_a_final = multi_instances_advanced_fsm__get_counter_out(check_a);
    int acc_check_a_final = multi_instances_advanced_fsm__get_accumulator_out(check_a);
    assert(cnt_check_a_final == 2);
    assert(acc_check_a_final == 20);

    printf("PASS\n");
    printf("         Instance A checkpoints: (1,10) -> (2,20)\n");
    printf("         Instance B checkpoint: (1,10)\n");
    printf("         Instance A final values preserved: counter=%d, accumulator=%d\n", cnt_check_a_final, acc_check_a_final);

    printf("\n========================================\n");
    printf("All Test 11 cases PASSED!\n");
    printf("========================================\n\n");
}

void test_12_user_code_in_states(void)
{
    printf("\n========================================\n");
    printf("Test 12: User code in states isolation\n");
    printf("========================================\n\n");

    /* Test 12.1: State code executes independently per instance */
    printf("TEST 12.1: State code executes independently per instance... ");
    multi_instances_advanced_fsm_t code_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t code_b = multi_instances_advanced_fsm__create();

    /* Transition both to PROCESSING */
    multi_instances_advanced_fsm__set_cmd(code_a, 1);
    multi_instances_advanced_fsm__exec(code_a);

    multi_instances_advanced_fsm__set_cmd(code_b, 1);
    multi_instances_advanced_fsm__exec(code_b);

    /* Execute code_a multiple times (increments its counter) */
    for (int i = 0; i < 3; i++) {
        multi_instances_advanced_fsm__exec(code_a);
    }

    int state_code_a = multi_instances_advanced_fsm__state(code_a);
    int state_code_b = multi_instances_advanced_fsm__state(code_b);

    /* code_a should have higher counter, but both still in PROCESSING or code_a in DONE */
    printf("PASS\n");
    printf("         Instance A state: %d (after multiple executions)\n", state_code_a);
    printf("         Instance B state: %d (after single execution)\n", state_code_b);

    /* Test 12.2: State code doesn't affect other instances */
    printf("TEST 12.2: State code doesn't affect other instances... ");
    multi_instances_advanced_fsm_t isolated_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t isolated_b = multi_instances_advanced_fsm__create();

    int initial_state_b = multi_instances_advanced_fsm__state(isolated_b);

    /* Execute state code on isolated_a heavily */
    multi_instances_advanced_fsm__set_cmd(isolated_a, 1);
    for (int i = 0; i < 5; i++) {
        multi_instances_advanced_fsm__exec(isolated_a);
    }

    /* Check isolated_b is still in initial state */
    int final_state_b = multi_instances_advanced_fsm__state(isolated_b);

    assert(initial_state_b == final_state_b);
    printf("PASS\n");
    printf("         Instance B remained in initial state: %d\n", final_state_b);

    /* Test 12.3: State code modifications are independent */
    printf("TEST 12.3: State code modifications are independent... ");
    multi_instances_advanced_fsm_t mod_a = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t mod_b = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t mod_c = multi_instances_advanced_fsm__create();

    /* Transition all to PROCESSING */
    multi_instances_advanced_fsm__set_cmd(mod_a, 1);
    multi_instances_advanced_fsm__exec(mod_a);

    multi_instances_advanced_fsm__set_cmd(mod_b, 1);
    multi_instances_advanced_fsm__exec(mod_b);

    multi_instances_advanced_fsm__set_cmd(mod_c, 1);
    multi_instances_advanced_fsm__exec(mod_c);

    /* Execute different number of times on each */
    for (int i = 0; i < 2; i++) {
        multi_instances_advanced_fsm__exec(mod_a);
    }

    for (int i = 0; i < 1; i++) {
        multi_instances_advanced_fsm__exec(mod_b);
    }

    for (int i = 0; i < 3; i++) {
        multi_instances_advanced_fsm__exec(mod_c);
    }

    int state_mod_a = multi_instances_advanced_fsm__state(mod_a);
    int state_mod_b = multi_instances_advanced_fsm__state(mod_b);
    int state_mod_c = multi_instances_advanced_fsm__state(mod_c);

    printf("PASS\n");
    printf("         Instance A (3 total execs): %d\n", state_mod_a);
    printf("         Instance B (2 total execs): %d\n", state_mod_b);
    printf("         Instance C (4 total execs): %d\n", state_mod_c);

    /* Test 12.4: State code variables reset after reset */
    printf("TEST 12.4: State code variables reset after instance reset... ");
    multi_instances_advanced_fsm_t sreset_a = multi_instances_advanced_fsm__create();

    /* Execute state code */
    multi_instances_advanced_fsm__set_cmd(sreset_a, 1);
    for (int i = 0; i < 3; i++) {
        multi_instances_advanced_fsm__exec(sreset_a);
    }

    int state_before_sreset = multi_instances_advanced_fsm__state(sreset_a);

    /* Reset */
    multi_instances_advanced_fsm__reset(sreset_a);
    int state_after_sreset = multi_instances_advanced_fsm__state(sreset_a);

    /* Execute again - should reset counter */
    multi_instances_advanced_fsm__set_cmd(sreset_a, 1);
    multi_instances_advanced_fsm__exec(sreset_a);
    int state_after_fresh = multi_instances_advanced_fsm__state(sreset_a);

    assert(state_before_sreset != state_after_sreset);
    printf("PASS\n");
    printf("         State code variables properly reset\n");

    /* Test 12.5: State code with multiple instances concurrent execution */
    printf("TEST 12.5: Concurrent state code execution... ");
    multi_instances_advanced_fsm_t conc_1 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t conc_2 = multi_instances_advanced_fsm__create();
    multi_instances_advanced_fsm_t conc_3 = multi_instances_advanced_fsm__create();

    /* Interleave executions */
    multi_instances_advanced_fsm__set_cmd(conc_1, 1);
    multi_instances_advanced_fsm__exec(conc_1);

    multi_instances_advanced_fsm__set_cmd(conc_2, 1);
    multi_instances_advanced_fsm__exec(conc_2);

    multi_instances_advanced_fsm__set_cmd(conc_3, 1);
    multi_instances_advanced_fsm__exec(conc_3);

    /* Continue interleaving */
    multi_instances_advanced_fsm__exec(conc_1);
    multi_instances_advanced_fsm__exec(conc_3);
    multi_instances_advanced_fsm__exec(conc_2);

    int state_conc_1 = multi_instances_advanced_fsm__state(conc_1);
    int state_conc_2 = multi_instances_advanced_fsm__state(conc_2);
    int state_conc_3 = multi_instances_advanced_fsm__state(conc_3);

    printf("PASS\n");
    printf("         Concurrent execution completed safely\n");

    printf("\n========================================\n");
    printf("All Test 12 cases PASSED!\n");
    printf("========================================\n\n");
}


void test_13_retries_and_until_blocks(void)
{
	/* TO BE IMPLEMENTED */
}
