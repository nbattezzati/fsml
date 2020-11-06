#ifndef __test3_FSM_H__
#define __test3_FSM_H__

/***********************************************************/
/*                    User declarations                    */
/***********************************************************/


#include "maneuver_lib.h"

#define MAX_ERROR 			(0.1)
#define MAX_MAN_RETRIES		(3)

typedef enum {
	ManeuverState_IDLE,
	ManeuverState_BUSY,
	ManeuverState_COMPLETE,
	ManeuverState_ERR
} maneuver_out_state_t;



/***********************************************************/
/*                          STATES                          */
/***********************************************************/
typedef enum {
   test3State__FINISHED,
   test3State__START_MAN,
   test3State__WAIT_MAN,
   test3State__WAIT_STABLE,
} test3_state_t;

/***********************************************************/
/*                          ERRORS                          */
/***********************************************************/
typedef enum {
   test3Err__NoError,
   test3Err__ManFailed,
   test3Err__MemViolation,
} test3_err_t;

/***********************************************************/
/*                      FSM STRUCTURE                      */
/***********************************************************/

typedef struct {
   /* built-in functions */
   void (*reset)(void);
   test3_state_t (*exec)(void);
   test3_state_t (*state)(void);
   test3_err_t (*err)(void);

   /* input setter functions */
   void (* set_maneuver_duration)(float);
   void (* set_q)(struct quaternion *);

   /* output getter functions */
   maneuver_out_state_t (* get_man_state)(void);

} test3_fsm_t;

extern test3_fsm_t * test3_fsm;

#endif   // __test3_FSM_H__
