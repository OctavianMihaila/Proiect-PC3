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
        room->id = i;
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
        LightBulb* bulb = calloc(1, sizeof(LightBulb));
        bulb->id = i;

        aux = alloc_cell(bulb);
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


void PrintList(TLG L, TF printEL) {
    if(!L) {
       printf("Lista vida\n");
       return;
    }

	printf("LIST:\n[\n");
	for(; L; L = L->urm) 
		printEL(L->info);
    
	printf("]\n");
}

void print_bulbs(void* el) {
	printf("    @bulb id: %d - proper: %d\n", ((LightBulb*)el)->id, ((LightBulb*)el)->proper);
}

void print_rooms(void* el) {
    printf("---->room id: %d\n", ((Room*)el)->id);
    PrintList(((Room*)el)->bulbs, print_bulbs);
}

//lighting system functions:
//only available if there was an authentification command 

//function that looks in the room list if there is a name and id matching for the pair
//to check

int CheckAccess (TLG list, char* pers, int id_room, TFCmp cmp) {
    for ( ; list != NULL; list = list->urm ) {
        Room room = *((Room*)(list->info));
        if ( cmp(room, pers, id_room) == 1 ) 
            return 1; 
    } 
    return 0;
}

//1 if the pers is the owner of the room at the moment
int Room_Owner (Room room, char* pers, int id ) {
    printf(">>>%s\n", room.tenant->name);
    if ( strcmp ( room.tenant->name, pers) == 0 ) {
        if ( room.tenant->room_id == id ) {
            if ( room.tenant->day_count > 0 ) 
                return 1;
            else 
                return 0;
        } else 
            return 0;
    } else 
        return 0;
}

//check if the operation is possible
//find the bulb in that room
//change the first byte to 1 oe 0 from prior field

TLG FindRoom_by_ID (TLG rooms, int room_id ) {
    TLG p = rooms;
    
    while (p) {
        if (((Room *)p->info)->id == room_id) break;
        p = p->urm;
    }

    return p;
}


void switch_light (char* pers, char* status, int room_id, int bulb_id, TLG* rooms) {
    if ( CheckAccess( (*rooms), pers, room_id, Room_Owner) == 0 ) {
        printf("You do not own this room. Please enter your room.\n");
        return;
    }

    //find the room
    TLG room = FindRoom_by_ID((*rooms), room_id);
    TLG bulb_list = ((Room*)room->info)->bulbs;
    TLG list = bulb_list;
    char exist = 0;
    for ( ; list != NULL; list = list->urm ) {
        LightBulb* bulb = ((LightBulb*)list->info);
        if ( bulb->id == bulb_id ) {
            if ( strcmp( status, "off") == 0 ) {
                bulb->proper = bulb->proper << 8;
                bulb->proper = bulb->proper >> 8;
               
            } else {
                bulb->proper = bulb->proper << 8;
                bulb->proper = bulb->proper >> 8;
                bulb->proper = bulb->proper + (1 << 24 );

            }
            exist = 1;
        }
    }

    if ( exist == 0 ) 
        printf("What would a room do with so many light bulbs? It's not a club, try again.\n");
    

    return;
}


void brightness_adj (char* pers, int room_id, int bulb_id, TLG* rooms, char R, char G, char B) {
    if ( CheckAccess( (*rooms), pers, room_id, Room_Owner) == 0 ) {
        printf("You do not own this room. Please enter your room.\n");
        return;
    }

    //find the room
    TLG room = FindRoom_by_ID((*rooms), room_id);
    ((Room*)room->info)->bulbs = modify_prop(((Room*)room->info)->bulbs, bulb_id, R, G, B);
    
    return ;
}

TLG modify_prop (TLG bulb_list, int bulb_id, char R, char G, char B) {
    TLG list = bulb_list;
    char exist = 0;
    for ( ; list != NULL; list = list->urm ) {
        LightBulb* bulb = ((LightBulb*)list->info);
        
        if ( bulb->id == bulb_id ) {
            bulb->proper = 0;
            //modific pe bytes campul de proper
            //xorez byte ul de modificat din numar, adaug la el rez dintre
            //11111111 and R/G/B 
            int blue = 255 & B;
            bulb->proper = bulb->proper + blue;
            
            int green = (255 << 8) & (G << 8);
            bulb->proper = bulb->proper + green;

            int red = (255 << 16) & (R << 16);
            bulb->proper = bulb->proper + red;
            
            printf("Now the intensity of the %d bulb is %d\n",bulb_id, bulb->proper);
            exist = 1;
        }
    }

    if ( exist == 0 ) 
        printf("What would a room do with so many light bulbs? It's not a club, try again.\n");
    
    return bulb_list;
}