/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include "utils.h"

/* Functia cauta prin lista de camere si daca aceasta
este disponibila o aloca solicitantului */
void find_room(TLG room_list, char *tenant_name, int days, int room_id,
                queue *start_q, queue *cleanup_q) {
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
        // Cazul in care camera se afla in coada de curatare
        else if (((Room *)p->info)->used == -1) {
            // Camera trece prima in coada ce curatre (are prioritatea cea mai mare)
            queue *new_q = NULL, *start_new_q = NULL; 
            *new_q = InsertQ(*new_q, start_new_q, p->info);
            while (*start_q) {
                queue elem = ExtractQ(start_q);
                *new_q = InsertQ(*new_q, start_new_q, elem->data);
            }
            *cleanup_q = *new_q;
            *start_q = *start_new_q;

        }
        else {
            printf("Room %d is rented\n", room_id);
            return;
        }

        return;
    }
}

// Se verifica situatia unei camere (available, cleaning, used).
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
        else if (((Room *)p->info)->used == -1) {
            printf("Room %d is in cleaning queue\n", room_id);
        }
        else {
            printf("Room %d is used\n", room_id);
        }

        return;
    }
}

// Se scade o zi din durata fiecarei camere inchiriate
void sub_day(TLG rooms, queue *cleanup_queue, queue *start_cleanup_queue) {
    TLG p = rooms;

    while (p) {
        if (((Room *)p->info)->tenant && ((Room *)p->info)->tenant->day_count == 1) {
            ((Room *)p->info)->tenant->day_count--;
            free(((Room *)p->info)->tenant->name);
            free(((Room *)p->info)->tenant);
            ((Room *)p->info)->tenant = NULL;
            ((Room *)p->info)->used = -1; // task-ul se afla in coada de curatare.
            *cleanup_queue = InsertQ(*cleanup_queue, start_cleanup_queue, p->info);
        }
        else if (((Room *)p->info)->tenant && ((Room *)p->info)->tenant->day_count != 0) {
            ((Room *)p->info)->tenant->day_count--;
        }
        p = p->urm;
    }
}

/* Se curata primele max_clean_per_day din coada si
acestea devin din nou disponibile pentru inchiriere */
void cleanup_day(queue *start_cleanup_queue, int max_clean_per_day) {
    while (max_clean_per_day) {
        queue elem = ExtractQ(&(*start_cleanup_queue));
        if (elem) 
            ((Room *)elem->data)->used = 0;
        max_clean_per_day--;
    }
}

/* Functia printeaza coada de asteptare pentru curatere */
void print_cleanup_q (queue *cleanup_q, queue *start_cleanup_q) {
    queue aux_q = NULL, start_aux_q = NULL, elem = NULL;

    printf("====== cleanup queue =======\n");
    while (*start_cleanup_q) {
        elem = ExtractQ(start_cleanup_q);
      	printf("    Room %d\n", ((Room *)elem->data)->id);
        aux_q = InsertQ(aux_q, &start_aux_q, elem->data);

        free(elem);
    }

    *start_cleanup_q = start_aux_q;
    *cleanup_q = aux_q;
}


void free_room(Room **room) {
    free((*room)->tenant->name);
    free((*room)->bulbs);
}

// Functia elibereaza memoria unei liste generice.
void DestroyTLG(TLG* aL) 
{
	TLG aux;
	while(*aL != NULL)
    {
        aux = *aL;    
        if (!aux)
            return;
        free_room(aux->info);
        *aL = aux->urm;  
        free(aux);
    }
}

void free_q(queue *start_q) {
    queue elem = NULL;

    while (*start_q) {
        elem = ExtractQ(start_q);
        free(elem->data);
        free(elem);
    }
}
