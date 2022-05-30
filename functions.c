/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include "utils.h"

int encode(char *request) {
    char *token = NULL;
    token = strtok(request, " ");

    if (strcmp(token, "init_hotel") == 0) {
        free(request);
        return init_hotel;
    }
    else if (strcmp(token, "authentification") == 0) {
        free(request);
        return authentification;
    }
    else if (strcmp(token, "switch_the_light") == 0) {
        free(request);
        return switch_the_light;
    }
    else if (strcmp(token, "brightness_adjustment") == 0) {
        free(request);
        return brightness_adjustment;
    }
    else if (strcmp(token, "turn_off_all_lights") == 0) {
        free(request);
        return turn_off_all_lights;
    }
    else if (strcmp(token, "rent_room") == 0) {
        free(request);
        return rent_room;
    }
    else if (strcmp(token, "show_room_status") == 0) {
        free(request);
        return show_room_status;
    }
    else if (strcmp(token, "cleanup") == 0) {
        free(request);
        return cleanup;
    }
    else if (strcmp(token, "day_passed") == 0) {
        free(request);
        return day_passed;
    }
    else if (strcmp(token, "quit") == 0) {
        free(request);
        return quit;
    }

    free(request);
    printf("Invalid request\n");
    return 0;
}

TLG alloc_cell(void* x) {	
    TLG aux;
  	aux = (TLG)calloc(1,sizeof(TcellG));
   	if(!aux) return NULL;
   	
	aux->info = x;
	aux->urm = NULL;
	return aux;
}

Hotel* InitHotel(int nr_rooms, int nr_bulbs ) {
    Hotel* hotel = calloc(1, sizeof(Hotel));
    hotel->nr_rooms = nr_rooms;
    
    TLG list = NULL;
    TLG  aux, contor;
    for ( int i = 1; i <= nr_rooms; i++ ) {
        Room* room = calloc( 1, sizeof(Room));
        if ( !room ) return NULL;
        room->tenant = calloc(1, sizeof(Tenant));
        room->tenant->name = calloc(50, sizeof(char));
        room->nr_bulbs = nr_bulbs;
        room->bulbs = InitBulbs(room->bulbs, nr_bulbs);

        aux = alloc_cell(room);
        if ( list == NULL ) {
            list = aux;
            contor = aux;
        } else {
            contor->urm = aux;
            contor = aux;
        }  
    }

    hotel->rooms = list;

    return hotel;
} 

TLG InitBulbs( TLG bulbs, int nr_bulbs) {
    TLG list = NULL;
    TLG aux, contor;
    for ( int i = 1 ;i <= nr_bulbs; i++ ) {
        aux = alloc_cell(&i);
        if ( list == NULL ) {
            list = aux;             //keep the head of the list
            contor = aux;
        } else {
            contor->urm = aux;
            contor = aux;
        }
    }
    return list;
}
