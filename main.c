/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include "utils.h"

int main () {
    char *request = NULL, *token = NULL, *aux_request = NULL;
    int room_id, bulb_id, nr_housekeepers, max_rooms_cleanup;

    queue cleanup_queue = NULL, start_cleanup_queue = NULL;

    scanf("%d", &nr_housekeepers);
    scanf("%d", &max_rooms_cleanup);
    scanf("\n");
    int max_clean_per_day = nr_housekeepers * max_rooms_cleanup;

    char *person_auth = calloc(50, sizeof(char)); // persoana curenta autentificata
    if (!person_auth) {
        printf("allocation failed for person_auth.");
        return 0;
    }

    request = calloc(100, sizeof(char));
    if (!request) {
        printf("allocation failed for request.");
        return 0;
    }

    while (scanf("%[^\n] ", request) != EOF) {
        aux_request = calloc(strlen(request) + null_terminator, sizeof(char));
        if (!aux_request) {
            printf("allocation failed for aux_request.");
            return 0;
        }
        memcpy(aux_request, request, strlen(request) + null_terminator);
        
        switch (encode(aux_request))
        {
            case init_hotel:
                token = strtok(request + offset_rooms, " ");
                int room_numbers = atoi(token);

                token = strtok(NULL, " ");
                int nr_bulbs = atoi(token);

                Hotel *hotel = InitHotel(room_numbers, nr_bulbs);

                break;

            case authentification:
                token = strtok(request + offset_authentification, " ");
                char *name = strdup(token);

                token = strtok(NULL, " ");
                int nr_room = atoi(token);

                //only the current pers auth can have control over commands 
                //concerning the lighting system if they have already rented 
                //the room they want to make changes in

                memcpy(person_auth, name, strlen(name));        
                if ( CheckAccess(hotel->rooms, name, nr_room, Room_Owner) == 1 )
                    printf("%s is now in control of the lighting system in room %d\n", name, nr_room);
                else {
                    printf("Sorry. Authentication failed.\n");
                }
                
                break; 


            case switch_the_light:
                token = strtok(request + offset_switch, " ");
                char *status = strdup(token); // on / off

                token = strtok(NULL, " ");
                room_id = atoi(token);          

                token = strtok(NULL, " ");
                bulb_id = atoi(token);

                if ( person_auth != NULL ) {
                    switch_light(person_auth, status, room_id, bulb_id, &hotel->rooms);
                } else 
                    printf("There is no person authenticated.\n");

                break;  

            case brightness_adjustment:
                token = strtok(request + offset_brightness, " ");
                char *pers = strdup(token);

                token = strtok(NULL, " ");
                int room_id = atoi(token);

                token = strtok(NULL, " ");
                bulb_id = atoi(token);

                token = strtok(NULL, " ");
                char R = atoi(token);

                token = strtok(NULL, " ");
                char G = atoi(token);

                token = strtok(NULL, " ");
                char B = atoi(token);

                brightness_adj(pers, room_id, bulb_id, &hotel->rooms, R, G, B);

                break;
            
            
            case turn_off_all_lights:
                token = strtok(request + offset_turn_off, " ");
                room_id = atoi(token);

                break;

            case rent_room:
                token = strtok(request + offset_rent, " ");
                char *tenant_name = strdup(token);

                token = strtok(NULL, " ");
                int days = atoi(token);

                token = strtok(NULL, " ");
                room_id = atoi(token);

                Tenant *tenant = calloc(1, sizeof(tenant));
                tenant->name = tenant_name;
                tenant->room_id = room_id;
                tenant->day_count = days;

                find_room(hotel->rooms, tenant_name, days, room_id,
                        &start_cleanup_queue, &cleanup_queue);

                break;

            case show_room_status:
                token = strtok(request + offfset_show_room, " ");
                room_id = atoi(token);

                show_status(hotel->rooms, room_id);
                // search in rooms

                break;

            case cleanup:
                cleanup_day(&start_cleanup_queue, max_clean_per_day);
                printf("cleanup\n");
                break;

            case day_passed:
                sub_day(hotel->rooms, &cleanup_queue, &start_cleanup_queue);
                print_cleanup_q(&cleanup_queue, &start_cleanup_queue);

                printf("day_passed\n");
                break;

            case quit:
                DestroyTLG(&(hotel->rooms));
                free_q(&(hotel->cleanup_queue));
                free(request);
                free(person_auth);
                free(hotel);
                
                break;
            
        default:

            break;
        }
    }

    return 0;
}