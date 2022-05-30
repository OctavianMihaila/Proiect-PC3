/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include "utils.h"

/* Functia cauta prin lista de camere si daca aceasta
este disponibila o aloca solicitantului */
void find_room(TLG room_list, char *tenant_name, int days, int room_id) {
    TLG p = room_list;
    
    while (p) {
        if (((Room *)p->info)->id == room_id) break;
        p = p->urm;
    }

    if (!p) {
        printf("Room %d not found\n", room_id);
        return;
    }
    else {
        if (((Room *)p->info)->used == 0) {
            ((Room *)p->info)->tenant->day_count = days;
            ((Room *)p->info)->tenant->room_id = room_id;
            ((Room *)p->info)->tenant->name = tenant_name;
            ((Room *)p->info)->used = 1;
        }
        else {
            printf("Room %d is rented\n", room_id);
            return;
        }

        return;
    }
}

void show_status(TLG room_list, int room_id) {
    TLG p = room_list;
    
    while (p) {
        if (((Room *)p->info)->id == room_id) break;
        p = p->urm;
    }

    if (!p) {
        printf("Room %d not found\n", room_id);

        return;
    }
    else {
        if (((Room *)p->info)->used == 0) {
            printf("Room %d is free\n", room_id);
        }
        else {
            printf("Room %d is used\n", room_id);
        }

        return;
    }
}