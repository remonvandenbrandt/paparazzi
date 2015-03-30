#include "firmwares/rotorcraft/navigation.h"
//#include "generated/flight_plan.h"
#include "math/pprz_geodetic_int.h"
#include "state.h"
#include <time.h>
#include <stdlib.h>
uint8_t wayp;

void waypointtest_init(void);

/*void waypointtest_periodic(void);

int moveWaypoint_HD(int);

int generateRandomWaypoint(int);*/

extern int createRandWP(void);

extern uint8_t getRandWP(void);

//int detectObstacle(void);

//int generateWaypoint(uint8_t wp_id);
