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
#define offset_rooms 10
#define offset_authentification 16
#define offset_switch 16
#define offset_brightness 21
#define offset_turn_off 19
#define offset_rent 9
#define offfset_show_room 16

// Argument pentru switch-ul care realizeaza parsarea.
int encode(char *request);

typedef struct cellg {
    void* info;           
    struct cellg *urm;
} TcellG, *TLG;


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
    TLG  bulbs;                  //lista becuri camera
    int nr_bulbs;                       //total numbers
    int used;
} Room;

typedef struct hotel {
    int nr_rooms;
    TLG rooms;
} Hotel;


//fucntion pointer for TLG functions
typedef void (*TF)(void*);


TLG alloc_cell(void* x);
TLG InitBulbs( TLG bulbs, int nr_bulbs);
Hotel* InitHotel(int nr_rooms, int nr_bulbs);