#include "math/pprz_geodetic_int.h"
#include "firmwares/rotorcraft/navigation.h"
#include "generated/flight_plan.h"
#include <stdio.h>

//double wx=51.990680;
//double wy=4.376790;



/*struct LlaCoor_i waypoint;
waypoint.lat=51.990680;
waypoint->lon=4.376790;
waypoint->alt=200;*/

void waypointtest_init(void)
{
}



void waypointtest_periodic(void)
{
	/*struct LlaCoor_i waypoint;
	waypoint.lat=51.9906689;
	waypoint.lon=4.3768509;
	waypoint.alt=200;

	nav_move_waypoint_lla(WP_DynamicWP, &waypoint);
	nav_set_heading_towards_waypoint(WP_DynamicWP);

	unsigned int i=0;
   	
	for(i=0; i<60000; i++) {	
		waypoint.lat=waypoint.lat+0.000002;
		waypoint.lon=waypoint.lon+0.000002;
		nav_move_waypoint_lla(WP_DynamicWP, &waypoint);
		nav_set_heading_towards_waypoint(WP_DynamicWP);
  	}*/
}

int moveWaypoint(uint8_t wp_id) {
	time_t counter;
	counter = time(NULL);	
	time_t t;
	srand((unsigned) time(&t));

	if((uintmax_t) counter %15 == 0) {
		int randomNumber = rand() %500;
		struct EnuCoor_i waypoint;
		waypoint.x=randomNumber*5;
		waypoint.y=randomNumber*8;
		waypoint.z=0;

		nav_move_waypoint(wp_id, &waypoint);
		nav_set_heading_towards_waypoint(wp_id);
	} else {
		//nav_set_heading_towards_waypoint(wp_id);
	}
	return 0;
}

int detectObstacle(void) {
	nav_set_heading_towards_waypoint(WP_GlobalWP);
	return 0;
}

int generateWaypoint(uint8_t wp_id) {
	nav_set_heading_towards_waypoint(wp_id);
	return 0;
}
