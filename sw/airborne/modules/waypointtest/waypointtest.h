#include "firmwares/rotorcraft/navigation.h"
#include "generated/flight_plan.h"
#include "math/pprz_geodetic_int.h"
#include "state.h"

void waypointtest_init(void);

void waypointtest_periodic(void);

int moveWaypoint_HD(uint8_t wp_id);

bool_t mock_detectObstacle(uint8_t wp_id);

//int detectObstacle(void);

//int generateWaypoint(uint8_t wp_id);
