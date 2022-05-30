/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include "utils.h"

int main () {
    char *request = NULL, *token = NULL, *aux_request = NULL;
    int room_id, bulb_id, nr_housekeepers, max_rooms_cleanup;

    scanf("%d", &nr_housekeepers);
    scanf("%d", &max_rooms_cleanup);
    scanf("\n");

    char* person_auth = NULL;              //the current authentificated person
    person_auth = calloc(50, sizeof(char));

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
                int room_number = atoi(token);

                token = strtok(NULL, " ");
                int nr_bulbs = atoi(token);

                Hotel *hotel = InitHotel(room_number, nr_bulbs);
                printf("init_hotel\n");
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

                printf("authentification\n");
                break; 


            case switch_the_light:
                token = strtok(request + offset_switch, " ");
                char *status = strdup(token); // on / off

                token = strtok(NULL, " ");
                bulb_id = atoi(token); // becul care trebuie stins

                printf("switch_the_light\n");
                break;  

            case brightness_adjustment:
                token = strtok(request + offset_brightness, " ");
                int room_id = atoi(token);

                token = strtok(NULL, " ");
                bulb_id = atoi(token);

                token = strtok(NULL, " ");
                int R = atoi(token);

                token = strtok(NULL, " ");
                int G = atoi(token);

                token = strtok(NULL, " ");
                int B = atoi(token);

                //printf(">>%d %d %d %d %d\n", room_id, bulb_id, R, G, B);

                printf("brightness_adjustment\n");
                break;
            
            case turn_off_all_lights:
                token = strtok(request + offset_turn_off, " ");
                room_id = atoi(token);

                printf("turn_off_all_lights\n");
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

                find_room(hotel->rooms, tenant_name, days, room_id);

                // search in rooms --> fill / error message

                break;

            case show_room_status:
                token = strtok(request + offfset_show_room, " ");
                room_id = atoi(token);

                show_status(hotel->rooms, room_id);
                // search in rooms

                printf("show_room_status\n");
                break;

            case cleanup:
                printf("cleanup\n");
                break;

            case day_passed:
                // actualizare peste tot
                printf("day_passed\n");
                break;

            case quit:
                // free-uri 
                printf("quit\n");
                break;
            
        default:
            break;
        }
    }

    return 0;
}