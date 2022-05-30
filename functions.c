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