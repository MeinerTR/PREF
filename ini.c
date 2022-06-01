#include "ini.h"

int main(void) {
    p_B Success = INI_Open("./WhereAreWe.ini");
    if (Success == p_F) {
        printf("FAILED!\n");
    } else {
        INI_Change("STAR", "OH, OK!");

        p_I Size = INI_Get_INT("STAR_SIZE", 9);
        if (Size != INI_NULL_KEY_INT) {
            if (Size != INI_NULL_TYPE) {
                printf("%i\n", Size);
            } else {
                printf("Cannot transform \"%s\" to a number in \"%s\"!\n", INI_Key, INI_Path);
            }
        } else {
            printf("Cannot find \"%s\" in \"%s\"!\n", INI_Key, INI_Path);
        } p_I Size2 = INI_Get_INT("PLANET_SIZE", 9);
        if (Size2 != INI_NULL_KEY_INT) {
            if (Size2 != INI_NULL_TYPE) {
                printf("%i\n", Size2);
            } else {
                printf("Cannot transform \"%s\" to a number in \"%s\"!\n", INI_Key, INI_Path);
            }
        } else {
            printf("Cannot find \"%s\" in \"%s\"!\n", INI_Key, INI_Path);
        } INI_Close();
    }
}