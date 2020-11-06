#ifndef MANEUVER_LIB_H_
#define MANEUVER_LIB_H_

#include <time.h>

typedef unsigned char bool;
#define FALSE 0
#define TRUE 1
typedef struct quaternion { float r, x, y, z; } quaternion_t;

#define ADCS_PERIOD			(200)

void rtems_clock_get_uptime(struct timespec * t);
bool xact_goto_eci_attitude(struct quaternion * q);
void xact_get_error(quaternion_t * q);
bool is_error_less_than(quaternion_t * q, float e);

#endif  // MANEUVER_LIB_H_