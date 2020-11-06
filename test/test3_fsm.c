/***********************************************************/
/*                    FSML DECLARATIONS                    */
/***********************************************************/

#include <stddef.h>
#include <time.h>
#include "test3_fsm.h"

// special states definition
#define __START_STATE   test3State__START_MAN
#define __ERR_STATE   test3State__FINISHED

// private variables
static test3_state_t __cur_state;
static test3_state_t __next_state;
static test3_err_t __err;
static unsigned int __retries_START_MAN;

// public function declarations
test3_state_t __get_state(void);
test3_err_t __get_err(void);
void __reset(void);
test3_state_t __exec(void);
// input setter and output getter functions
void __set_maneuver_duration(float);
void __set_q(struct quaternion *);
maneuver_out_state_t __get_man_state(void);


// FSM object to access internal variables
static test3_fsm_t this = {
    .state = __get_state,
    .err = __get_err,
    .reset = __reset,
    .exec = __exec,
   .get_man_state = __get_man_state,
   .set_maneuver_duration = __set_maneuver_duration,
   .set_q = __set_q

};
test3_fsm_t * test3_fsm = &this;

// timer declarations
typedef struct {
    struct timespec __started_time;
    unsigned int __timeout_ms;
} fsm_timer_t;
void fsm_timer_start(fsm_timer_t * t);
unsigned char fsm_timer_expired(fsm_timer_t * t);

/***********************************************************/
/*                     Timeout handling                     */
/***********************************************************/
struct timespec get_cur_time(void) {

	struct timespec t;
	rtems_clock_get_uptime(&t);
	return t;

}


/***********************************************************/
/*                      FSM variables                      */
/***********************************************************/
static maneuver_out_state_t man_state = ManeuverState_IDLE;
static float maneuver_duration = 0.100000;
static struct quaternion * q = NULL;
static quaternion_t q_err = {0};
static bool res = FALSE;
static unsigned long int * this_is_a_test = 0;


/***********************************************************/
/*                        FSM timers                        */
/***********************************************************/
static fsm_timer_t maneuver_timer;
static fsm_timer_t stable_timer;


/***********************************************************/
/*                     Output functions                     */
/***********************************************************/
// OUT Variable: man_state;
typedef maneuver_out_state_t (*__out_foo__man_state)(void);
maneuver_out_state_t __out_foo__man_state__FINISHED(void);
maneuver_out_state_t __out_foo__man_state__START_MAN(void);
static __out_foo__man_state __out_table__man_state[] = {
   __out_foo__man_state__FINISHED,
   __out_foo__man_state__START_MAN,
   NULL,
   NULL
};

// OUT Variable: man_state;
maneuver_out_state_t __out_foo__man_state__FINISHED(void)
{ return this.err() ? ManeuverState_ERR : ManeuverState_COMPLETE; }

maneuver_out_state_t __out_foo__man_state__START_MAN(void)
{ return ManeuverState_BUSY; }


/***********************************************************/
/*                     Timer functions                     */
/***********************************************************/

void fsm_timer_start(fsm_timer_t * t)
{
   t->__started_time = get_cur_time();
}

// return 0 if timeout is not elapsed, 1 if elapsed
unsigned char fsm_timer_expired(fsm_timer_t * t)
{
   struct timespec now_t = get_cur_time();
   long ms_diff = now_t.tv_nsec/1000000 - t->__started_time.tv_nsec/1000000;
   long s_diff = now_t.tv_sec - t->__started_time.tv_sec;
   double t_diff = ms_diff + s_diff*1000;

   return t_diff >= t->__timeout_ms;
}

/***********************************************************/
/*                     Public functions                     */
/***********************************************************/

// state getter function
test3_state_t __get_state(void)
{
    return __cur_state;
}

// error getter function
test3_err_t __get_err(void)
{
    return __err;
}

// input setter functions
void __set_maneuver_duration(float input)
{
   maneuver_duration = input;
}

void __set_q(struct quaternion * input)
{
   q = input;
}


// output getter functions
maneuver_out_state_t __get_man_state(void)
{
   return man_state;
}



// reset function
void __reset(void)
{
   // init private variables
   __cur_state = __START_STATE;
   __next_state = __START_STATE;
   __err = test3Err__NoError;

   // init timers
   maneuver_timer.__started_time = get_cur_time();
   maneuver_timer.__timeout_ms = maneuver_duration;
   stable_timer.__started_time = get_cur_time();
   stable_timer.__timeout_ms = ADCS_PERIOD;

   // init retry variables
   __retries_START_MAN = 0;
}


// execute function
test3_state_t __exec(void)
{
   // execute current state and transition evaluation
   switch(__cur_state) {
      case test3State__FINISHED:
      {

      }
      break;

      case test3State__START_MAN:
      {
         {
			if (q)
				res = xact_goto_eci_attitude(q);
		}
         if (__retries_START_MAN >= MAX_MAN_RETRIES) {
            __next_state = __ERR_STATE;
            __err = test3Err__ManFailed;
         }
         else
         if (q == NULL) {
            __next_state = __ERR_STATE;
            __err = test3Err__MemViolation;
         }
         else
         if (res == TRUE) {
            __next_state = test3State__WAIT_MAN;
            fsm_timer_start(&maneuver_timer);
         }
         else
         if (res == FALSE) {
            __next_state = test3State__START_MAN;
            __retries_START_MAN++;
         }

         else {
	        // stay in this state
		 }

      }
      break;

      case test3State__WAIT_MAN:
      {
         {
			xact_get_error(&q_err);
		}
         if (is_error_less_than(&q_err, MAX_ERROR)) {
            __next_state = test3State__WAIT_STABLE;
            fsm_timer_start(&stable_timer);
         }
         else
         if (fsm_timer_expired(&maneuver_timer)) {
            __next_state = test3State__START_MAN;
            __retries_START_MAN++;
         }

         else {
	        // stay in this state
		 }

      }
      break;

      case test3State__WAIT_STABLE:
      {
         {
			xact_get_error(&q_err);
		}
         if (!is_error_less_than(&q_err, MAX_ERROR)) {
            __next_state = test3State__WAIT_MAN;
         }
         else
         if (fsm_timer_expired(&stable_timer)) {
            __next_state = test3State__FINISHED;
         }
         else
         if (fsm_timer_expired(&maneuver_timer)) {
            __next_state = test3State__START_MAN;
            __retries_START_MAN++;
         }

         else {
	        // stay in this state
		 }

      }
      break;


      default:
	     // TODO: handle error here
      break;
   }
   // assign new values to the output (Mealy Machine)
   man_state = (__out_table__man_state[__next_state] != NULL ? __out_table__man_state[__next_state]() : man_state);

   // execute transition
   __cur_state = __next_state;

   return __cur_state;
}
