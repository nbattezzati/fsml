#include <stdio.h>
#include <assert.h>
#include "alarm_fsm.h"


void print_menu()
{
    printf("To program the Alarm you can:\n");
    printf("   * press S [set] to enter programming mode or change between hours and minutes\n");
    printf("   * press + [plus] to increment the hours/minutes\n");
    printf("   * press - [minus] to decrement the hours/minutes\n");
    printf("   * press Q [quit] to exit the program");
    printf("\n");
}

void print_cur_time(const alarm_time_t * cur_t, alarm_state_t state)
{
    if (state == alarmState__SET_HOUR) {
        printf("%.2d:--\n", cur_t->hour);
    }
    else if (state == alarmState__SET_MINUTE) {
        printf("--:%.2d\n", cur_t->minute);
    }
    else {
        printf("%.2d:%.2d\n", cur_t->hour, cur_t->minute);
    }
}

alarm_cmd_t wait_command(unsigned char * quit)
{
    char cmd_str[16] = {""};
    char cmd = '\0';
    
    *quit = 0;

    printf ("Insert command: ");
    fgets(cmd_str, sizeof(cmd_str), stdin);
    if (sscanf(cmd_str, "%c", &cmd) > 0) {
        switch(cmd) {
            case 'S': return AlarmCmd_ProgrSet;
            case '+': return AlarmCmd_ProgrPlus;
            case '-': return AlarmCmd_ProgrMinus;
            case 'Q': *quit = 1;
            default:  return AlarmCmd_NoCommand;
        }
    }

    return AlarmCmd_NoCommand;
}

int main(int argc, char *argv[])
{
    int i = 0;
    unsigned char quit = 0;
    alarm_cmd_t cmd = AlarmCmd_NoCommand;
    alarm_time_t cur_time = {0};
    alarm_state_t cur_state = alarmState__PROGRAMMED;

    alarm_fsm_t alarm_fsm = alarm_fsm__create();
    assert(alarm_fsm != NULL);

    /* reset fsm to the starting state */
    alarm_fsm__reset(alarm_fsm);

    /* print menu */
    print_menu();
    
    do {
        
        cmd = wait_command(&quit);
        
        alarm_fsm__set_cmd(alarm_fsm, cmd);
        cur_state = alarm_fsm__exec(alarm_fsm);
        cur_time = alarm_fsm__get_alarm_time(alarm_fsm);

        print_cur_time(&cur_time, cur_state);
    } while (!quit);
}
