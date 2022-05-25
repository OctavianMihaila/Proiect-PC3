/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define init_hotel 1
#define switch_the_light 2
#define brightness_adjustment 3
#define turn_off_all_lights 4
#define rent_room 5
#define show_room_status 6
#define cleanup 7
#define day_passed 8
#define quit 9
#define null_terminator 1

// Argument pentru switch-ul care realizeaza parsarea.
int encode(char *request);
