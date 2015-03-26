#include "math/pprz_geodetic_int.h"
#include "firmwares/rotorcraft/navigation.h"
#include "state.h"
#include "waypointtest.h"
#include "generated/flight_plan.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int moveWaypoint_HD(wp_id) {
	printf("Waypoint nr: %i", wp_id);
	nav_set_heading_towards_waypoint(wp_id);
return 0;
}


int generateRandomWaypoint(wp_id){
   //int i, n;
   struct Int32Eulers Angles;
   struct EnuCoor_i waypoint;
   time_t t;
   t = time(&t);
   srand((unsigned) t);
   /*waypoint.x = rand() %7;
   waypoint.y = rand() %7;
   waypoint.x=waypoint.x*10;
   waypoint.y=waypoint.y*10;
   nav_move_waypoint(wp_id, &waypoint);*/
   printf("DEBG x: %d \n y: %d \n",waypoint.x, waypoint.y);
   printf("Time: %d \n", t);
   waypoint = *stateGetPositionEnu_i();
   Angles = *stateGetNedToBodyEulers_i();
   printf("Debug message: Entered the function");
   //Intializes random number generator
   
   /*if(t % 10 == 0){
 	i=1; //Generates 1 or 0 */

	waypoint.x=waypoint.x+900*cos(Angles.phi)+900*sin(Angles.phi);
	//waypoint.y=waypoint.y-265*sin(Angles.phi)+265*cos(Angles.phi);

	nav_move_waypoint(wp_id, &waypoint);
   /*} else {
   	i=0;
   }*/
   return 0;
}

/*int detectObstacle(void) {
	nav_set_heading_towards_waypoint(WP_GlobalWP);
	return 0;
}
int generateWaypoint(uint8_t wp_id) {
	struct EnuCoor_i waypoint;
	waypoint.x=1;
	waypoint.y=1;
	waypoint.z=0;

	nav_move_waypoint(wp_id, &waypoint);

	return 0;
}*/
