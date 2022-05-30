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
#define authentification 10
#define null_terminator 1

// Argument pentru switch-ul care realizeaza parsarea.
int encode(char *request);

typedef struct  tenant{
   char* name;
   int day_count;
   int room_id;                          //roomm id 
} Tenant;

typedef struct  lights {
    int id;
    int proper;
} LightBulb;

typedef struct  room {
    int id;
    Tenant* tenant;
    LightBulb*  bulbs;                  //lista becuri camera
    int nr_bulbs;                       //total numbers
    int used;
} Room;

typedef struct hotel {
    int nr_rooms;
    Room* rooms;
} Hotel;

typedef struct celulag {
  void* info;           
  struct celulag *urm;
} TCelulaG, *TLG;

