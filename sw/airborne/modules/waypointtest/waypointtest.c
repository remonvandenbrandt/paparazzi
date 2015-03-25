#include "math/pprz_geodetic_int.h"
#include "firmwares/rotorcraft/navigation.h"
#include "generated/flight_plan.h"
#include <stdio.h>
#include <stdlib.h>
/*double wx=51.990680;
double wy=4.376790;
struct LlaCoor_i waypoint;
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

	//nav_move_waypoint_lla(WP_DynamicWP, &waypoint);
	//nav_set_heading_towards_waypoint(WP_DynamicWP);

	unsigned int i=0;
   	
	for(i=0; i<60000; i++) {	
		waypoint.lat=waypoint.lat+0.000002;
		waypoint.lon=waypoint.lon+0.000002;
		nav_move_waypoint_lla(WP_DynamicWP, &waypoint);
		nav_set_heading_towards_waypoint(WP_DynamicWP);
  	}*/
}

int moveWaypoint_HD(uint8_t wp_id) {
	printf("Waypoint nr: %i", wp_id);
	nav_set_heading_towards_waypoint(wp_id);
return 0;
}


bool_t mock_detectObstacle(void){
   int i, n;
   time_t t;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));
   if(t % 30 == 0){
 	i=rand() % 1; //Generates 1 or 0
   } else {
   	i=0;
   }
	printf("%d",i);
   return i;
}

/*int detectObstacle(void) {
	nav_set_heading_towards_waypoint(WP_GlobalWP);
	return 0;
}

int generateWaypoint(uint8_t wp_id) {
	nav_set_heading_towards_waypoint(wp_id);
	return 0;
}*/
