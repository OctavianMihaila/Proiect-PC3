/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

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

typedef struct tenant {
   char* name;
   int day_count; // numar de zile ramas pana la decazare
   int room_id;
} Tenant;

typedef struct  lights {
    int id;
    int proper; // on/off (byte 1), R(byte 2), G(byte 3), B(byte 4). (big endian)
} LightBulb;

typedef struct  room {
    int id;
    Tenant* tenant;
    TLG  bulbs; //lista becuri camera
    int nr_bulbs; 
    int used;
} Room;

typedef struct hotel {
    int nr_rooms;
    TLG rooms;
    queue cleanup_queue; // coada de curatare a camerelor eliberate
} Hotel;


//function pointer for TLG functions
typedef void (*TF)(void*);
typedef int (*TFCmp)(Room room, char* pers, int id);

TLG alloc_cell(void* x);
TLG InitBulbs( TLG bulbs, int nr_bulbs);
Hotel* InitHotel(int nr_rooms, int nr_bulbs);
void PrintList(TLG L, TF printEL);
void print_bulbs(void* el);
void print_rooms(void* el);

/* Functia realizeaza atribuirea camerei catre cel care a facut cererea
In plus, in cazul in care camera se afla in coada de curatare, aceasta
devine prioritara (este trecuta prima in coada) */
void find_room(TLG room_list, char *tenant_name, int days, int room_id,
                queue *start_q, queue *cleanup_q);

// Verificare camera ocupata/libera.
void show_status(TLG room_list, int room_id);

// Functia scade cate o zi pentru fiecare chirias (day passed)
void sub_day(TLG rooms, queue *cleanup_queue, queue *start_cleanup_queue);

/* Se curata primele max_clean_per_day din coada si
acestea devin din nou disponibile pentru inchiriere */
void cleanup_day(queue *start_cleanup_queue, int max_clean_per_day);

/* Functia printeaza coada de asteptare pentru curatere */
void print_cleanup_q (queue *cleanup_q, queue *start_cleanup_q);

// Functia elibereaza memoria pentru o coada.
void free_q(queue *start_q);

// Functia elibereaza memoria unei liste generice.
void DestroyTLG(TLG* aL);
