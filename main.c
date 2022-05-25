/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

#include "utils.h"

int main () {
    char *request = NULL, *token = NULL, *aux_request = NULL;

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
            printf("init_hotel\n");
            break;

        case switch_the_light:
            printf("switch_the_light\n");
            break;  

        case brightness_adjustment:
            printf("brightness_adjustment\n");
            break;
        
        case turn_off_all_lights:
            printf("turn_off_all_lights\n");
            break;

        case rent_room:
            printf("rent_room\n");
            break;

        case show_room_status:
            printf("show_room_status\n");
            break;

        case cleanup:
            printf("cleanup\n");
            break;

        case day_passed:
            printf("day_passed\n");
            break;

        case quit:
            printf("quit\n");
            break;
        
        default:
            break;
        }
    }

    return 0;
}