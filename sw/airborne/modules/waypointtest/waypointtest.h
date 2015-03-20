#include "firmwares/rotorcraft/navigation.h"
#include "generated/flight_plan.h"
#include "math/pprz_geodetic_int.h"

void waypointtest_init(void);

void waypointtest_periodic(void);

int moveWaypoint(uint8_t wp_id);

int detectObstacle(void);

int generateWaypoint(uint8_t wp_id);
